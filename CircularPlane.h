#include "Plane.h"

#ifndef CircularPlane_H
#define CircularPlane_H

class CircularPlane : public Plane
{
public:
	double radius;

	CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
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