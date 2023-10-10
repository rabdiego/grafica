#include <Eigen>

#include "LightSource.h"

#ifndef PontualSource_H
#define PontualSource_H

class PontualSource : public LightSource
{
	/*
	Classe para representar uma fonte
	de luz pontual
	*/
public:
	Eigen::Vector3d origin;
	PontualSource(Eigen::Vector3d origin, Eigen::Vector3d intensity);
	void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
		Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
};

#endif