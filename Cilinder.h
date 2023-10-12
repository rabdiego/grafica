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
	double radius;
	double height;
	Eigen::Vector3d centerBase;
	Eigen::Vector3d centerTop;
	Eigen::Vector3d direction;
	CircularPlane* bottom;
	CircularPlane* top;

	Cilinder(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	Eigen::Vector4d hasInterceptedRay(Ray ray, std::vector<LightSource*> sources);
};

#endif