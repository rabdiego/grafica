#include <Eigen>

#include "Ray.h"

#ifndef LightSource_H
#define LightSource_H

class LightSource
{
public:
	Eigen::Vector3d intensity;
	Eigen::Vector3d origin;
	virtual Eigen::Vector3d getDirection(Eigen::Vector3d pInt) = 0;
	virtual void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
		Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed) = 0;
	virtual void convertToCamera(Eigen::Matrix4d transformationMatrix) = 0;
};

#endif