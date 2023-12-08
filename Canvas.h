#include <Eigen>

#include "Tensor.h"
#include "Ray.h"
#include "Scene.h"

#ifndef Canvas_H
#define Canvas_H

class Canvas
{
	/*
	Classe do Canvas
	*/
public:
	double windowDistance;
	double windowWidth;
	double windowHeight;
	int numLines;
	int numColumns;
	double deltaX;
	double deltaY;
	double jXMin;
	double jYMax;

	Canvas(double windowDistance, double windowWidth, double windowHeight, int numLines, int numColumns);
	Tensor raycast(Eigen::Vector3d observable, Scene scene, bool toCamera);
};

#endif