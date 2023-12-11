#include "Object.h"
#include <SDL.h>

#ifndef Plane_H
#define Plane_H

/**
 * Classe pro plano.
*/
class Plane : public Object
{
public:
	Eigen::Vector3d normal;
	Eigen::Vector3d center;

	// textura
	SDL_Surface* texture;

	Eigen::Vector3d axis1;
	Eigen::Vector3d axis2;

	// Construtor do plano.
	Plane(SDL_Surface* texture, Eigen::Vector3d normal, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	// Metodos de intersecao e computar cor.
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	// metodos de transformacao
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2);

	//* Metodo para converter o objeto para o sistema de coordenadas da câmera
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif