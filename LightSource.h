#include <Eigen>

#include "Ray.h"

#ifndef LightSource_H
#define LightSource_H

/**
 * Classe abstrata que representa uma fonte de luz.
 */
class LightSource
{
public:
	Eigen::Vector3d intensity; /**< Intensidade da luz. */
	Eigen::Vector3d origin; /**< Origem da luz. */

	/**
	 * Retorna a direção da luz em relação a um ponto específico.
	 * @param pInt O ponto em que a direção da luz será calculada.
	 * @return A direção da luz.
	 */
	virtual Eigen::Vector3d getDirection(Eigen::Vector3d pInt) = 0;

	/**
	 * Calcula a intensidade da luz em um ponto específico.
	 * @param pInt O ponto em que a intensidade da luz será calculada.
	 * @param ray O raio que atinge o ponto.
	 * @param ptrIntesityAmbient Ponteiro para armazenar a intensidade ambiente.
	 * @param ptrIntesityDifuse Ponteiro para armazenar a intensidade difusa.
	 * @param ptrIntesitySpecular Ponteiro para armazenar a intensidade especular.
	 * @param normal A normal do ponto.
	 * @param kAmbient O coeficiente de reflexão ambiente.
	 * @param kDif O coeficiente de reflexão difusa.
	 * @param kEsp O coeficiente de reflexão especular.
	 * @param specularIndex O índice especular.
	 * @param shadowed Indica se o ponto está sombreado.
	 */
	virtual void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular,
		Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed) = 0;

	/**
	 * Converte a posição da luz para o sistema de coordenadas da câmera.
	 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
	 */
	virtual void convertToCamera(Eigen::Matrix4d transformationMatrix) = 0;
};

#endif