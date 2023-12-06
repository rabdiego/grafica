#include <Eigen>

#ifndef Ray_H
#define Ray_H

/**
 * Classe para representar os raios de visão.
 */
class Ray
{
public:
	Eigen::Vector3d initialPoint; /**< Ponto inicial do raio. */
	Eigen::Vector3d direction;   /**< Direção do raio. */

	/**
	 * Construtor da classe Ray.
	 * @param initialPoint Ponto inicial do raio.
	 * @param direction Direção do raio.
	 */
	Ray(Eigen::Vector3d initialPoint, Eigen::Vector3d direction);
};

#endif