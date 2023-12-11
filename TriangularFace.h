#include "Object.h"

#ifndef TriangularFace_H
#define TriangularFace_H

/**
 * Classe que representa uma face triangular em um objeto gráfico.
 */
class TriangularFace : public Object
{
public:
	Eigen::Vector3d vertexes[3]; /**< Vetores que representam os vértices da face. */
	Eigen::Vector3d normal; /**< Vetor normal à face. */

	Eigen::Vector3d r1; /**< Vetor r1. */
	Eigen::Vector3d r2; /**< Vetor r2. */

	/**
	 * Construtor da classe TriangularFace.
	 * @param v1 Vetor representando o primeiro vértice da face.
	 * @param v2 Vetor representando o segundo vértice da face.
	 * @param v3 Vetor representando o terceiro vértice da face.
	 * @param kAmbient Vetor representando o coeficiente de reflexão ambiente.
	 * @param kDif Vetor representando o coeficiente de reflexão difusa.
	 * @param kEsp Vetor representando o coeficiente de reflexão especular.
	 * @param specularIndex Índice especular da face.
	 */
	TriangularFace(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d v3, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * Verifica se a face intercepta um raio.
	 * @param ray Raio a ser verificado.
	 * @return Valor indicando se houve interceptação (1) ou não (0).
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * Calcula a cor da face.
	 * @param tInt Valor de interceptação do raio com a face.
	 * @param ray Raio que interceptou a face.
	 * @param sources Vetor de fontes de luz.
	 * @param shadows Vetor de booleanos indicando se há sombra ou não.
	 * @return Vetor representando a cor da face.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	// metodo de transformacao
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2);

	/**
	 * Converte a face para o sistema de coordenadas da câmera.
	 * @param transformationMatrix Matriz de transformação para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif