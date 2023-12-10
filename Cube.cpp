#include <iostream>
#include "Cube.h"

/**
 * @brief Construtor da classe Cube.
 * 
 * A classe Cube representa um cubo tridimensional definido por um vértice principal,
 * largura, altura, profundidade, coeficientes de reflexão ambiente, difusa e especular,
 * e um índice especular.
 * 
 * @param mainVertex O vértice principal do cubo.
 * @param width A largura do cubo.
 * @param height A altura do cubo.
 * @param depth A profundidade do cubo.
 * @param kAmbient O coeficiente de reflexão ambiente do cubo.
 * @param kDif O coeficiente de reflexão difusa do cubo.
 * @param kEsp O coeficiente de reflexão especular do cubo.
 * @param specularIndex O índice especular do cubo.
 */
Cube::Cube(Eigen::Vector3d mainVertex, double width, double height, double depth, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->structure = 0;
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	this->center = mainVertex + Eigen::Vector3d(width, height, -depth) / 2;

	Eigen::Vector3d a = mainVertex + Eigen::Vector3d(width, 0, 0);
	Eigen::Vector3d b = mainVertex + Eigen::Vector3d(width, height, 0);
	Eigen::Vector3d c = mainVertex + Eigen::Vector3d(0, height, 0);
	Eigen::Vector3d d = mainVertex;
	Eigen::Vector3d e = mainVertex + Eigen::Vector3d(width, 0, -depth);
	Eigen::Vector3d f = mainVertex + Eigen::Vector3d(width, height, -depth);
	Eigen::Vector3d g = mainVertex + Eigen::Vector3d(0, height, -depth);
	Eigen::Vector3d h = mainVertex + Eigen::Vector3d(0, 0, -depth);

	// Faces do cubo, totalizando 12 faces.

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

/**
 * Verifica se o raio intercepta o cubo e retorna a distância até o ponto de interseção mais próximo.
 * 
 * @param ray O raio a ser verificado.
 * @return A distância até o ponto de interseção mais próximo. Retorna 1 se não houver interseção.
 */
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

/**
 * Calcula a cor do cubo.
 *
 * @param tInt O valor de tInt.
 * @param ray O raio.
 * @param sources As fontes de luz.
 * @param shadows As sombras.
 * @return A cor calculada.
 */
Eigen::Vector3d Cube::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	// calculo da cor de cada face do cubo
	return faces[structure]->computeColor(tInt, ray, sources, shadows);
}


void Cube::translate(double x, double y, double z)
{
	// translada cada face do cubo
	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate(x, y, z);
	}
}

void Cube::scale(double x, double y, double z)
{
	// aplica escala em cada face do cubo
	for (int i = 0; i < 12; i++)
	{
		faces[i]->scale(x, y, z);
	}
}

void Cube::rotateX(double angle)
{
	// Translada o cubo para a origem, rotaciona e translada de volta para a posição original.
	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate
		(
			-this->center[0],
			-this->center[1],
			-this->center[2]
		);
	}

	// Rotaciona cada face do cubo
	for (int i = 0; i < 12; i++)
	{
		faces[i]->rotateX(angle);
	}

	// Translada o cubo de volta para a posição original
	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate
		(
			this->center[0],
			this->center[1],
			this->center[2]
		);
	}
}

// O mesmo que o rotateX
void Cube::rotateY(double angle)
{
	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate
		(
			-this->center[0],
			-this->center[1],
			-this->center[2]
		);
	}

	for (int i = 0; i < 12; i++)
	{
		faces[i]->rotateY(angle);
	}

	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate
		(
			this->center[0],
			this->center[1],
			this->center[2]
		);
	}
}

// O mesmo que o rotateX
void Cube::rotateZ(double angle)
{
	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate
		(
			-this->center[0],
			-this->center[1],
			-this->center[2]
		);
	}

	for (int i = 0; i < 12; i++)
	{
		faces[i]->rotateZ(angle);
	}

	for (int i = 0; i < 12; i++)
	{
		faces[i]->translate
		(
			this->center[0],
			this->center[1],
			this->center[2]
		);
	}
}

void Cube::rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2)
{
	// rotaciona cada face do cubo
	for (int i = 0; i < 12; i++)
	{
		faces[i]->rotateAny(angle, p1, p2);
	}
}

// Converte as coordenadas do cubo para o sistema de coordenadas da câmera.
void Cube::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	// converte cada face do cubo
	for (int i = 0; i < 12; i++)
	{
		faces[i]->convertToCamera(transformationMatrix);
	}
}