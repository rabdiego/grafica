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
	virtual Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows) = 0;

	virtual void translate(double x, double y, double z) = 0;
	virtual void scale(double x, double y, double z) = 0;

	virtual void rotateX(double angle) = 0;
	virtual void rotateY(double angle) = 0;
	virtual void rotateZ(double angle) = 0;
	virtual void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2) = 0;

	virtual void convertToCamera(Eigen::Matrix4d transformationMatrix) = 0;
};

#endif