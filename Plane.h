#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"

#ifndef Plane_H
#define Plane_H

class Plane : public Object
{
	/*
	Classe para representar uma esfera
	*/
public:
	Eigen::Vector3d normal;
	Eigen::Vector3d center;

	Plane(Eigen::Vector3d normal, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, double specularIndex);
	Eigen::Vector4d hasInterceptedRay(Ray ray, std::vector<LightSource*> sources);
};

#endif