#include "AmbientSource.h"

/**
 * @brief Construtor da classe AmbientSource.
 * 
 * @param intensity Intensidade da fonte de luz ambiente.
 */
AmbientSource::AmbientSource(Eigen::Vector3d intensity)
{
	this->intensity = intensity;
	this->origin = Eigen::Vector3d(0, 0, 0);
}

Eigen::Vector3d AmbientSource::getDirection(Eigen::Vector3d pInt)
{
	Eigen::Vector3d placeholder(0, 0, 0);
	return placeholder;
}

/**
 * Calcula a intensidade da fonte de luz ambiente.
 * 
 * @param pInt Ponto de interseção entre o raio e a superfície.
 * @param ray Raio incidente.
 * @param ptrIntesityAmbient Ponteiro para a intensidade da luz ambiente.
 * @param ptrIntesityDifuse Ponteiro para a intensidade da luz difusa.
 * @param ptrIntesitySpecular Ponteiro para a intensidade da luz especular.
 * @param normal Vetor normal à superfície.
 * @param kAmbient Coeficiente de reflexão ambiente.
 * @param kDif Coeficiente de reflexão difusa.
 * @param kEsp Coeficiente de reflexão especular.
 * @param specularIndex Índice de especularidade.
 * @param shadowed Indica se a superfície está em sombra.
 */
void AmbientSource::computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
	Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed)
{
	Eigen::Vector3d temp = ((this->intensity).cwiseProduct(kAmbient));

	// Monkey code

	Eigen::Vector3d intesityAmbient = *ptrIntesityAmbient;

	if (temp[0] > 0)
	{
		intesityAmbient[0] += temp[0];
	}
	if (temp[1] > 0)
	{
		intesityAmbient[1] += temp[1];
	}
	if (temp[2] > 0)
	{
		intesityAmbient[2] += temp[2];
	}

	*ptrIntesityAmbient = intesityAmbient;
}

void AmbientSource::convertToCamera(Eigen::Matrix4d transformationMatrix)
{

}
