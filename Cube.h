#include "TriangularFace.h"

#ifndef Cube_H
#define Cube_H

/**
 * @brief Classe que representa um cubo tridimensional.
 */
class Cube : public Object
{
public:
	TriangularFace* faces[12]; /**< Array de faces triangulares do cubo. */
	int structure; /**< Estrutura do cubo. */
	Eigen::Vector3d center; /**< Centro do cubo. */

	/**
	 * @brief Construtor da classe Cube.
	 * @param mainVertex O vértice principal do cubo.
	 * @param width A largura do cubo.
	 * @param height A altura do cubo.
	 * @param depth A profundidade do cubo.
	 * @param kAmbient O coeficiente de reflexão ambiente do cubo.
	 * @param kDif O coeficiente de reflexão difusa do cubo.
	 * @param kEsp O coeficiente de reflexão especular do cubo.
	 * @param specularIndex O índice de especularidade do cubo.
	 */
	Cube(Eigen::Vector3d mainVertex, double width, double height, double depth, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * @brief Verifica se o raio intercepta o cubo.
	 * @param ray O raio a ser verificado.
	 * @return O valor do parâmetro t de interseção, ou -1 se não houver interseção.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * @brief Calcula a cor do cubo no ponto de interseção com o raio.
	 * @param tInt O valor do parâmetro t de interseção.
	 * @param ray O raio de interseção.
	 * @param sources O vetor de fontes de luz.
	 * @param shadows O vetor de booleanos indicando se há sombra no ponto de interseção.
	 * @return A cor do cubo no ponto de interseção.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);


	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2);

	/**
	 * @brief Converte o cubo para o sistema de coordenadas da câmera.
	 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif