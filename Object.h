#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"

#ifndef Object_H
#define Object_H

/**
 * @brief Classe abstrata que representa um objeto gráfico.
 * 
 * A classe Object define as propriedades e métodos básicos que um objeto gráfico deve ter.
 * Ela possui propriedades para os coeficientes de reflexão de luz ambiente, difusa e especular,
 * bem como um índice especular. Além disso, ela define métodos virtuais puros para verificar
 * se um raio intercepta o objeto, calcular a cor do objeto em um ponto de interseção e realizar
 * transformações geométricas no objeto.
 */
class Object
{
public:
	Eigen::Vector3d kAmbient; /**< Coeficiente de reflexão de luz ambiente */
	Eigen::Vector3d kDif; /**< Coeficiente de reflexão de luz difusa */
	Eigen::Vector3d kEsp; /**< Coeficiente de reflexão de luz especular */
	int specularIndex; /**< Índice especular */

	/**
	 * @brief Verifica se um raio intercepta o objeto.
	 * 
	 * @param ray O raio a ser verificado.
	 * @return double O valor do parâmetro t no ponto de interseção, ou um valor negativo caso não haja interseção.
	 */
	virtual double hasInterceptedRay(Ray ray) = 0;

	/**
	 * @brief Calcula a cor do objeto em um ponto de interseção.
	 * 
	 * @param tInt O valor do parâmetro t no ponto de interseção.
	 * @param ray O raio que intersectou o objeto.
	 * @param sources Vetor de fontes de luz.
	 * @param shadows Vetor de booleanos indicando se há sombra no ponto de interseção.
	 * @return Eigen::Vector3d A cor do objeto no ponto de interseção.
	 */
	virtual Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows) = 0;

	/**
	 * @brief Translada o objeto nas direções x, y e z.
	 * 
	 * @param x O valor de translação no eixo x.
	 * @param y O valor de translação no eixo y.
	 * @param z O valor de translação no eixo z.
	 */
	virtual void translate(double x, double y, double z) = 0;

	/**
	 * @brief Escala o objeto nas direções x, y e z.
	 * 
	 * @param x O valor de escala no eixo x.
	 * @param y O valor de escala no eixo y.
	 * @param z O valor de escala no eixo z.
	 */
	virtual void scale(double x, double y, double z) = 0;

	/**
	 * @brief Rotaciona o objeto no eixo x.
	 * 
	 * @param angle O ângulo de rotação em radianos.
	 */
	virtual void rotateX(double angle) = 0;

	/**
	 * @brief Rotaciona o objeto no eixo y.
	 * 
	 * @param angle O ângulo de rotação em radianos.
	 */
	virtual void rotateY(double angle) = 0;

	/**
	 * @brief Rotaciona o objeto no eixo z.
	 * 
	 * @param angle O ângulo de rotação em radianos.
	 */
	virtual void rotateZ(double angle) = 0;

	/**
	 * @brief Converte as coordenadas do objeto para o sistema de coordenadas da câmera.
	 * 
	 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
	 */
	virtual void convertToCamera(Eigen::Matrix4d transformationMatrix) = 0;
};

#endif