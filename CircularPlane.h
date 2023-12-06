#include "Plane.h"

#ifndef CircularPlane_H
#define CircularPlane_H

/**
 * @brief Classe que representa um plano circular.
 * 
 * A classe CircularPlane herda da classe Plane e adiciona a funcionalidade de um plano circular.
 * Possui métodos para calcular a interseção com um raio, computar a cor do ponto de interseção e realizar transformações geométricas.
 */
class CircularPlane : public Plane
{
public:
	double radius; /**< Raio do plano circular. */

	/**
	 * @brief Construtor da classe CircularPlane.
	 * 
	 * @param normal Vetor normal ao plano.
	 * @param center Centro do plano circular.
	 * @param radius Raio do plano circular.
	 * @param kAmbient Coeficientes de reflexão ambiente.
	 * @param kDif Coeficientes de reflexão difusa.
	 * @param kEsp Coeficientes de reflexão especular.
	 * @param specularIndex Índice de reflexão especular.
	 */
	CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * @brief Verifica se o raio intercepta o plano circular.
	 * 
	 * @param ray Raio a ser verificado.
	 * @return Valor de t da interseção, ou -1 se não houver interseção.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * @brief Calcula a cor do ponto de interseção com o plano circular.
	 * 
	 * @param tInt Valor de t da interseção.
	 * @param ray Raio de interseção.
	 * @param sources Vetor de fontes de luz.
	 * @param shadows Vetor de booleanos indicando se há sombra no ponto de interseção.
	 * @return Cor do ponto de interseção.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	/**
	 * @brief Translada o plano circular.
	 * 
	 * @param x Valor de translação no eixo x.
	 * @param y Valor de translação no eixo y.
	 * @param z Valor de translação no eixo z.
	 */
	void translate(double x, double y, double z);

	/**
	 * @brief Escala o plano circular.
	 * 
	 * @param x Valor de escala no eixo x.
	 * @param y Valor de escala no eixo y.
	 * @param z Valor de escala no eixo z.
	 */
	void scale(double x, double y, double z);

	/**
	 * @brief Rotaciona o plano circular em torno do eixo x.
	 * 
	 * @param angle Ângulo de rotação em radianos.
	 */
	void rotateX(double angle);

	/**
	 * @brief Rotaciona o plano circular em torno do eixo y.
	 * 
	 * @param angle Ângulo de rotação em radianos.
	 */
	void rotateY(double angle);

	/**
	 * @brief Rotaciona o plano circular em torno do eixo z.
	 * 
	 * @param angle Ângulo de rotação em radianos.
	 */
	void rotateZ(double angle);

	/**
	 * @brief Converte o plano circular para o sistema de coordenadas da câmera.
	 * 
	 * @param transformationMatrix Matriz de transformação.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif