#include <Eigen>
#include <vector>

#include "Ray.h"
#include "Object.h"

#ifndef HitBox_H
#define HitBox_H

/**
 * Classe para representar uma caixa de colisão.
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

	/**
	 * Construtor da classe HitBox.
	 * @param radius O raio da caixa de colisão.
	 * @param centerBase O centro da base da caixa de colisão.
	 * @param centerTop O centro do topo da caixa de colisão.
	 */
	HitBox(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop);

	/**
	 * Adiciona um objeto à caixa de colisão.
	 * @param object O objeto a ser adicionado.
	 */
	void addObject(Object* object);

	/**
	 * Converte a caixa de colisão para o sistema de coordenadas da câmera.
	 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);

	/**
	 * Verifica se a caixa de colisão interceptou um raio.
	 * @param ray O raio a ser verificado.
	 * @return true se houve interceptação, false caso contrário.
	 */
	bool hasInterceptedRay(Ray ray);

	/**
	 * Obtém o número de elementos na caixa de colisão.
	 * @return O número de elementos na caixa de colisão.
	 */
	int getNumElements();
};

#endif