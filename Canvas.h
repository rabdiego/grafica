#include <Eigen>

#include "Tensor.h"
#include "Sphere.h"
#include "PontualSource.h"
#include "Ray.h"
#include "Scene.h"

#ifndef Canvas_H
#define Canvas_H

class Canvas {
	/*
	Classe do Canvas
	*/
public:
	int windowDistance;
	int windowWidth;
	int windowHeight;
	int numLines;
	int numColumns;
	int deltaX;
	int deltaY;
	int jXMin;
	int jYMax;

	Canvas(int windowDistance, int windowWidth, int windowHeight, int numLines, int numColumns);
	Tensor raycast(Eigen::Vector3d observable, Scene scene, PontualSource source);
};

#endif