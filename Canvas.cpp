#include "Canvas.h"
#include <vector>

Canvas::Canvas(int windowDistance, int windowWidth, int windowHeight, int numLines, int numColumns)
{
	this->windowDistance = windowDistance;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->numLines = numLines;
	this->numColumns = numColumns;

	this->deltaX = windowWidth / numColumns;
	this->deltaY = windowHeight / numLines;

	this->jXMin = -(windowWidth / 2);
	this->jYMax = windowHeight / 2;
}

Tensor Canvas::raycast(Eigen::Vector3d observable, Scene scene)
{
	/*
	M�todo para desenhar os objetos do cen�rio na tela
	*/
	Tensor canvas(this->numColumns, this->numLines);
	int yL, xC, numObjects = scene.getNumElements(), numHitBoxes = scene.getNumHitBoxes();
	Eigen::Vector3d pJ;
	int numObjectsVector = numObjects;

	for (int i = 0; i < numHitBoxes; i++)
	{
		numObjectsVector += (*scene.hitboxes[i]).getNumElements();
	}

	std::vector<Eigen::Array4d> intensityAndDistanceToObjects(numObjectsVector);
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

			for (int i = 0; i < numObjects; i++)
			{
				intensityAndDistanceToObjects[idx] = ((*scene.objects[i]).hasInterceptedRay(ray, scene.sources));
				idx++;
			}

			for (int i = 0; i < numHitBoxes; i++)
			{
				int numElements = (*scene.hitboxes[i]).getNumElements();
				if ((*scene.hitboxes[i]).hasInterceptedRay(ray))
				{
					for (int j = 0; j < numElements; j++)
					{
						intensityAndDistanceToObjects[idx] = ((*scene.hitboxes[i]->objects[j]).hasInterceptedRay(ray, scene.sources));
						idx++;
					}
				}
			}

			double minimum = -INFINITY;
			int idxMin = 0;

			for (int i = 0; i < idx; i++)
			{
				if (intensityAndDistanceToObjects[i][3] < 0 && intensityAndDistanceToObjects[i][3] > minimum)
				{
					minimum = intensityAndDistanceToObjects[i][3];
					idxMin = i;
				}
			}

			
			canvas.red(l, c) = intensityAndDistanceToObjects[idxMin][0];
			canvas.green(l, c) = intensityAndDistanceToObjects[idxMin][1];
			canvas.blue(l, c) = intensityAndDistanceToObjects[idxMin][2];
		}
	}

	return canvas;
}