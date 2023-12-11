#include "CircularPlane.h"


/**
 * @brief Construtor da classe CircularPlane.
 * 
 * @param normal Vetor normal ao plano circular.
 * @param center Vetor representando o centro do plano circular.
 * @param radius Raio do plano circular.
 * @param kAmbient Vetor representando o coeficiente de reflexão ambiente do plano circular.
 * @param kDif Vetor representando o coeficiente de reflexão difusa do plano circular.
 * @param kEsp Vetor representando o coeficiente de reflexão especular do plano circular.
 * @param specularIndex Índice de reflexão especular do plano circular.
 */
CircularPlane::CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
	: Plane(NULL, normal, center, kAmbient, kDif, kEsp, specularIndex)
{
	this->radius = radius;
}

double CircularPlane::hasInterceptedRay(Ray ray)
{
	// Verifica se o raio intercepta o plano infinito.
	Eigen::Vector3d w = ray.initialPoint - this->center;
	double tInt = -(this->normal.dot(w)) / (this->normal.dot(ray.direction));

	// Se o raio não intercepta o plano infinito, retorna 1.
	Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

	// Verifica se o ponto de interseção está dentro do círculo.
	double insideInterval = pow((pInt - this->center).norm(), 2);
	if (tInt < 0 && insideInterval >= 0 && insideInterval <= pow(this->radius, 2))
	{
		return tInt;
	}

	return 1;
}

/**
 * Calcula a cor resultante para um ponto de interseção em um plano circular.
 *
 * @param tInt O parâmetro de interseção do raio com o plano circular.
 * @param ray O raio que intersecta o plano circular.
 * @param sources Um vetor contendo as fontes de luz no cenário.
 * @param shadows Um vetor de booleanos indicando se cada fonte de luz está bloqueada por sombras.
 * @return A cor resultante para o ponto de interseção no plano circular.
 */
Eigen::Vector3d CircularPlane::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	Eigen::Vector3d intesityEye(0, 0, 0);
	Eigen::Vector3d intesityAmbient(0, 0, 0);
	Eigen::Vector3d intesityDifuse(0, 0, 0);
	Eigen::Vector3d intesitySpecular(0, 0, 0);
	Eigen::Vector3d normal = this->normal;
	Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

	int idx = 0;

	// Calcula a cor resultante para cada fonte de luz.
	for (auto& source : sources)
	{
		source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
		idx++;
	}

	intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;

	return intesityEye;
}


/**
 * Translates the CircularPlane by the specified amount in the x, y, and z directions.
 *
 * @param x The amount to translate in the x direction.
 * @param y The amount to translate in the y direction.
 * @param z The amount to translate in the z direction.
 */
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

void CircularPlane::rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2)
{}

// Converte as coordenadas do cone para o sistema de coordenadas da câmera.
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