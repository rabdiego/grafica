#include "Sphere.h"

Sphere::Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex) {
	this->radius = radius;
	this->center = center;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = 2 * specularIndex + 1;
}

Eigen::Vector4d Sphere::hasInterceptedRay(Ray ray, PontualSource source) {
	/*
	Método para checar se interceptou um raio
	*/
	Eigen::Vector3d w = ray.initialPoint - this->center;
	Eigen::Vector3d pInt(0, 0, 0);
	double b = w.dot(ray.direction);
	double c = w.dot(w) - this->radius * this->radius;
	Eigen::Vector3d intesityEye(0, 0, 0);
	Eigen::Vector4d intensityAndDistance(0, 0, 0, 1);

	double delta = b * b - c;

	if (delta >= 0) {
		double tInt = (sqrt(delta) - b);

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

		for (int i = 0; i < 3; i++) {
			intensityAndDistance[i] = intesityEye[i];
		}
		intensityAndDistance[3] = tInt;
	}

	return intensityAndDistance;
}