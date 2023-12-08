#include "PontualSource.h"


/**
 * @brief Construtor da classe PontualSource.
 * @param origin A posição da fonte de luz pontual.
 * @param intensity A intensidade da luz emitida pela fonte pontual.
 */
PontualSource::PontualSource(Eigen::Vector3d origin, Eigen::Vector3d intensity)
{
	this->origin = origin;
	this->intensity = intensity;
}

/**
 * @brief Obtém a direção da luz emitida pela fonte pontual em um determinado ponto. 
 */
Eigen::Vector3d PontualSource::getDirection(Eigen::Vector3d pInt)
{
	return (pInt - this->origin).normalized();
}

/**
 * @brief Calcula a intensidade da luz emitida pela fonte pontual em um determinado ponto.
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
void PontualSource::computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
	Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed)
{
	if (shadowed == false)
	{
		Eigen::Vector3d directionToSource = (this->origin - pInt).normalized();
		if (directionToSource.dot(normal) > 0)
		{
			Eigen::Vector3d directionToSourceReflex = (2 * directionToSource.dot(normal) * normal) - directionToSource;
			Eigen::Vector3d rayDirectionReflex = ray.direction;

			Eigen::Vector3d tempDifuse = ((this->intensity).cwiseProduct(kDif)) * normal.dot(directionToSource);
			double lr = directionToSourceReflex.dot(rayDirectionReflex);

			Eigen::Vector3d tempSpecular;

			if (lr >= 0)
			{
				tempSpecular = ((this->intensity).cwiseProduct(kEsp)) * pow(directionToSourceReflex.dot(rayDirectionReflex), specularIndex);
			}
			else
			{
				tempSpecular = Eigen::Vector3d(0, 0, 0);
			}

			// Monkey code

			Eigen::Vector3d intesityDifuse = *ptrIntesityDifuse;
			Eigen::Vector3d intesitySpecular = *ptrIntesitySpecular;

			if (tempDifuse[0] > 0)
			{
				intesityDifuse[0] += tempDifuse[0];
			}
			if (tempDifuse[1] > 0)
			{
				intesityDifuse[1] += tempDifuse[1];
			}
			if (tempDifuse[2] > 0)
			{
				intesityDifuse[2] += tempDifuse[2];
			}

			if (tempSpecular[0] > 0)
			{
				intesitySpecular[0] += tempSpecular[0];
			}
			if (tempSpecular[1] > 0)
			{
				intesitySpecular[1] += tempSpecular[1];
			}
			if (tempSpecular[2] > 0)
			{
				intesitySpecular[2] += tempSpecular[2];
			}

			*ptrIntesityDifuse = intesityDifuse;
			*ptrIntesitySpecular = intesitySpecular;
		}
	}
}

/**
 * @brief Converte a posição da fonte pontual para o sistema de coordenadas da câmera.
 * @param transformationMatrix A matriz de transformação da câmera.
 */
void PontualSource::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d origin4;
	origin4 << origin[0], origin[1], origin[2], 1;
	origin4 = transformationMatrix * origin4;
	origin << origin4[0], origin4[1], origin4[2];
}