#include <vector>
#include "HitBox.h"

HitBox::HitBox(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop)
{
	this->radius = radius;
	this->centerBase = centerBase;
	this->centerTop = centerTop;
	this->direction = (centerTop - centerBase).normalized();
	this->height = (centerTop - centerBase).norm();
}

void HitBox::addObject(Object* object)
{
	this->objects.push_back(object);
}

int HitBox::getNumElements()
{
	return (this->objects).size();
}

bool HitBox::hasInterceptedRay(Ray ray)
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
		return true;
	}

	w = ray.initialPoint - this->centerBase;
	double tInt = -(-this->direction.dot(w)) / (-this->direction.dot(ray.direction));

	if (tInt < 0)
	{
		pInt = ray.initialPoint + tInt * ray.direction;

		double insideInterval = pow((pInt - this->centerBase).norm(), 2);

		if (insideInterval >= 0 && insideInterval <= pow(this->radius, 2))
		{
			return true;
		}
	}

	w = ray.initialPoint - this->centerTop;
	tInt = -(this->direction.dot(w)) / (this->direction.dot(ray.direction));

	if (tInt < 0)
	{
		pInt = ray.initialPoint + tInt * ray.direction;

		double insideInterval = pow((pInt - this->centerTop).norm(), 2);

		if (insideInterval >= 0 && insideInterval <= pow(this->radius, 2))
		{
			return true;
		}
	}

	return false;
}