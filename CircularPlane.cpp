#include "CircularPlane.h"

/**
 * @brief Construtor da classe CircularPlane.
 * 
 * @param normal Vetor normal ao plano.
 * @param center Vetor que representa o centro do plano.
 * @param radius Raio do plano circular.
 * @param kAmbient Coeficientes de reflexão ambiente do plano.
 * @param kDif Coeficientes de reflexão difusa do plano.
 * @param kEsp Coeficientes de reflexão especular do plano.
 * @param specularIndex Índice especular do plano.
 */
CircularPlane::CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
	: Plane(NULL, normal, center, kAmbient, kDif, kEsp, specularIndex)
{
	this->radius = radius;
}

/**
 * Cheque se o raio intercepta o plano circular
 * 
 * @param ray O raio a ser verificado.
 * @return O parametro t da interseção, ou -1 se não houver interseção.
 */
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

/**
 * Calcula a cor resultante da interseção entre um raio e um plano circular.
 * 
 * @param tInt O parâmetro t da interseção entre o raio e o plano circular.
 * @param ray O raio que intersecta o plano circular.
 * @param sources Um vetor contendo as fontes de luz no cenário.
 * @param shadows Um vetor de booleanos indicando se cada fonte de luz está bloqueada por sombras.
 * @return A cor resultante da interseção entre o raio e o plano circular.
 */
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


// Metodo para transladar o plano circular
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

// Metodo para escalar o plano circular
void CircularPlane::scale(double x, double y, double z)
{
	Eigen::Matrix4d m;
	m << x, 0, 0, 0,
		 0, y, 0, 0,
		 0, 0, z, 0,
		 0, 0, 0, 1;

	Eigen::Vector4d center4;
	center4 << this->center[0], this->center[1], this->center[2], 1;

	center4 = m * center4;

	this->center << center4[0], center4[1], center4[2];
}

// Metodo para rotacionar o plano circular em torno do eixo X
void  CircularPlane::rotateX(double angle)
{

}

// Metodo para rotacionar o plano circular em torno do eixo Y
void  CircularPlane::rotateY(double angle)
{

}


// Metodo para rotacionar o plano circular em torno do eixo Z
void  CircularPlane::rotateZ(double angle)
{

}

// Metodo para converter o plano circular para o sistema de coordenadas da camera
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