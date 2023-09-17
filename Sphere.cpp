#include "Sphere.h"

Sphere::Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kDif, Eigen::Vector3d kEsp) {
	this->radius = radius;
	this->center = center;
	this->kDif = kDif;
	this->kEsp = kEsp;
}

Eigen::Vector3d Sphere::hasInterceptedRay(Ray ray, PontualSource source) {
	/*
	Método para checar se interceptou um raio
	*/
	Eigen::Vector3d w = ray.initialPoint - this->center;
	Eigen::Vector3d pInt(0, 0, 0);
	double b = 2 * w.dot(ray.direction);
	double c = w.dot(w) - this->radius * this->radius;
	Eigen::Vector3d intesityEye(0, 0, 0);

	double delta = b * b - 4 * c;

	if (delta >= 0) {
		double tInt = (sqrt(delta) - b) / 2;

		pInt = ray.initialPoint + tInt * ray.direction;

		Eigen::Vector3d normal = (pInt - this->center).normalized();
		Eigen::Vector3d directionToSource = (source.origin - this->center).normalized();

		Eigen::Vector3d intesityDifuse(0, 0, 0);
		Eigen::Vector3d intesitySpecular(0, 0, 0);

		Eigen::Vector3d directionToSourceReflex = (2 * directionToSource.dot(normal) * normal) - directionToSource;
		Eigen::Vector3d rayDirectionReflex = ray.direction;

		intesityDifuse = ((source.intensity).cwiseProduct(this->kDif)) * normal.dot(directionToSource);
		intesitySpecular = ((source.intensity).cwiseProduct(this->kEsp)) * pow(directionToSourceReflex.dot(rayDirectionReflex), this->specularIndex);

		intesityEye = intesityDifuse + intesitySpecular;
	}

	return intesityEye;
}