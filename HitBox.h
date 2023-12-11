#include <Eigen>
#include <vector>

#include "Ray.h"
#include "Object.h"

#ifndef HitBox_H
#define HitBox_H

/**
 * @brief Classe que representa uma hitbox.
 * 
 * A classe HitBox representa uma caixa de colisão tridimensional definida por um raio,
 * altura, coeficientes de reflexão ambiente, difusa e especular, e um índice especular.
 * 
*/
class HitBox
{
public:
	double radius;
	double height;
	Eigen::Vector3d centerBase;
	Eigen::Vector3d centerTop;
	Eigen::Vector3d direction;
	std::vector<Object*> objects;

	// Construtor da classe HitBox.
	HitBox(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop);

	// Adiciona um objeto à hitbox.
	void addObject(Object* object);

	// Verifica se o raio intercepta a hitbox.
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
	
	// Verifica se o raio intercepta a hitbox.
	bool hasInterceptedRay(Ray ray);
	int getNumElements();
};

#endif