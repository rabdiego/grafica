#include <Eigen>

#include "Ray.h"
#include "PontualSource.h"
#include "Object.h"

#ifndef Sphere_H
#define Sphere_H

class Sphere : public Object {
	/*
	Classe para representar uma esfera
	*/
public:
	double radius;
	Eigen::Vector3d center;
	Eigen::Vector3d kDif;
	Eigen::Vector3d kEsp;
	double specularIndex = 15;

	Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	Eigen::Vector4d hasInterceptedRay(Ray ray, PontualSource source);
};

#endif