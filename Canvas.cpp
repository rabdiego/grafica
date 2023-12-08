#include "Canvas.h"
#include <vector>

/**
 * @brief Construtor da classe Canvas.
 * 
 * @param windowDistance Distância da câmera para o plano de projeção.
 * @param windowWidth Largura do plano de projeção.
 * @param windowHeight Altura do plano de projeção.
 * @param numLines Número de linhas do canvas.
 * @param numColumns Número de colunas do canvas.
 */
Canvas::Canvas(double windowDistance, double windowWidth, double windowHeight, double numLines, double numColumns)
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
 * @brief Classe que representa um tensor.
 * 
 * Um tensor é uma estrutura de dados multidimensional que armazena elementos de um determinado tipo.
 * Neste caso, o tensor é utilizado para armazenar os valores RGB de cada pixel em um canvas.
 */
Tensor Canvas::raycast(Eigen::Vector3d observable, Scene scene, bool toCamera)
{
	Tensor canvas(this->numColumns, this->numLines);
	double yL, xC;

	// Numero de objetos e de hitboxes na cena
	int numObjects = scene.getNumElements(), numHitBoxes = scene.getNumHitBoxes();
	Eigen::Vector3d pJ;
	int numObjectsVector = numObjects;

	// Converte os objetos para coordenadas de câmera, se necessario
	if (toCamera)
	{
		scene.convertObjectsToCamera(true);
	}

	// Calcula o numero de objetos na cena e nas hitboxes
	for (int i = 0; i < numHitBoxes; i++)
	{
		numObjectsVector += (*scene.hitboxes[i]).getNumElements();
	}

	std::vector<double> distanceToObjects(numObjectsVector);
	std::vector<Object*> objects(numObjectsVector);
	int idx;

	for (int l = 0; l < this->numLines; l++)
	{
		yL = this->jYMax - l * this->deltaY - this->deltaY / 2;

		for (int c = 0; c < this->numColumns; c++)
		{
			xC = this->jXMin + c * this->deltaX + this->deltaX / 2;

			pJ << xC, yL, -(this->windowDistance);

			Ray ray(observable, pJ);

			idx = 0;

			std::vector <bool> isShadowed;

			/*Calculamos as distancias para cada objeto
			presente na cena ou em alguma hitbox*/
			for (int i = 0; i < numObjects; i++)
			{
				distanceToObjects[idx] = ((*scene.objects[i]).hasInterceptedRay(ray));
				objects[idx] = &(*scene.objects[i]);
				idx++;
			}

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

			/*Vemos qual tem distancia minima*/
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

			// Se houver interseção, calcula a cor do pixel
			if (idxMin != -1)
			{
				Eigen::Vector3d pInt = ray.initialPoint + minimum * ray.direction;
				Eigen::Vector3d sourceDirection(0, 0, 0);
					
				for (auto& source : scene.sources)
				{
					int idx2 = 0;
					sourceDirection = source->getDirection(pInt);

					if (sourceDirection.norm() != 0)
					{
						std::vector<double> distanceToSource(numObjectsVector);
						Ray sourceRay(source->origin, pInt);

						for (int i = 0; i < numObjects; i++)
						{
							distanceToSource[idx2] = ((*scene.objects[i]).hasInterceptedRay(sourceRay));
							idx2++;
						}

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

						for (int i = 0; i < idx2; i++)
						{
							if (distanceToSource[i] < 0 && distanceToSource[i] > minimum2)
							{
								minimum2 = distanceToSource[i];
								idxMin2 = i;
							}
						}

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

				// Calcula a cor do pixel
				Eigen::Vector3d color = objects[idxMin]->computeColor(minimum, ray, scene.sources, isShadowed);

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