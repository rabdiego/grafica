#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"

#ifndef Object_H
#define Object_H

/**
 * @brief Classe para representar um objeto genérico.
*/
class Object
{
public:
	/**
	 * @brief Coeficientes de reflexão do objeto.
	 * 
	 * @param kAmbient coeficiente de reflexão ambiente
	 * @param kDif coeficiente de reflexão difusa
	 * @param kEsp coeficiente de reflexão especular
	*/
	Eigen::Vector3d kAmbient;
	Eigen::Vector3d kDif;
	Eigen::Vector3d kEsp;
	int specularIndex;

	//* metodos abstrato para verificar se o raio intercepta o objeto e computar a cor do objeto
	virtual double hasInterceptedRay(Ray ray) = 0;
	virtual Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows) = 0;

	//* Metodos para transformações Translação, Escala 
	virtual void translate(double x, double y, double z) = 0;
	virtual void scale(double x, double y, double z) = 0;

	//* Metodos para Rotação, em torno X, Y,Z e eixo arbitrário
	virtual void rotateX(double angle) = 0;
	virtual void rotateY(double angle) = 0;
	virtual void rotateZ(double angle) = 0;
	virtual void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2) = 0;

	//* Metodo para converter o objeto para o sistema de coordenadas da câmera
	virtual void convertToCamera(Eigen::Matrix4d transformationMatrix) = 0;
};

#endif