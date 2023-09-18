#include <Eigen>

#ifndef PontualSource_H
#define PontualSource_H

class PontualSource {
	/*
	Classe para representar uma fonte
	de luz pontual
	*/
public:
	Eigen::Vector3d origin;
	Eigen::Vector3d intensity;

	PontualSource(Eigen::Vector3d origin, Eigen::Vector3d intensity);
};

#endif