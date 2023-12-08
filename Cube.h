#include "TriangularFace.h"

#ifndef Cube_H
#define Cube_H

/**
 * @brief Classe que representa um cubo tridimensional.
 * 
 * A classe Cube herda da classe Object e representa um cubo tridimensional no espaço.
 * Possui métodos para realizar transformações geométricas, calcular interseção com um raio
 * e computar a cor do cubo com base em fontes de luz e sombras.
 */
class Cube : public Object
{
public:
	TriangularFace* faces[12]; // Array de faces triangulares do cubo
	int structure; // Estrutura do cubo
	Eigen::Vector3d center; // Centro do cubo

	/**
	 * @brief Construtor da classe Cube.
	 * 
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
	 * @brief Verifica se o cubo intercepta um raio.
	 * 
	 * @param ray O raio a ser verificado.
	 * @return O valor de t da interseção, ou -1 se não houver interseção.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * @brief Calcula a cor do cubo com base na interseção com um raio, fontes de luz e sombras.
	 * 
	 * @param tInt O valor de t da interseção.
	 * @param ray O raio que intersectou o cubo.
	 * @param sources As fontes de luz no ambiente.
	 * @param shadows Vetor de booleanos indicando se há sombras para cada fonte de luz.
	 * @return A cor resultante do cubo.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	/**
	 * @brief Translada o cubo nas direções x, y e z.
	 * 
	 * @param x O valor de translação no eixo x.
	 * @param y O valor de translação no eixo y.
	 * @param z O valor de translação no eixo z.
	 */
	void translate(double x, double y, double z);

	/**
	 * @brief Escala o cubo nas direções x, y e z.
	 * 
	 * @param x O valor de escala no eixo x.
	 * @param y O valor de escala no eixo y.
	 * @param z O valor de escala no eixo z.
	 */
	void scale(double x, double y, double z);

	/**
	 * @brief Rotaciona o cubo em torno do eixo x.
	 * 
	 * @param angle O ângulo de rotação em radianos.
	 */
	void rotateX(double angle);

	/**
	 * @brief Rotaciona o cubo em torno do eixo y.
	 * 
	 * @param angle O ângulo de rotação em radianos.
	 */
	void rotateY(double angle);

	/**
	 * @brief Rotaciona o cubo em torno do eixo z.
	 * 
	 * @param angle O ângulo de rotação em radianos.
	 */
	void rotateZ(double angle);

	/**
	 * @brief Converte as coordenadas do cubo para o sistema de coordenadas da câmera.
	 * 
	 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif