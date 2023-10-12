#include "CircularPlane.h"

CircularPlane::CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
	: Plane(normal, center, kAmbient, kDif, kEsp, specularIndex)
{
	this->radius = radius;
}

Eigen::Vector4d CircularPlane::hasInterceptedRay(Ray ray, std::vector<LightSource*> sources)
{
	Eigen::Vector3d w = ray.initialPoint - this->center;
	double tInt = -(this->normal.dot(w)) / (this->normal.dot(ray.direction));

	Eigen::Vector3d intesityEye(0, 0, 0);
	Eigen::Vector4d intensityAndDistance(0, 0, 0, 1);

	if (tInt < 0)
	{
		Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

		double insideInterval = pow((pInt - this->center).norm(), 2);

		if (insideInterval >= 0 && insideInterval <= pow(this->radius, 2))
		{
			Eigen::Vector3d intesityAmbient(0, 0, 0);
			Eigen::Vector3d intesityDifuse(0, 0, 0);
			Eigen::Vector3d intesitySpecular(0, 0, 0);
			Eigen::Vector3d singleDifuse;
			Eigen::Vector3d singleSpecular;
			Eigen::Vector3d normal = this->normal;

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

	return intensityAndDistance;
}