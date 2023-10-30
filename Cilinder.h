#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"
#include "CircularPlane.h"

#ifndef Cilinder_H
#define Cilinder_H

class Cilinder : public Object
{
	/*
	Classe para representar uma esfera
	*/
public:
	int structure;
	double radius;
	double height;
	Eigen::Vector3d centerBase;
	Eigen::Vector3d centerTop;
	Eigen::Vector3d direction;
	CircularPlane* bottom;
	CircularPlane* top;

	Cilinder(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);
};

#endif