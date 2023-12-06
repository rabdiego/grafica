#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"

#ifndef Sphere_H
#define Sphere_H

/**
 * Classe para representar uma esfera.
 */
class Sphere : public Object
{
public:
	double radius; // raio da esfera
	Eigen::Vector3d center; // centro da esfera

	/**
	 * Construtor da classe Sphere.
	 * @param radius O raio da esfera.
	 * @param center O centro da esfera.
	 * @param kAmbient O coeficiente de reflexão ambiente da esfera.
	 * @param kDif O coeficiente de reflexão difusa da esfera.
	 * @param kEsp O coeficiente de reflexão especular da esfera.
	 * @param specularIndex O índice de especularidade da esfera.
	 */
	Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * Verifica se um raio intercepta a esfera.
	 * @param ray O raio a ser verificado.
	 * @return A distância do ponto de interseção mais próximo ou -1 se não houver interseção.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * Calcula a cor do ponto de interseção da esfera.
	 * @param tInt A distância do ponto de interseção.
	 * @param ray O raio que intersectou a esfera.
	 * @param sources As fontes de luz no ambiente.
	 * @param shadows Um vetor de booleanos indicando se cada fonte de luz está bloqueada por uma sombra.
	 * @return A cor do ponto de interseção.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	/**
	 * Translada a esfera nas direções x, y e z.
	 * @param x A quantidade a ser transladada no eixo x.
	 * @param y A quantidade a ser transladada no eixo y.
	 * @param z A quantidade a ser transladada no eixo z.
	 */
	void translate(double x, double y, double z);

	/**
	 * Escala a esfera nas direções x, y e z.
	 * @param x O fator de escala no eixo x.
	 * @param y O fator de escala no eixo y.
	 * @param z O fator de escala no eixo z.
	 */
	void scale(double x, double y, double z);

	/**
	 * Rotaciona a esfera em torno do eixo x.
	 * @param angle O ângulo de rotação em radianos.
	 */
	void rotateX(double angle);

	/**
	 * Rotaciona a esfera em torno do eixo y.
	 * @param angle O ângulo de rotação em radianos.
	 */
	void rotateY(double angle);

	/**
	 * Rotaciona a esfera em torno do eixo z.
	 * @param angle O ângulo de rotação em radianos.
	 */
	void rotateZ(double angle);

	/**
	 * Converte a esfera para o sistema de coordenadas da câmera.
	 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif