#include <Eigen>

#include "LightSource.h"

#ifndef PontualSource_H
#define PontualSource_H

/**
 * Classe para representar uma fonte de luz pontual.
 */
class PontualSource : public LightSource
{
public:
	/**
	 * Construtor da classe PontualSource.
	 * @param origin A posição da fonte de luz pontual.
	 * @param intensity A intensidade da luz emitida pela fonte pontual.
	 */
	PontualSource(Eigen::Vector3d origin, Eigen::Vector3d intensity);
};
	/**
	 * Obtém a direção da luz emitida pela fonte pontual em um determinado ponto.
	 * @param pInt O ponto de interesse.
	 * @return A direção da luz.
	 */
	Eigen::Vector3d getDirection(Eigen::Vector3d pInt);

	/**
	 * Calcula a intensidade da luz emitida pela fonte pontual em um determinado ponto.
	 * @param pInt O ponto de interesse.
	 * @param ray O raio que atinge o ponto de interesse.
	 * @param ptrIntesityAmbient Ponteiro para armazenar a intensidade da luz ambiente.
	 * @param ptrIntesityDifuse Ponteiro para armazenar a intensidade da luz difusa.
	 * @param ptrIntesitySpecular Ponteiro para armazenar a intensidade da luz especular.
	 * @param normal A normal do ponto de interesse.
	 * @param kAmbient O coeficiente de reflexão ambiente.
	 * @param kDif O coeficiente de reflexão difusa.
	 * @param kEsp O coeficiente de reflexão especular.
	 * @param specularIndex O índice de especularidade.
	 * @param shadowed Indica se o ponto de interesse está em sombra.
	 */
	void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
		Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed);

	/**
	 * Converte a posição da fonte pontual para o sistema de coordenadas da câmera.
	 * @param transformationMatrix A matriz de transformação da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif