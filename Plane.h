#include "Object.h"
#include <SDL.h>

#ifndef Plane_H
#define Plane_H

/**
 * @brief Classe que representa um plano no espaço tridimensional.
 */
class Plane : public Object
{
public:
	Eigen::Vector3d normal; /**< Vetor normal ao plano */
	Eigen::Vector3d center; /**< Ponto central do plano */

	SDL_Surface* texture; /**< Textura do plano */

	Eigen::Vector3d axis1; /**< Primeiro eixo do plano */
	Eigen::Vector3d axis2; /**< Segundo eixo do plano */

	/**
	 * @brief Construtor da classe Plane.
	 * @param texture Textura do plano.
	 * @param normal Vetor normal ao plano.
	 * @param center Ponto central do plano.
	 * @param kAmbient Coeficiente de reflexão ambiente.
	 * @param kDif Coeficiente de reflexão difusa.
	 * @param kEsp Coeficiente de reflexão especular.
	 * @param specularIndex Índice de reflexão especular.
	 */
	Plane(SDL_Surface* texture, Eigen::Vector3d normal, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, double specularIndex);

	/**
	 * @brief Verifica se um raio intercepta o plano.
	 * @param ray Raio a ser verificado.
	 * @return Valor do parâmetro t no ponto de interseção, ou -1 se não houver interseção.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * @brief Calcula a cor do plano no ponto de interseção com um raio.
	 * @param tInt Valor do parâmetro t no ponto de interseção.
	 * @param ray Raio de interseção.
	 * @param sources Vetor de fontes de luz.
	 * @param shadows Vetor de booleanos indicando se há sombra no ponto de interseção.
	 * @return Cor do plano no ponto de interseção.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	/**
	 * @brief Translada o plano nas direções x, y e z.
	 * @param x Valor de translação no eixo x.
	 * @param y Valor de translação no eixo y.
	 * @param z Valor de translação no eixo z.
	 */
	void translate(double x, double y, double z);

	/**
	 * @brief Escala o plano nas direções x, y e z.
	 * @param x Valor de escala no eixo x.
	 * @param y Valor de escala no eixo y.
	 * @param z Valor de escala no eixo z.
	 */
	void scale(double x, double y, double z);

	/**
	 * @brief Rotaciona o plano em torno do eixo x.
	 * @param angle Ângulo de rotação em radianos.
	 */
	void rotateX(double angle);

	/**
	 * @brief Rotaciona o plano em torno do eixo y.
	 * @param angle Ângulo de rotação em radianos.
	 */
	void rotateY(double angle);

	/**
	 * @brief Rotaciona o plano em torno do eixo z.
	 * @param angle Ângulo de rotação em radianos.
	 */
	void rotateZ(double angle);

	/**
	 * @brief Converte as coordenadas do plano para o sistema de coordenadas da câmera.
	 * @param transformationMatrix Matriz de transformação para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif