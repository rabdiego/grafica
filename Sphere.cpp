#include "Sphere.h"

Sphere::Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->radius = radius;
	this->center = center;
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;
}

double Sphere::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d w = ray.initialPoint - this->center;

	double b = w.dot(ray.direction);
	double c = w.dot(w) - this->radius * this->radius;

	double delta = b * b - c;

	if (delta >= 0)
		return (sqrt(delta) - b);

	return 1;
}

Eigen::Vector3d Sphere::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources)
{
	Eigen::Vector3d pInt(0, 0, 0);
	Eigen::Vector3d intesityEye(0, 0, 0);

	pInt = ray.initialPoint + tInt * ray.direction;

	Eigen::Vector3d intesityAmbient(0, 0, 0);
	Eigen::Vector3d intesityDifuse(0, 0, 0);
	Eigen::Vector3d intesitySpecular(0, 0, 0);
	Eigen::Vector3d singleDifuse;
	Eigen::Vector3d singleSpecular;
	Eigen::Vector3d normal = (pInt - this->center).normalized();

	for (auto& source : sources)
	{
		source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	}

	intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;

	return intesityEye;
}