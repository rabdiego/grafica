#include <Eigen>

#include "LightSource.h"

#ifndef PontualSource_H
#define PontualSource_H

/**
 * @brief Classe que representa uma fonte de luz pontual.
 */
class PontualSource : public LightSource
{
public:
	/**
	 * @brief Construtor da classe PontualSource.
	 * @param origin A posição de origem da fonte de luz.
	 * @param intensity A intensidade da fonte de luz.
	 */
	PontualSource(Eigen::Vector3d origin, Eigen::Vector3d intensity);

	/**
	 * @brief Obtém a direção da fonte de luz em relação a um ponto de interesse.
	 * @param pInt O ponto de interesse.
	 * @return A direção da fonte de luz.
	 */
	Eigen::Vector3d getDirection(Eigen::Vector3d pInt);

	/**
	 * @brief Calcula a intensidade da luz em um ponto de interesse.
	 * @param pInt O ponto de interesse.
	 * @param ray O raio que atinge o ponto de interesse.
	 * @param ptrIntesityAmbient Ponteiro para armazenar a intensidade da luz ambiente.
	 * @param ptrIntesityDifuse Ponteiro para armazenar a intensidade da luz difusa.
	 * @param ptrIntesitySpecular Ponteiro para armazenar a intensidade da luz especular.
	 * @param normal O vetor normal do ponto de interesse.
	 * @param kAmbient O coeficiente de reflexão ambiente.
	 * @param kDif O coeficiente de reflexão difusa.
	 * @param kEsp O coeficiente de reflexão especular.
	 * @param specularIndex O índice de especularidade.
	 * @param shadowed Indica se o ponto de interesse está sombreado.
	 */
	void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular,
		Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed);

	/**
	 * @brief Converte a posição da fonte de luz para o sistema de coordenadas da câmera.
	 * @param transformationMatrix A matriz de transformação da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif