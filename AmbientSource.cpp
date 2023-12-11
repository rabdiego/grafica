#include "AmbientSource.h"


/**
 * Construtor da classe AmbientSource.
 *
 * @param intensity A intensidade da fonte de luz ambiente.
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
 * @param pInt O ponto de interseção entre o raio e a superfície.
 * @param ray O raio incidente.
 * @param ptrIntesityAmbient Um ponteiro para a intensidade ambiente atual.
 * @param ptrIntesityDifuse Um ponteiro para a intensidade difusa atual.
 * @param ptrIntesitySpecular Um ponteiro para a intensidade especular atual.
 * @param normal O vetor normal da superfície.
 * @param kAmbient O coeficiente de reflexão ambiente.
 * @param kDif O coeficiente de reflexão difusa.
 * @param kEsp O coeficiente de reflexão especular.
 * @param specularIndex O índice especular.
 * @param shadowed Indica se a superfície está sombreada.
 */
void AmbientSource::computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
	Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed)
{
	Eigen::Vector3d temp = ((this->intensity).cwiseProduct(kAmbient));


	Eigen::Vector3d intesityAmbient = *ptrIntesityAmbient;

	intesityAmbient[0] += temp[0] > 0 ? temp[0] : 0;
	intesityAmbient[1] += temp[1] > 0 ? temp[1] : 0;
	intesityAmbient[2] += temp[2] > 0 ? temp[2] : 0;

	*ptrIntesityAmbient = intesityAmbient;
}

void AmbientSource::convertToCamera(Eigen::Matrix4d transformationMatrix)
{

}
