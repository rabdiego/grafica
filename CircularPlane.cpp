#include "CircularPlane.h"

CircularPlane::CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
	: Plane(normal, center, kAmbient, kDif, kEsp, specularIndex)
{
	this->radius = radius;
}

double CircularPlane::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d w = ray.initialPoint - this->center;
	double tInt = -(this->normal.dot(w)) / (this->normal.dot(ray.direction));

	Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

	double insideInterval = pow((pInt - this->center).norm(), 2);

	if (tInt < 0 && insideInterval >= 0 && insideInterval <= pow(this->radius, 2))
	{
		return tInt;
	}

	return 1;
}

Eigen::Vector3d CircularPlane::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	Eigen::Vector3d intesityEye(0, 0, 0);
	Eigen::Vector3d intesityAmbient(0, 0, 0);
	Eigen::Vector3d intesityDifuse(0, 0, 0);
	Eigen::Vector3d intesitySpecular(0, 0, 0);
	Eigen::Vector3d singleDifuse;
	Eigen::Vector3d singleSpecular;
	Eigen::Vector3d normal = this->normal;
	Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

	int idx = 0;

	for (auto& source : sources)
	{
		source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
		idx++;
	}

	intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;

	return intesityEye;
}