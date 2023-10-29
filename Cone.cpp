#include "Cone.h"
#include <iostream>

Cone::Cone(double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->structure = 0;
	this->angle = angle;
	this->centerBase = centerBase;
	this->vertex = vertex;
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	this->height = (vertex - centerBase).norm();
	this->radius = this->height * tan(this->angle);
	this->direction = (vertex - centerBase).normalized();
	this->bottom = new CircularPlane(-this->direction, centerBase, radius, kAmbient, kDif, kEsp, specularIndex);
}

double Cone::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d v = (this->vertex - ray.initialPoint);
	Eigen::Vector3d pInt(0, 0, 0);

	double returnValue = 1;

	double a = pow((ray.direction).dot(this->direction), 2) - ((ray.direction).dot(ray.direction)) * pow(cos(this->angle), 2);
	double b = v.dot(ray.direction) * pow(cos(this->angle), 2) - (v.dot(this->direction)) * ((ray.direction).dot(this->direction));
	double c = pow(v.dot(this->direction), 2) - v.dot(v) * pow(cos(this->angle), 2);

	double delta = b * b - a * c;

	if (a != 0 && delta >= 0)
	{
		double tInt = (-sqrt(delta) - b) / a;
		pInt = ray.initialPoint + tInt * ray.direction;
		double insideInterval = ((pInt - this->centerBase).dot(this->direction)) / this->direction.norm();

		if (insideInterval >= 0 && insideInterval <= this->height)
		{
			returnValue = tInt;
		}
	}

	double base = this->bottom->hasInterceptedRay(ray);

	std::vector <double> distances = { returnValue, base };

	double minimum = -INFINITY;
	int idx = -1;

	for (int i = 0; i < 2; i++)
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

Eigen::Vector3d Cone::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources)
{
	if (this->structure == 0)
	{
		Eigen::Vector3d intesityEye(0, 0, 0);
		Eigen::Vector3d intesityAmbient(0, 0, 0);
		Eigen::Vector3d intesityDifuse(0, 0, 0);
		Eigen::Vector3d intesitySpecular(0, 0, 0);
		Eigen::Vector3d singleDifuse;
		Eigen::Vector3d singleSpecular;

		Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

		Eigen::Vector3d PI = pInt - this->vertex;
		Eigen::Vector3d normal = -((this->direction.cross(PI)).cross(PI)).normalized();

		for (auto& source : sources)
		{
			source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
		}

		intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;
		return intesityEye;
	}
	else
	{
		return this->bottom->computeColor(tInt, ray, sources);
	}
}