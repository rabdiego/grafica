#include "TriangularFace.h"

#ifndef Cube_H
#define Cube_H

class Cube : public Object
{
public:
	TriangularFace* faces[12];
	int structure;
	Eigen::Vector3d center;

	Cube(Eigen::Vector3d mainVertex, double width, double height, double depth, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
};

#endif