#include "Plane.h"

#ifndef CircularPlane_H
#define CircularPlane_H

class CircularPlane : public Plane
{
public:
	double radius;

	CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources);
};

#endif