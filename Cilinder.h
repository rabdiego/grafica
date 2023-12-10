#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"
#include "CircularPlane.h"

#ifndef Cilinder_H
#define Cilinder_H


/**
 * @brief para representar um cilindro.
 * 
 * Com metodos herdados da classe Object:
 * Para verificar raio intercepta, computar cor, transformações e conversão para o sistema de coordenadas da câmera.
*/
class Cilinder : public Object
{
public:
	int structure;
	double radius;
	double height;
	Eigen::Vector3d centerBase;
	Eigen::Vector3d centerTop;
	Eigen::Vector3d direction;
	CircularPlane* bottom;
	CircularPlane* top;

	/** 
	 * Construtores da classse Cilinder 
	 * 
	 * 1º - Cilindro com base e topo
	 * 2º - Cilindro com base e direção
	*/
	Cilinder(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	Cilinder(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	double hasInterceptedRay(Ray ray);
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