#include "PontualSource.h"

/**
 * @brief Construtor da classe PontualSource.
 * 
 * @param origin A origem da fonte pontual.
 * @param intensity A intensidade da fonte pontual.
 */
PontualSource::PontualSource(Eigen::Vector3d origin, Eigen::Vector3d intensity)
{
	this->origin = origin;
	this->intensity = intensity;
}

/**
 * @brief Retorna a origem da fonte pontual.
*/
Eigen::Vector3d PontualSource::getDirection(Eigen::Vector3d pInt)
{
	return (pInt - this->origin).normalized();
}


/**
 * Calcula a intensidade da fonte pontual para um ponto de interseção.
 *
 * @param pInt O ponto de interseção.
 * @param ray O raio de interseção.
 * @param ptrIntesityAmbient Um ponteiro para armazenar a intensidade ambiente calculada.
 * @param ptrIntesityDifuse Um ponteiro para armazenar a intensidade difusa calculada.
 * @param ptrIntesitySpecular Um ponteiro para armazenar a intensidade especular calculada.
 * @param normal O vetor normal do ponto de interseção.
 * @param kAmbient O coeficiente de reflexão ambiente.
 * @param kDif O coeficiente de reflexão difusa.
 * @param kEsp O coeficiente de reflexão especular.
 * @param specularIndex O índice especular.
 * @param shadowed Indica se o ponto de interseção está sombreado.
 */
void PontualSource::computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
	Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed)
{
	// computa a intensidade se nao estiver sombreado
	if (shadowed == false)
	{
		Eigen::Vector3d directionToSource = (this->origin - pInt).normalized();
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


		Eigen::Vector3d intesityDifuse = *ptrIntesityDifuse;
		Eigen::Vector3d intesitySpecular = *ptrIntesitySpecular;

		// acumula a intensidade
		intesityDifuse[0] += tempDifuse[0] > 0 ? tempDifuse[0] : 0;
		intesityDifuse[1] += tempDifuse[1] > 0 ? tempDifuse[1] : 0;
		intesityDifuse[2] += tempDifuse[2] > 0 ? tempDifuse[2] : 0;

		intesitySpecular[0] += tempSpecular[0] > 0 ? tempSpecular[0] : 0;
		intesitySpecular[1] += tempSpecular[1] > 0 ? tempSpecular[1] : 0;
		intesitySpecular[2] += tempSpecular[2] > 0 ? tempSpecular[2] : 0;

		*ptrIntesityDifuse = intesityDifuse;
		*ptrIntesitySpecular = intesitySpecular;
	}
}

/**
 * @brief Converte a origem da fonte pontual para o sistema de coordenadas da câmera.
 *
 * @param transformationMatrix A matriz de transformação.
 */
void PontualSource::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d origin4;
	origin4 << origin[0], origin[1], origin[2], 1;
	origin4 = transformationMatrix * origin4;
	origin << origin4[0], origin4[1], origin4[2];
}