#include <Eigen>

#ifndef Camera_H
#define Camera_H

/**
 * Classe que representa uma câmera.
 */
class Camera
{
public:
	Eigen::Vector3d position;
	Eigen::Vector3d lookAt;
	Eigen::Vector3d viewUp;

	Eigen::Vector3d i;
	Eigen::Vector3d j;
	Eigen::Vector3d k;

	Eigen::Matrix4d transformationMatrix;

	// construtor e get da matriz de transformação
	Camera(Eigen::Vector3d position, Eigen::Vector3d lookAt, Eigen::Vector3d viewUp);
	Eigen::Matrix4d getTransformationMatrix();
};

#endif