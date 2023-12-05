#include "CircularPlane.h"

CircularPlane::CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
	: Plane(NULL, normal, center, kAmbient, kDif, kEsp, specularIndex)
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

void CircularPlane::translate(double x, double y, double z)
{
	Eigen::Matrix4d m;
	m << 1, 0, 0, x,
		 0, 1, 0, y,
		 0, 0, 1, z,
		 0, 0, 0, 1;

	Eigen::Vector4d center4;
	center4 << this->center[0], this->center[1], this->center[2], 1;

	center4 = m * center4;

	this->center << center4[0], center4[1], center4[2];
}

void CircularPlane::scale(double x, double y, double z)
{

}

void  CircularPlane::rotateX(double angle)
{

}

void  CircularPlane::rotateY(double angle)
{

}

void  CircularPlane::rotateZ(double angle)
{

}

void CircularPlane::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d center4, normal4;
	center4 << this->center[0], this->center[1], this->center[2], 1;
	normal4 << this->normal[0], this->normal[1], this->normal[2], 0;

	center4 = transformationMatrix * center4;
	normal4 = transformationMatrix * normal4;

	this->center << center4[0], center4[1], center4[2];
	this->normal << normal4[0], normal4[1], normal4[2];
}