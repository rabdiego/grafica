#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"

#ifndef Object_H
#define Object_H

class Object
{
public:
	Eigen::Vector3d kAmbient;
	Eigen::Vector3d kDif;
	Eigen::Vector3d kEsp;
	int specularIndex;

	virtual double hasInterceptedRay(Ray ray) = 0;
	virtual Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources) = 0;
};

#endif