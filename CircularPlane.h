#include "Plane.h"

#ifndef CircularPlane_H
#define CircularPlane_H

/**
 * Classe CircularPlane representa um plano circular no espaço tridimensional.
 * Esta classe herda da classe Plane.
 */
class CircularPlane : public Plane
{
public:
	double radius;

	/**
	 * Construtor da classe CircularPlane.
	 * @param normal Vetor normal ao plano circular.
	 * @param center Vetor representando o centro do plano circular.
	 * @param radius Raio do plano circular.
	 * @param kAmbient Coeficientes de reflexão ambiente do material do plano circular.
	 * @param kDif Coeficientes de reflexão difusa do material do plano circular.
	 * @param kEsp Coeficientes de reflexão especular do material do plano circular.
	 * @param specularIndex Índice de especularidade do material do plano circular.
	 */
	CircularPlane(Eigen::Vector3d normal, Eigen::Vector3d center, double radius, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * Verifica se um raio intercepta o plano circular.
	 * @param ray Raio a ser verificado.
	 * @return Valor double representando o parâmetro t de interseção do raio com o plano circular.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * Calcula a cor do plano circular no ponto de interseção com um raio.
	 * @param tInt Parâmetro t de interseção do raio com o plano circular.
	 * @param ray Raio de interseção.
	 * @param sources Vetor de fontes de luz.
	 * @param shadows Vetor de booleanos indicando se há sombra no ponto de interseção.
	 * @return Vetor representando a cor do plano circular no ponto de interseção.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);


	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2);

	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif