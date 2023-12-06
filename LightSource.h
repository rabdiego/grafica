#include <Eigen>

#include "Ray.h"

#ifndef LightSource_H
#define LightSource_H

/**
 * @brief Classe abstrata que representa uma fonte de luz.
 */
class LightSource
{
public:
	Eigen::Vector3d intensity; /**< Intensidade da luz */
	Eigen::Vector3d origin; /**< Origem da luz */

	/**
	 * @brief Retorna a direção da luz em relação a um ponto de interesse.
	 * @param pInt Ponto de interesse
	 * @return Direção da luz
	 */
	virtual Eigen::Vector3d getDirection(Eigen::Vector3d pInt) = 0;

	/**
	 * @brief Calcula a intensidade da luz em um ponto de interesse.
	 * @param pInt Ponto de interesse
	 * @param ray Raio de interseção
	 * @param ptrIntesityAmbient Ponteiro para a intensidade da luz ambiente
	 * @param ptrIntesityDifuse Ponteiro para a intensidade da luz difusa
	 * @param ptrIntesitySpecular Ponteiro para a intensidade da luz especular
	 * @param normal Vetor normal da superfície
	 * @param kAmbient Coeficiente de reflexão ambiente
	 * @param kDif Coeficiente de reflexão difusa
	 * @param kEsp Coeficiente de reflexão especular
	 * @param specularIndex Índice de especularidade
	 * @param shadowed Indica se o ponto está em sombra
	 */
	virtual void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular,
								  Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed) = 0;

	/**
	 * @brief Converte a posição da luz para o sistema de coordenadas da câmera.
	 * @param transformationMatrix Matriz de transformação
	 */
	virtual void convertToCamera(Eigen::Matrix4d transformationMatrix) = 0;
};

#endif