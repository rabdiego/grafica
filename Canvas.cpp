#include "Canvas.h"

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

Tensor Canvas::raycast(Eigen::Vector3d observable, Sphere sphere, PontualSource source) {
	/*
	Método para desenhar os objetos do cenário na tela
	*/
	Tensor canvas(this->numColumns, this->numLines);
	int yL, xC;
	Eigen::Vector3d pJ, intercepted;

	for (int l = 0; l < this->numLines; l++) {
		yL = this->jYMax - l * this->deltaY - this->deltaY / 2;

		for (int c = 0; c < this->numColumns; c++) {
			xC = this->jXMin + c * this->deltaX + this->deltaX / 2;

			pJ << xC, yL, -(this->windowDistance);

			Ray ray(observable, pJ);

			intercepted = sphere.hasInterceptedRay(ray, source);

			canvas.red(l, c) = intercepted[0];
			canvas.green(l, c) = intercepted[1];
			canvas.blue(l, c) = intercepted[2];
		}
	}

	return canvas;
}