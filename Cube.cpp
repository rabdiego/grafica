/*
#include "TriangularFace.h"

#ifndef Cube_H
#define Cube_H

class Cube : public Object
{
public:
	TriangularFace faces[12];

	Cube(Eigen::Vector3d mainVertex, double height, double width, double depth, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);
	double hasInterceptedRay(Ray ray);
	Eigen::Vector3d computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows);

	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
};

#endif
*/

#include "Cube.h"

Cube::Cube(Eigen::Vector3d mainVertex, double width, double height, double depth, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->structure = 0;
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	Eigen::Vector3d a = mainVertex + Eigen::Vector3d(width, 0, 0);
	Eigen::Vector3d b = mainVertex + Eigen::Vector3d(width, height, 0);
	Eigen::Vector3d c = mainVertex + Eigen::Vector3d(0, height, 0);
	Eigen::Vector3d d = mainVertex;
	Eigen::Vector3d e = mainVertex + Eigen::Vector3d(width, 0, -depth);
	Eigen::Vector3d f = mainVertex + Eigen::Vector3d(width, height, -depth);
	Eigen::Vector3d g = mainVertex + Eigen::Vector3d(0, height, -depth);
	Eigen::Vector3d h = mainVertex + Eigen::Vector3d(0, 0, -depth);

	// Frente embaixo
	faces[0] = new TriangularFace
	(
		c,
		a,
		d,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Frente acima
	faces[1] = new TriangularFace
	(
		b,
		a,
		c,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Fundo embaixo
	faces[2] = new TriangularFace
	(
		f,
		h,
		e,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Fundo acima
	faces[3] = new TriangularFace
	(
		g,
		h,
		f,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Topo embaixo
	faces[4] = new TriangularFace
	(
		g,
		b,
		c,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Topo acima
	faces[5] = new TriangularFace
	(
		f,
		b,
		g,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Base embaixo
	faces[6] = new TriangularFace
	(
		d,
		e,
		h,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Base acima
	faces[7] = new TriangularFace
	(
		a,
		e,
		d,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Esquerda embaixo
	faces[8] = new TriangularFace
	(
		g,
		d,
		h,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Esquerda acima
	faces[9] = new TriangularFace
	(
		c,
		d,
		g,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Direita embaixo
	faces[10] = new TriangularFace
	(
		b,
		e,
		a,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);

	// Direita acima
	faces[11] = new TriangularFace
	(
		f,
		e,
		b,
		this->kAmbient,
		this->kDif,
		this->kEsp,
		this->specularIndex
	);
}

double Cube::hasInterceptedRay(Ray ray)
{
	double distances[12];

	for (int i = 0; i < 12; i++)
	{
		distances[i] = faces[i]->hasInterceptedRay(ray);
	}

	double minimum = -INFINITY;
	int idx = -1;

	for (int i = 0; i < 12; i++)
	{
		if (distances[i] < 0 && distances[i] > minimum)
		{
			minimum = distances[i];
			idx = i;
			this->structure = i;
		}
	}

	if (idx != -1)
		return distances[idx];

	return 1;
}

Eigen::Vector3d Cube::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	return faces[structure]->computeColor(tInt, ray, sources, shadows);
}

void Cube::translate(double x, double y, double z)
{
	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate(x, y, z);
	}
}

void Cube::scale(double x, double y, double z)
{
	for (int i = 0; i < 12; i++)
	{
		faces[i]->scale(x, y, z);
	}
}

void Cube::rotateX(double angle)
{
	for (int i = 0; i < 12; i++)
	{
		faces[i]->rotateX(angle);
	}
}

void Cube::rotateY(double angle)
{
	for (int i = 0; i < 12; i++)
	{
		faces[i]->rotateY(angle);
	}
}

void Cube::rotateZ(double angle)
{
	for (int i = 0; i < 12; i++)
	{
		faces[i]->rotateZ(angle);
	}
}