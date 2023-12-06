#include "Ray.h"

/**
 * Construtor da classe Ray.
 * @param initialPoint Ponto inicial do raio.
 * @param direction Direção do raio.
 */
Ray::Ray(Eigen::Vector3d initialPoint, Eigen::Vector3d direction)
{
	this->initialPoint = initialPoint;
	this->direction = (initialPoint - direction).normalized();
}