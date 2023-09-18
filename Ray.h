#include <Eigen>

#ifndef Ray_H
#define Ray_H

class Ray {
	/*
	Classe para representar os raios
	de visão
	*/
public:
	Eigen::Vector3d initialPoint;
	Eigen::Vector3d direction;

	Ray(Eigen::Vector3d initialPoint, Eigen::Vector3d direction);
};

#endif