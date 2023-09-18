#include "Canvas.h"
#include <vector>

Canvas::Canvas(int windowDistance, int windowWidth, int windowHeight, int numLines, int numColumns) {
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

Tensor Canvas::raycast(Eigen::Vector3d observable, Scene scene, PontualSource source) {
	/*
	Método para desenhar os objetos do cenário na tela
	*/
	Tensor canvas(this->numColumns, this->numLines);
	int yL, xC, numObjects = scene.getNumElements();
	Eigen::Vector3d pJ;
	std::vector<Eigen::Array4d> intensityAndDistanceToObjects(numObjects);

	for (int l = 0; l < this->numLines; l++) {
		yL = this->jYMax - l * this->deltaY - this->deltaY / 2;

		for (int c = 0; c < this->numColumns; c++) {
			xC = this->jXMin + c * this->deltaX + this->deltaX / 2;

			pJ << xC, yL, -(this->windowDistance);

			Ray ray(observable, pJ);

			for (int i = 0; i < numObjects; i++) {
				intensityAndDistanceToObjects[i] = (*scene.objects[i]).hasInterceptedRay(ray, source);
			}

			double minimum = -INFINITY;
			int idx = 0;

			for (int i = 0; i < numObjects; i++) {
				if (intensityAndDistanceToObjects[i][3] < 0 && intensityAndDistanceToObjects[i][3] > minimum) {
					minimum = intensityAndDistanceToObjects[i][3];
					idx = i;
				}
			}

			canvas.red(l, c) = intensityAndDistanceToObjects[idx][0];
			canvas.green(l, c) = intensityAndDistanceToObjects[idx][1];
			canvas.blue(l, c) = intensityAndDistanceToObjects[idx][2];
		}
	}

	return canvas;
}