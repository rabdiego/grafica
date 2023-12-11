#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"

#ifndef Sphere_H
#define Sphere_H

/**
 * Classe que representa uma esfera no espaço tridimensional.
 */
class Sphere : public Object
{
public:
	/**
	 * Raio da esfera.
	 */
	double radius;
	
	/**
	 * Centro da esfera.
	 */
	Eigen::Vector3d center;

	/**
	 * Construtor da classe Sphere.
	 * @param radius O raio da esfera.
	 * @param center O centro da esfera.
	 * @param kAmbient O coeficiente de reflexão ambiente da esfera.
	 * @param kDif O coeficiente de reflexão difusa da esfera.
	 * @param kEsp O coeficiente de reflexão especular da esfera.
	 * @param specularIndex O índice especular da esfera.
	 */
	Sphere(double radius, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * Verifica se a esfera intercepta um raio.
	 * @param ray O raio a ser verificado.
	 * @return A distância do ponto de interseção ou -1 se não houver interseção.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * Calcula a cor do ponto de interseção da esfera.
	 * @param tInt A distância do ponto de interseção.
	 * @param ray O raio que intersectou a esfera.
	 * @param sources As fontes de luz no ambiente.
	 * @param shadows Um vetor de booleanos indicando se há sombra no ponto de interseção.
	 * @return A cor do ponto de interseção.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	// metodos de transformacao
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2);

	/**
	 * Converte a esfera para o sistema de coordenadas da camera.
	 * @param transformationMatrix A matriz de transformação da camera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif