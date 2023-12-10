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
 * A classe Cone é derivada da classe Object e representa um cone tridimensional.
 * Ela possui propriedades como estrutura, raio, altura, ângulo, centro da base, vértice e direção.
 * Além disso, possui métodos para cálculo de interseção com um raio, cálculo de cor e transformações geométricas.
 */
class Cone : public Object
{
public:
	int structure; // Estrutura do cone
	double radius; // Raio da base do cone
	double height; // Altura do cone
	double angle; // Ângulo do cone
	Eigen::Vector3d centerBase; // Centro da base do cone
	Eigen::Vector3d vertex; // Vértice do cone
	Eigen::Vector3d direction; // Direção do cone
	CircularPlane* bottom; // Plano circular da base do cone

	/**
	 * @brief Construtor da classe Cone.
	 * 
	 * 1º: angulo e vertice passado por parâmetro
	 * 2º: altura e direção passados por parâmetro 
	 */
	Cone(double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	Cone(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	/**
	 * @brief Verifica se o cone intercepta um raio.
	 */
	double hasInterceptedRay(Ray ray);

	/**
	 * @brief Calcula a cor do cone no ponto de interseção com um raio.
	 */
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	// Métodos de transformação 
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);

	/**
	 * @brief Rotaciona o cone em torno de um eixo arbitrário definido por dois pontos.
	 */
	void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2);

	/**
	 * @brief Converte as coordenadas do cone para o sistema de coordenadas da câmera.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif