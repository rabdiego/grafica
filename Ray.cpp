#include "Ray.h"

Ray::Ray(Eigen::Vector3d initialPoint, Eigen::Vector3d direction)
{
	this->initialPoint = initialPoint;
	this->direction = (initialPoint - direction).normalized();
}