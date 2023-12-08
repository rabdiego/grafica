#include "Camera.h"

/**
 * @brief Construtor da classe Camera.
 * 
 * @param position A posição da câmera.
 * @param lookAt O ponto para onde a câmera está olhando.
 * @param viewUp O vetor de orientação da câmera.
 */
Camera::Camera(Eigen::Vector3d position, Eigen::Vector3d lookAt, Eigen::Vector3d viewUp)
{
	this->position = position;
	this->lookAt = lookAt;
	this->viewUp = viewUp;

	// Calcula os vetores i, j e k.
	this->k = (position - lookAt).normalized();
	this->i = (viewUp.cross(k)).normalized();
	this->j = k.cross(i);

	// matriz de transformação da câmera.
	this->transformationMatrix << i[0], i[1], i[2], -(i.dot(position)),
								  j[0], j[1], j[2], -(j.dot(position)),
								  k[0], k[1], k[2], -(k.dot(position)),
									0,    0, 	0, 			1;	
}

/**
 * @brief Retorna a matriz de transformação da câmera.
 * 
 * @return A matriz de transformação da câmera.
 */
Eigen::Matrix4d Camera::getTransformationMatrix()
{
	return this->transformationMatrix;
}