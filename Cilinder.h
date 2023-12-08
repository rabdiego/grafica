#include <Eigen>
#include <vector>

#include "Ray.h"
#include "LightSource.h"
#include "Object.h"
#include "CircularPlane.h"

#ifndef Cilinder_H
#define Cilinder_H

class Cilinder : public Object
{
	/*
	Classe para representar uma Cilindro
	*/
public:
	int structure; // Variável para armazenar a estrutura do cilindro
	double radius; // Raio do cilindro
	double height; // Altura do cilindro
	Eigen::Vector3d centerBase; // Centro da base do cilindro
	Eigen::Vector3d centerTop; // Centro do topo do cilindro
	Eigen::Vector3d direction; // Direção do cilindro
	CircularPlane* bottom; // Ponteiro para o plano circular da base do cilindro
	CircularPlane* top; // Ponteiro para o plano circular do topo do cilindro

	// Construtor para cilindro com base e topo definidos
	Cilinder(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	// Construtor para cilindro com base, altura e direção definidos
	Cilinder(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	// Função para verificar se o raio intercepta o cilindro
	double hasInterceptedRay(Ray ray);

	// Função para calcular a cor do cilindro no ponto de interseção
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	// Funções para realizar transformações no cilindro
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);

	// Função para converter o cilindro para o sistema de coordenadas da câmera
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif