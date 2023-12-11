#include <vector>
#include "HitBox.h"

/**
 * @brief Construtor da classe HitBox.
 * 
 * @param radius O raio da HitBox.
 * @param centerBase O centro da base da HitBox.
 * @param centerTop O centro do topo da HitBox.
 */
HitBox::HitBox(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop)
{
	this->radius = radius;
	this->centerBase = centerBase;
	this->centerTop = centerTop;
	this->direction = (centerTop - centerBase).normalized();
	this->height = (centerTop - centerBase).norm();
}


/**
 * @brief Adiciona um objeto à HitBox.
 * 
 * @param object O objeto a ser adicionado.
 */
void HitBox::addObject(Object* object)
{
	this->objects.push_back(object);
}

/**
 * @brief Retorna o número de elementos da HitBox.
*/
int HitBox::getNumElements()
{
	return (int) (this->objects).size();
}

/**
 * @brief Verifica se o raio intercepta a HitBox.
 * 
 * @param ray O raio a ser verificado.
 */
bool HitBox::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d w = ray.initialPoint - this->centerBase;
	Eigen::Vector3d pInt(0, 0, 0);

	double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(this->direction), 2);
	double b = 2 * w.dot(ray.direction) - 2 * w.dot(this->direction) * ray.direction.dot(this->direction);
	double c = w.dot(w) - pow(w.dot(this->direction), 2) - pow(this->radius, 2);

	double delta = b * b - 4 * a * c;
	// se delta >= 0, o raio intercepta a hitbox
	if (a != 0 && delta >= 0)
	{
		return true;
	}

	
	w = ray.initialPoint - this->centerBase;
	double tInt = -(-this->direction.dot(w)) / (-this->direction.dot(ray.direction));

	// se tInt >= 0, o raio intercepta a hitbox a partir da base
	if (tInt < 0)
	{
		pInt = ray.initialPoint + tInt * ray.direction;

		double insideInterval = pow((pInt - this->centerBase).norm(), 2);
		// se o ponto de interseção está dentro da hitbox
		if (insideInterval >= 0 && insideInterval <= pow(this->radius, 2))
		{
			return true;
		}
	}

	w = ray.initialPoint - this->centerTop;
	tInt = -(this->direction.dot(w)) / (this->direction.dot(ray.direction));

	// se tInt >= 0, o raio intercepta a hitbox a partir do topo
	if (tInt < 0)
	{
		pInt = ray.initialPoint + tInt * ray.direction;

		double insideInterval = pow((pInt - this->centerTop).norm(), 2);

		if (insideInterval >= 0 && insideInterval <= pow(this->radius, 2))
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief Converte a matriz de transformação para a câmera.
 *
 * @param transformationMatrix A matriz de transformação a ser convertida.
 */
void HitBox::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d centerTop4;
	Eigen::Vector4d centerBase4;

	centerTop4 << this->centerTop[0], this->centerTop[1], this->centerTop[2], 1;
	centerBase4 << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	centerTop4 = transformationMatrix * centerTop4;
	centerBase4 = transformationMatrix * centerBase4;

	this->centerTop << centerTop4[0], centerTop4[1], centerTop4[2];
	this->centerBase << centerBase4[0], centerBase4[1], centerBase4[2];

	this->direction = (this->centerTop - this->centerBase).normalized();

	// converte cada objeto da hitbox para a câmera
	for (auto& o : this->objects)
	{
		o->convertToCamera(transformationMatrix);
	}
}