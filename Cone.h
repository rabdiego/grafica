#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"
#include "CircularPlane.h"

#ifndef Cone_H
#define Cone_H

/**
 * @brief Classe que representa um cone tridimensional.
 * 
 * A classe Cone é uma subclasse da classe Object e representa um cone tridimensional.
 * Ela possui propriedades como estrutura, raio, altura, ângulo, centro da base, vértice, direção e plano circular inferior.
 * Além disso, a classe possui métodos para realizar transformações geométricas no cone e calcular a cor do cone em um determinado ponto.
 */
class Cone : public Object
{
public:
	int structure; // Estrutura do cone
	double radius; // Raio do cone
	double height; // Altura do cone
	double angle; // Ângulo do cone
	Eigen::Vector3d centerBase; // Centro da base do cone
	Eigen::Vector3d vertex; // Vértice do cone
	Eigen::Vector3d direction; // Direção do cone
	CircularPlane* bottom; // Plano circular inferior do cone

	/**
	 * @brief Construtor da classe Cone.
	 * 
	 * @param angle O ângulo do cone.
	 * @param centerBase O centro da base do cone.
	 * @param vertex O vértice do cone.
	 * @param kAmbient O coeficiente de reflexão ambiente do cone.
	 * @param kDif O coeficiente de reflexão difusa do cone.
	 * @param kEsp O coeficiente de reflexão especular do cone.
	 * @param specularIndex O índice de especularidade do cone.
	 */
	Cone(double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * @brief Construtor da classe Cone.
	 * 
	 * @param radius O raio do cone.
	 * @param height A altura do cone.
	 * @param centerBase O centro da base do cone.
	 * @param direction A direção do cone.
	 * @param kAmbient O coeficiente de reflexão ambiente do cone.
	 * @param kDif O coeficiente de reflexão difusa do cone.
	 * @param kEsp O coeficiente de reflexão especular do cone.
	 * @param specularIndex O índice de especularidade do cone.
	 */
	Cone(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * @brief Verifica se um raio intercepta o cone.
	 * 
	 * @param ray O raio a ser verificado.
	 * @return O valor do parâmetro t no ponto de interseção, ou -1 se não houver interseção.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * @brief Calcula a cor do cone em um determinado ponto.
	 * 
	 * @param tInt O valor do parâmetro t no ponto de interseção.
	 * @param ray O raio que intersectou o cone.
	 * @param sources Um vetor de fontes de luz.
	 * @param shadows Um vetor de booleanos indicando se há sombra no ponto de interseção.
	 * @return A cor do cone no ponto de interseção.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	/**
	 * @brief Translada o cone nas direções x, y e z.
	 * 
	 * @param x O valor de translação no eixo x.
	 * @param y O valor de translação no eixo y.
	 * @param z O valor de translação no eixo z.
	 */
	void translate(double x, double y, double z);

	/**
	 * @brief Escala o cone nas direções x, y e z.
	 * 
	 * @param x O valor de escala no eixo x.
	 * @param y O valor de escala no eixo y.
	 * @param z O valor de escala no eixo z.
	 */
	void scale(double x, double y, double z);

	/**
	 * @brief Rotaciona o cone em torno do eixo x.
	 * 
	 * @param angle O ângulo de rotação em graus.
	 */
	void rotateX(double angle);

	/**
	 * @brief Rotaciona o cone em torno do eixo y.
	 * 
	 * @param angle O ângulo de rotação em graus.
	 */
	void rotateY(double angle);

	/**
	 * @brief Rotaciona o cone em torno do eixo z.
	 * 
	 * @param angle O ângulo de rotação em graus.
	 */
	void rotateZ(double angle);

	/**
	 * @brief Converte as coordenadas do cone para o sistema de coordenadas da câmera.
	 * 
	 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif