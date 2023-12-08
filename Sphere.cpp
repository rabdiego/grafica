#include "Sphere.h"

// Construtor da classe Sphere.
Sphere::Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->radius = radius;
	this->center = center;
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;
}

// Verifica se um raio intercepta a esfera.
double Sphere::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d w = ray.initialPoint - this->center;

	double b = w.dot(ray.direction);
	double c = w.dot(w) - this->radius * this->radius;

	double delta = b * b - c;

	if (delta >= 0)
		return (sqrt(delta) - b);

	return 1;
}

// Calcula a cor do ponto de interseção da esfera.
Eigen::Vector3d Sphere::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	Eigen::Vector3d pInt(0, 0, 0);
	Eigen::Vector3d intesityEye(0, 0, 0);

	pInt = ray.initialPoint + tInt * ray.direction;

	Eigen::Vector3d intesityAmbient(0, 0, 0);
	Eigen::Vector3d intesityDifuse(0, 0, 0);
	Eigen::Vector3d intesitySpecular(0, 0, 0);
	Eigen::Vector3d singleDifuse;
	Eigen::Vector3d singleSpecular;
	Eigen::Vector3d normal = (pInt - this->center).normalized();

	int idx = 0;
	for (auto& source : sources)
	{
		source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
		idx++;
	}

	intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;

	return intesityEye;
}

// Translada a esfera nas direções x, y e z.
void Sphere::translate(double x, double y, double z)
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

// Escala a esfera nas direções x, y e z.
void  Sphere::scale(double x, double y, double z)
{
	this->radius *= x;
}


void  Sphere::rotateX(double angle)
{
	// nao tem sentido rotacionar uma esfera com cor "chapada"
}

void  Sphere::rotateY(double angle)
{
	// nao tem sentido rotacionar uma esfera com cor "chapada"
}
void  Sphere::rotateZ(double angle)
{
	// nao tem sentido rotacionar uma esfera com cor "chapada"
}

// Converte a esfera para o sistema de coordenadas da câmera.
void Sphere::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d center4;
	center4 << this->center[0], this->center[1], this->center[2], 1;

	center4 = transformationMatrix * center4;

	this->center << center4[0], center4[1], center4[2];
}
