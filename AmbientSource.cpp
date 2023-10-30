#include "AmbientSource.h"

AmbientSource::AmbientSource(Eigen::Vector3d intensity)
{
	this->intensity = intensity;
	this->origin = Eigen::Vector3d(0, 0, 0);
}

Eigen::Vector3d AmbientSource::getDirection(Eigen::Vector3d pInt)
{
	Eigen::Vector3d placeholder(0, 0, 0);
	return placeholder;
}

void AmbientSource::computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
	Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed)
{
	Eigen::Vector3d temp = ((this->intensity).cwiseProduct(kAmbient));

	// Monkey code

	Eigen::Vector3d intesityAmbient = *ptrIntesityAmbient;

	if (temp[0] > 0)
	{
		intesityAmbient[0] += temp[0];
	}
	if (temp[1] > 0)
	{
		intesityAmbient[1] += temp[1];
	}
	if (temp[2] > 0)
	{
		intesityAmbient[2] += temp[2];
	}

	*ptrIntesityAmbient = intesityAmbient;
}