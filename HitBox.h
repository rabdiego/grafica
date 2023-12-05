#include <Eigen>
#include <vector>

#include "Ray.h"
#include "Object.h"

#ifndef HitBox_H
#define HitBox_H

class HitBox
{
	/*
	Classe para representar uma esfera
	*/
public:
	double radius;
	double height;
	Eigen::Vector3d centerBase;
	Eigen::Vector3d centerTop;
	Eigen::Vector3d direction;
	std::vector<Object*> objects;

	HitBox(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop);
	void addObject(Object* object);
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
	bool hasInterceptedRay(Ray ray);
	int getNumElements();
};

#endif