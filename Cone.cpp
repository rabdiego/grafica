#include "Cone.h"
#include <iostream>

Cone::Cone(double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
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

Eigen::Vector4d Cone::hasInterceptedRay(Ray ray, std::vector<LightSource*> sources)
{
	Eigen::Vector3d v = (this->vertex - ray.initialPoint);
	Eigen::Vector3d pInt(0, 0, 0);

	double a = pow((ray.direction).dot(this->direction), 2) - ((ray.direction).dot(ray.direction)) * pow(cos(this->angle), 2);
	double b = v.dot(ray.direction) * pow(cos(this->angle), 2) - (v.dot(this->direction)) * ((ray.direction).dot(this->direction));
	double c = pow(v.dot(this->direction), 2) - v.dot(v) * pow(cos(this->angle), 2);

	Eigen::Vector3d intesityEye(0, 0, 0);
	Eigen::Vector4d intensityAndDistance(0, 0, 0, 1);

	double delta = b * b - a * c;

	if (a!= 0 && delta >= 0)
	{
		double tInt;
		tInt = (-sqrt(delta) - b) / a;
		pInt = ray.initialPoint + tInt * ray.direction;
		double insideInterval = ((pInt - this->centerBase).dot(this->direction)) / this->direction.norm();

		if (insideInterval >= 0 && insideInterval <= this->height)
		{
			Eigen::Vector3d intesityAmbient(0, 0, 0);
			Eigen::Vector3d intesityDifuse(0, 0, 0);
			Eigen::Vector3d intesitySpecular(0, 0, 0);
			Eigen::Vector3d singleDifuse;
			Eigen::Vector3d singleSpecular;

			Eigen::Vector3d PI = pInt - this->vertex;
			Eigen::Vector3d normal = -((this->direction.cross(PI)).cross(PI)).normalized();

			for (auto& source : sources)
			{
				source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
			}

			intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;

			for (int i = 0; i < 3; i++)
			{
				intensityAndDistance[i] = intesityEye[i];
			}
			intensityAndDistance[3] = tInt;
		}
	}

	Eigen::Vector4d intensityAndDistanceBottom = this->bottom->hasInterceptedRay(ray, sources);

	std::vector <Eigen::Vector4d> intensityAndDistances = { intensityAndDistance, intensityAndDistanceBottom };

	double minimum = -INFINITY;
	int idx = 0;

	for (int i = 0; i < 2; i++)
	{
		if (intensityAndDistances[i][3] < 0 && intensityAndDistances[i][3] > minimum)
		{
			minimum = intensityAndDistances[i][3];
			idx = i;
		}
	}

	return intensityAndDistances[idx];
}

/*
Eigen::Vector4d Cilinder::hasInterceptedRay(Ray ray, std::vector<LightSource*> sources)
{
	Eigen::Vector3d w = ray.initialPoint - this->centerBase;
	Eigen::Vector3d pInt(0, 0, 0);

	double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(this->direction), 2);
	double b = 2 * w.dot(ray.direction) - 2 * w.dot(this->direction) * ray.direction.dot(this->direction);
	double c = w.dot(w) - pow(w.dot(this->direction), 2) - pow(this->radius, 2);

	Eigen::Vector3d intesityEye(0, 0, 0);
	Eigen::Vector4d intensityAndDistance(0, 0, 0, 1);

	double delta = b * b - 4 * a * c;

	if (a != 0 && delta >= 0)
	{
		double tInt = (sqrt(delta) - b) / (2 * a);

		pInt = ray.initialPoint + tInt * ray.direction;
		double insideInterval = (pInt - this->centerBase).dot(this->direction);

		if (insideInterval >= 0 && insideInterval <= this->height)
		{
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

			for (int i = 0; i < 3; i++)
			{
				intensityAndDistance[i] = intesityEye[i];
			}
			intensityAndDistance[3] = tInt;
		}
	}

	Eigen::Vector4d intensityAndDistanceTop = this->top->hasInterceptedRay(ray, sources);
	Eigen::Vector4d intensityAndDistanceBottom = this->bottom->hasInterceptedRay(ray, sources);

	std::vector <Eigen::Vector4d> intensityAndDistances = { intensityAndDistance, intensityAndDistanceBottom, intensityAndDistanceTop };

	double minimum = -INFINITY;
	int idx = 0;

	for (int i = 0; i < 3; i++)
	{
		if (intensityAndDistances[i][3] < 0 && intensityAndDistances[i][3] > minimum)
		{
			minimum = intensityAndDistances[i][3];
			idx = i;
		}
	}

	return intensityAndDistances[idx];
}
*/