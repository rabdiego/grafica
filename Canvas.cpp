#include "Canvas.h"
#include <vector>


/**
 * Construtor da classe Canvas.
 *
 * @param windowDistance A distância da câmera para o canvas.
 * @param windowWidth A largura do canvas.
 * @param windowHeight A altura do canvas.
 * @param numLines O número de linhas do canvas.
 * @param numColumns O número de colunas do canvas.
 */
Canvas::Canvas(double windowDistance, double windowWidth, double windowHeight, int numLines, int numColumns)
{
	this->windowDistance = windowDistance;
	this->windowWidth = windowWidth;  // pov_w
	this->windowHeight = windowHeight;  // pov_h
	this->numLines = numLines;
	this->numColumns = numColumns;

	this->deltaX = windowWidth / numColumns;  // dx
	this->deltaY = windowHeight / numLines;  // dy

	this->jXMin = -(windowWidth / 2);  // - half_w
	this->jYMax = windowHeight / 2;  // half_h
}


/**
 * Metodo para desenha os objetos do cenario na tela.
 *
 * @param observable O ponto de onde o observador está olhando.
 * @param scene A cena a ser desenhada.
 * @param toCamera Indica se os objetos devem ser convertidos para o sistema de coordenadas da câmera.
 */
Tensor Canvas::raycast(Eigen::Vector3d observable, Scene scene, bool toCamera)
{
	Tensor canvas(this->numColumns, this->numLines);
	double yL, xC;
	int numObjects = scene.getNumElements(), numHitBoxes = scene.getNumHitBoxes();
	Eigen::Vector3d pJ;
	int numObjectsVector = numObjects;

	// converte os objetos para o sistema de coordenadas da câmera
	if (toCamera)
	{
		scene.convertObjectsToCamera(true);
	}

	// calcula o número de objetos na cena
	for (int i = 0; i < numHitBoxes; i++)
	{
		numObjectsVector += (*scene.hitboxes[i]).getNumElements();
	}

	std::vector<double> distanceToObjects(numObjectsVector);
	std::vector<Object*> objects(numObjectsVector);
	int idx;

	// Loop para pintar o canvas
	for (int l = 0; l < this->numLines; l++)
	{
		// calcula a coordenada y do pixel
		yL = this->jYMax - l * this->deltaY - this->deltaY / 2;

		for (int c = 0; c < this->numColumns; c++)
		{	
			// calcula a coordenada x do pixel
			xC = this->jXMin + c * this->deltaX + this->deltaX / 2;

			// cria o vetor pJ com parâmetros x e y do pixel e z = -d
			pJ << xC, yL, -(this->windowDistance);

			// cria o raio que sai do observador e passa pelo pixel
			Ray ray(observable, pJ);

			idx = 0;

			std::vector <bool> isShadowed;

			/**
			 * TODO: Calcula a distância do raio a cada objeto da cena(ou hitbox) e armazena em um vetor.
			 */

			//* Cada objeto da cena
			for (int i = 0; i < numObjects; i++)
			{
				distanceToObjects[idx] = ((*scene.objects[i]).hasInterceptedRay(ray));
				objects[idx] = &(*scene.objects[i]);
				idx++;
			}

			//* Cada objeto da hitbox
			for (int i = 0; i < numHitBoxes; i++)
			{
				int numElements = (*scene.hitboxes[i]).getNumElements();
				if ((*scene.hitboxes[i]).hasInterceptedRay(ray))
				{
					for (int j = 0; j < numElements; j++)
					{
						distanceToObjects[idx] = ((*scene.hitboxes[i]->objects[j]).hasInterceptedRay(ray));
						objects[idx] = &(*scene.hitboxes[i]->objects[j]);
						idx++;
					}
				}
			}

			/**
			 * TODO: Ve a distancia minima e pega o indice do objeto.
			*/
			double minimum = -INFINITY;
			int idxMin = -1;

			for (int i = 0; i < idx; i++)
			{
				if (distanceToObjects[i] < 0 && distanceToObjects[i] > minimum)
				{
					minimum = distanceToObjects[i];
					idxMin = i;
				}
			}

			//// se o o idxMin for -1, nao houve interseccao(ou seja, o raio nao interceptou nenhum objeto)
			if (idxMin != -1)
			{
				// ponto de interseção pInt = p0 + t * d
				Eigen::Vector3d pInt = ray.initialPoint + minimum * ray.direction;
				Eigen::Vector3d sourceDirection(0, 0, 0);

				/**
				 * TODO: Para cada fonte de luz da cena, verifica se o ponto de interseção está na sombra.
				*/
				for (auto& source : scene.sources)
				{
					// indice para o vetor de sombras
					int idx2 = 0;
					
					sourceDirection = source->getDirection(pInt);

					//! se a direcao da fonte de luz for zero, entao nao ha sombra
					if (sourceDirection.norm() != 0)
					{
						//? distancia a fonte de luz e raio da origem ate o ponto de interseccao
						std::vector<double> distanceToSource(numObjectsVector);
						Ray sourceRay(source->origin, pInt);

						//* Cada objeto da cena
						for (int i = 0; i < numObjects; i++)
						{
							distanceToSource[idx2] = ((*scene.objects[i]).hasInterceptedRay(sourceRay));
							idx2++;
						}

						//* Cada hitbox da cena
						for (int i = 0; i < numHitBoxes; i++)
						{
							int numElements = (*scene.hitboxes[i]).getNumElements();
							if ((*scene.hitboxes[i]).hasInterceptedRay(sourceRay))
							{
								for (int j = 0; j < numElements; j++)
								{
									distanceToSource[idx2] = ((*scene.hitboxes[i]->objects[j]).hasInterceptedRay(sourceRay));
									idx2++;
								}
							}
						}

						double minimum2 = -INFINITY;
						int idxMin2 = -1;

						//* ve a distancia minima e pega o indice do objeto
						for (int i = 0; i < idx2; i++)
						{
							if (distanceToSource[i] < 0 && distanceToSource[i] > minimum2)
							{
								minimum2 = distanceToSource[i];
								idxMin2 = i;
							}
						}


						//! se o o idxMin2 for igual ao idxMin, entao nao ha sombra
						if (idxMin == idxMin2)
						{
							isShadowed.push_back(false);
						}
						else
						{
							isShadowed.push_back(true);
						}
					}
					else
					{
						isShadowed.push_back(false);
					}
				}

				// computa a cor dos pixel e pinta o canvas
				Eigen::Vector3d color = objects[idxMin]->computeColor(minimum, ray, scene.sources, isShadowed)

				canvas.red(l, c) = color(0);
				canvas.green(l, c) = color(1);
				canvas.blue(l, c) = color(2);
			}
			else
			{
				canvas.red(l, c) = 0;
				canvas.green(l, c) = 0;
				canvas.blue(l, c) = 0;
			}
			
		}
	}

	return canvas;
}