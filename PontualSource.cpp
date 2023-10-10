#include "PontualSource.h"

PontualSource::PontualSource(Eigen::Vector3d origin, Eigen::Vector3d intensity)
{
	this->origin = origin;
	this->intensity = intensity;
}

void PontualSource::computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
	Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	Eigen::Vector3d directionToSource = (this->origin - pInt).normalized();

	Eigen::Vector3d directionToSourceReflex = (2 * directionToSource.dot(normal) * normal) - directionToSource;
	Eigen::Vector3d rayDirectionReflex = ray.direction;

	Eigen::Vector3d tempDifuse = ((this->intensity).cwiseProduct(kDif)) * normal.dot(directionToSource);
	Eigen::Vector3d tempSpecular = ((this->intensity).cwiseProduct(kEsp)) * pow(directionToSourceReflex.dot(rayDirectionReflex), specularIndex);

	// Monkey code

	Eigen::Vector3d intesityDifuse = *ptrIntesityDifuse;
	Eigen::Vector3d intesitySpecular = *ptrIntesitySpecular;

	if (tempDifuse[0] > 0) {
		intesityDifuse[0] += tempDifuse[0];
	}
	if (tempDifuse[1] > 0) {
		intesityDifuse[1] += tempDifuse[1];
	}
	if (tempDifuse[2] > 0) {
		intesityDifuse[2] += tempDifuse[2];
	}

	if (tempSpecular[0] > 0) {
		intesitySpecular[0] += tempSpecular[0];
	}
	if (tempSpecular[1] > 0) {
		intesitySpecular[1] += tempSpecular[1];
	}
	if (tempSpecular[2] > 0) {
		intesitySpecular[2] += tempSpecular[2];
	}

	*ptrIntesityDifuse = intesityDifuse;
	*ptrIntesitySpecular = intesitySpecular;
}