#include <Eigen>

#ifndef Camera_H
#define Camera_H

/**
 * Classe que representa uma câmera
 */
class Camera
{
public:
	Eigen::Vector3d position; // < Posição da câmera
	Eigen::Vector3d lookAt;   // < Ponto para onde a câmera está olhando
	Eigen::Vector3d viewUp;   // < Vetor de orientação da câmera

	Eigen::Vector3d i;  // < Vetor i do sistema de coordenadas da câmera
	Eigen::Vector3d j;  // < Vetor j do sistema de coordenadas da câmera
	Eigen::Vector3d k;  // < Vetor k do sistema de coordenadas da câmera

	Eigen::Matrix4d transformationMatrix; // < Matriz de transformação da câmera

	/**
	 * Construtor da classe Camera.
	 * @param position Posição da câmera
	 * @param lookAt Ponto para onde a câmera está olhando
	 * @param viewUp Vetor de orientação da câmera
	 */
	Camera(Eigen::Vector3d position, Eigen::Vector3d lookAt, Eigen::Vector3d viewUp);

	//Obtém a matriz de transformação da câmera
	Eigen::Matrix4d getTransformationMatrix();
};

#endif