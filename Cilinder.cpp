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
}

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