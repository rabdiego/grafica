#include "Object.h"

#ifndef TriangularFace_H
#define TriangularFace_H

/**
 * Classe TriangularFace representa uma face triangular em um objeto tridimensional.
 * Herda da classe Object.
 */
class TriangularFace : public Object
{
public:
	Eigen::Vector3d vertexes[3]; /**< Vetor de vértices da face triangular */
	Eigen::Vector3d normal; /**< Vetor normal da face triangular */

	Eigen::Vector3d r1; /**< Vetor r1 da face triangular */
	Eigen::Vector3d r2; /**< Vetor r2 da face triangular */

	/**
	 * Construtor da classe TriangularFace.
	 * @param v1 Vértice 1 da face triangular
	 * @param v2 Vértice 2 da face triangular
	 * @param v3 Vértice 3 da face triangular
	 * @param kAmbient Coeficiente de reflexão ambiente
	 * @param kDif Coeficiente de reflexão difusa
	 * @param kEsp Coeficiente de reflexão especular
	 * @param specularIndex Índice especular
	 */
	TriangularFace(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d v3, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * Verifica se um raio intercepta a face triangular.
	 * @param ray Raio a ser verificado
	 * @return Valor booleano indicando se houve interceptação
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * Calcula a cor da face triangular com base no raio interceptado.
	 * @param tInt Valor de interceptação do raio
	 * @param ray Raio interceptado
	 * @param sources Vetor de fontes de luz
	 * @param shadows Vetor de sombras
	 * @return Vetor de cor calculada
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	/**
	 * Translada a face triangular nos eixos x, y e z.
	 * @param x Valor de translação no eixo x
	 * @param y Valor de translação no eixo y
	 * @param z Valor de translação no eixo z
	 */
	void translate(double x, double y, double z);

	/**
	 * Escala a face triangular nos eixos x, y e z.
	 * @param x Valor de escala no eixo x
	 * @param y Valor de escala no eixo y
	 * @param z Valor de escala no eixo z
	 */
	void scale(double x, double y, double z);

	/**
	 * Rotaciona a face triangular no eixo x.
	 * @param angle Ângulo de rotação em radianos
	 */
	void rotateX(double angle);

	/**
	 * Rotaciona a face triangular no eixo y.
	 * @param angle Ângulo de rotação em radianos
	 */
	void rotateY(double angle);

	/**
	 * Rotaciona a face triangular no eixo z.
	 * @param angle Ângulo de rotação em radianos
	 */
	void rotateZ(double angle);

	/**
	 * Converte a face triangular para o sistema de coordenadas da câmera.
	 * @param transformationMatrix Matriz de transformação
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif