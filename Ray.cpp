#include "Ray.h"

/**
 * @brief Classe que representa um raio no espaço tridimensional.
 * 
 * Um raio é definido por um ponto inicial e uma direção.
 */
Ray::Ray(Eigen::Vector3d initialPoint, Eigen::Vector3d direction)
{
	this->initialPoint = initialPoint;
	this->direction = (initialPoint - direction).normalized();
}