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

Cone::Cone(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->radius = radius;
	this->height = height;
	this->centerBase = centerBase;
	this->direction = direction.normalized();
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;
	this->structure = 0;

	this->vertex = centerBase + height * this->direction;
	this->angle = atan(radius / height);
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

Eigen::Vector3d Cone::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
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

		int idx = 0;
		for (auto& source : sources)
		{
			source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
			idx++;
		}

		intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;
		return intesityEye;
	}
	else
	{
		return this->bottom->computeColor(tInt, ray, sources, shadows);
	}
}

void Cone::translate(double x, double y, double z)
{
	Eigen::Matrix4d m;
	m << 1, 0, 0, x,
		 0, 1, 0, y,
		 0, 0, 1, z,
		 0, 0, 0, 1;

	Eigen::Vector4d centerTop4;
	Eigen::Vector4d centerBase4;

	centerTop4 << this->vertex[0], this->vertex[1], this->vertex[2], 1;
	centerBase4 << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	centerTop4 = m * centerTop4;
	centerBase4 = m * centerBase4;

	this->vertex << centerTop4[0], centerTop4[1], centerTop4[2];
	this->centerBase << centerBase4[0], centerBase4[1], centerBase4[2];

	this->direction = (this->vertex - this->centerBase).normalized();
	this->bottom->translate(x, y, z);
}

void Cone::scale(double x, double y, double z)
{
	/*
	x -> Raio
	y -> Altura
	z -> Nada
	*/

	this->radius *= x;
	this->height *= y;

	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

void  Cone::rotateX(double angle)
{
	Eigen::Matrix4d rx;
	rx << 1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	newDir = rx * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

void  Cone::rotateY(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	newDir = rx * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

void  Cone::rotateZ(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	newDir = rx * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

void Cone::rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2)
{}

void Cone::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d centerTop4;
	Eigen::Vector4d centerBase4;

	centerTop4 << this->vertex[0], this->vertex[1], this->vertex[2], 1;
	centerBase4 << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	centerTop4 = transformationMatrix * centerTop4;
	centerBase4 = transformationMatrix * centerBase4;

	this->vertex << centerTop4[0], centerTop4[1], centerTop4[2];
	this->centerBase << centerBase4[0], centerBase4[1], centerBase4[2];

	this->direction = (this->vertex - this->centerBase).normalized();
	this->bottom->convertToCamera(transformationMatrix);
}