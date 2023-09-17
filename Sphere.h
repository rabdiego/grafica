#include <Eigen>

#include "Ray.h"
#include "PontualSource.h"

#ifndef Sphere_H
#define Sphere_H

class Sphere {
	/*
	Classe para representar uma esfera
	*/
public:
	double radius;
	Eigen::Vector3d center;
	Eigen::Vector3d kDif;
	Eigen::Vector3d kEsp;
	double specularIndex = 15;

	Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kDif, Eigen::Vector3d kEsp);
	Eigen::Vector3d hasInterceptedRay(Ray ray, PontualSource source);
};

#endif