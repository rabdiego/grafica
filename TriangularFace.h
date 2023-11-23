#include "Object.h"

#ifndef TriangularFace_H
#define TriangularFace_H

class TriangularFace : public Object
{
public:
	Eigen::Vector3d vertexes[3];
	Eigen::Vector3d normal;

	Eigen::Vector3d r1;
	Eigen::Vector3d r2;

	TriangularFace(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d v3, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
};

#endif