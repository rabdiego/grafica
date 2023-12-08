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
 * @param ptrIntensityAmbient Ponteiro para a intensidade da luz ambiente.
 * @param ptrIntensityDifuse Ponteiro para a intensidade da luz difusa.
 * @param ptrIntensitySpecular Ponteiro para a intensidade da luz especular.
 * @param normal Vetor normal à superfície.
 * @param kAmbient Coeficiente de reflexão ambiente.
 * @param kDif Coeficiente de reflexão difusa.
 * @param kEsp Coeficiente de reflexão especular.
 * @param specularIndex Índice de especularidade.
 * @param shadowed Indica se a superfície está em sombra.
 */
void AmbientSource::computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntensityAmbient, Eigen::Vector3d* ptrIntensityDifuse, Eigen::Vector3d* ptrIntensitySpecular, 
	Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed)
{
	
	Eigen::Vector3d temp = ((this->intensity).cwiseProduct(kAmbient));


	Eigen::Vector3d intensityAmbient = *ptrIntensityAmbient;

	// Soma as intensidades
	intensityAmbient[0] += temp[0] > 0 ? temp[0] : 0;
	intensityAmbient[1] += temp[1] > 0 ? temp[1] : 0;
	intensityAmbient[2] += temp[2] > 0 ? temp[2] : 0;

	*ptrIntensityAmbient = intensityAmbient;
}

void AmbientSource::convertToCamera(Eigen::Matrix4d transformationMatrix)
{	
	// Converte a origem para coordenadas de câmera
	Eigen::Vector4d origin4(this->origin[0], this->origin[1], this->origin[2], 1);

	// Multiplica a origem pela matriz de transformação
	origin4 = transformationMatrix * origin4;

	// Atualiza a origem
	this->origin = Eigen::Vector3d(origin4[0], origin4[1], origin4[2]);
}
