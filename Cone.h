#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"
#include "CircularPlane.h"

#ifndef Cone_H
#define Cone_H

class Cone : public Object
{
	/*
	Classe para representar uma esfera
	*/
public:
	int structure;
	double radius;
	double height;
	double angle;
	Eigen::Vector3d centerBase;
	Eigen::Vector3d vertex;
	Eigen::Vector3d direction;
	CircularPlane* bottom;

	Cone(double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	Cone(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotate(double x, double y, double z);
};

#endif