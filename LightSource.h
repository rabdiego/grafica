#include <Eigen>

#include "Ray.h"

#ifndef LightSource_H
#define LightSource_H

class LightSource
{
public:
	Eigen::Vector3d intensity;
	virtual void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
		Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex) = 0;
};

#endif