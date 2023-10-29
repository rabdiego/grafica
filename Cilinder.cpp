#include <vector>
#include "Cilinder.h"

Cilinder::Cilinder(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->radius = radius;
	this->centerBase = centerBase;
	this->centerTop = centerTop;
	this->direction = (centerTop - centerBase).normalized();
	this->height = (centerTop - centerBase).norm();
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->structure = 0;
}

double Cilinder::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d w = ray.initialPoint - this->centerBase;
	Eigen::Vector3d pInt(0, 0, 0);

	double returnValue = 1;

	double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(this->direction), 2);
	double b = 2 * w.dot(ray.direction) - 2 * w.dot(this->direction) * ray.direction.dot(this->direction);
	double c = w.dot(w) - pow(w.dot(this->direction), 2) - pow(this->radius, 2);

	double delta = b * b - 4 * a * c;

	if (a != 0 && delta >= 0)
	{
		double tInt = (sqrt(delta) - b) / (2 * a);

		pInt = ray.initialPoint + tInt * ray.direction;
		double insideInterval = (pInt - this->centerBase).dot(this->direction);

		if (insideInterval >= 0 && insideInterval <= this->height)
		{
			returnValue = tInt;
			this->structure = 0;
		}

	}

	double top = this->top->hasInterceptedRay(ray);
	double bottom = this->bottom->hasInterceptedRay(ray);

	double minimum = -INFINITY;
	int idx = -1;
	std::vector <double> distances = { returnValue, top, bottom };

	for (int i = 0; i < 3; i++)
	{
		if (distances[i] < 0 && distances[i] > minimum)
		{
			minimum = distances[i];
			idx = i;
			this->structure = i;
		}
	}

	if (idx != -1)
		return distances[idx];

	return 1;
}

Eigen::Vector3d Cilinder::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources)
{
	if (this->structure == 0)
	{
		Eigen::Vector3d intesityEye(0, 0, 0);
		Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

		Eigen::Vector3d intesityAmbient(0, 0, 0);
		Eigen::Vector3d intesityDifuse(0, 0, 0);
		Eigen::Vector3d intesitySpecular(0, 0, 0);
		Eigen::Vector3d singleDifuse;
		Eigen::Vector3d singleSpecular;

		Eigen::Vector3d v = pInt - this->centerBase;
		Eigen::Vector3d projection = (v.dot(this->direction)) * this->direction;
		Eigen::Vector3d normal = (v - projection).normalized();

		for (auto& source : sources)
		{
			source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
		}

		intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;
		return intesityEye;
	}
	else if (this->structure == 1)
	{
		return this->top->computeColor(tInt, ray, sources);
	}
	else
	{
		return this->bottom->computeColor(tInt, ray, sources);
	}
}