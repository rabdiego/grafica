#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"

#ifndef Sphere_H
#define Sphere_H

class Sphere : public Object
{
	/*
	Classe para representar uma esfera
	*/
public:
	double radius;
	Eigen::Vector3d center;

	Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif