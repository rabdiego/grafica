#include <Eigen>

#ifndef Ray_H
#define Ray_H

/**
 * @brief Classe que representa um raio.
 *
*/
class Ray
{
public:
	Eigen::Vector3d initialPoint;
	Eigen::Vector3d direction;

	Ray(Eigen::Vector3d initialPoint, Eigen::Vector3d direction);
};

#endif