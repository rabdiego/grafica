#include "TriangularFace.h"
#include <iostream>


// Construtor da classe TriangularFace.
TriangularFace::TriangularFace(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d v3, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->vertexes[0] = v1;
	this->vertexes[1] = v2;
	this->vertexes[2] = v3;

	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();

	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;
}

// Verifica se um raio intercepta a face triangular.
double TriangularFace::hasInterceptedRay(Ray ray)
{
	double tInt = -((ray.initialPoint - this->vertexes[0]).dot(this->normal)) / (ray.direction.dot(this->normal));
	Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

	double c1 = (((this->vertexes[2] - pInt).cross(this->vertexes[0] - pInt)).dot(this->normal)) / ((this->r1.cross(this->r2)).dot(this->normal));
	double c2 = (((this->vertexes[0] - pInt).cross(this->vertexes[1] - pInt)).dot(this->normal)) / ((this->r1.cross(this->r2)).dot(this->normal));
	double c3 = 1 - c1 - c2;

	if (c1 < 0 || c2 < 0 || c3 < 0)
	{
		return 1;
	}
	else
	{
		return tInt;
	}
}

// Calcula a cor do ponto de interseção da face triangular.
Eigen::Vector3d TriangularFace::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	Eigen::Vector3d intesityEye(0, 0, 0);

	Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

	Eigen::Vector3d intesityAmbient(0, 0, 0);
	Eigen::Vector3d intesityDifuse(0, 0, 0);
	Eigen::Vector3d intesitySpecular(0, 0, 0);
	Eigen::Vector3d singleDifuse;
	Eigen::Vector3d singleSpecular;
	Eigen::Vector3d normal = this->normal;

	int idx = 0;
	for (auto& source : sources)
	{
		source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
		idx++;
	}

	intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;

	return intesityEye;
}

// Translada a face triangular nos eixos x, y e z.
void TriangularFace::translate(double x, double y, double z)
{
	Eigen::Matrix4d m;
	m << 1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1;

	Eigen::Vector4d vertexes4[3];
	for (int i = 0; i < 3; i++)
	{
		vertexes4[i] << vertexes[i][0], vertexes[i][1], vertexes[i][2], 1;
		vertexes4[i] = m * vertexes4[i];
		vertexes[i] << vertexes4[i][0], vertexes4[i][1], vertexes4[i][2];
	}

	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();
}

// Escala a face triangular nos eixos x, y e z.
void TriangularFace::scale(double x, double y, double z)
{
	Eigen::MatrixXd m(4, 4);
	m << x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1;

	Eigen::MatrixXd n(4, 3);
	n << vertexes[0][0], vertexes[1][0], vertexes[2][0],
		vertexes[0][1], vertexes[1][1], vertexes[2][1],
		vertexes[0][2], vertexes[1][2], vertexes[2][2],
		1, 1, 1;

	auto mn = m * n;
	std::cout << mn << std::endl;

	for (int i = 0; i < 3; i++)
	{
		vertexes[i] << mn(0, i), mn(1, i), mn(2, i);
	}

	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();
}

// Rotaciona a face triangular no eixo x.
void TriangularFace::rotateX(double angle)
{
	Eigen::Matrix4d rx;
	rx << 1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d vertexes4[3];
	for (int i = 0; i < 3; i++)
	{
		vertexes4[i] << vertexes[i][0], vertexes[i][1], vertexes[i][2], 1;
		vertexes4[i] = rx * vertexes4[i];
		vertexes[i] << vertexes4[i][0], vertexes4[i][1], vertexes4[i][2];
	}

	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();
}

// Rotaciona a face triangular no eixo y.
void TriangularFace::rotateY(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d vertexes4[3];
	for (int i = 0; i < 3; i++)
	{
		vertexes4[i] << vertexes[i][0], vertexes[i][1], vertexes[i][2], 1;
		vertexes4[i] = rx * vertexes4[i];
		vertexes[i] << vertexes4[i][0], vertexes4[i][1], vertexes4[i][2];
	}

	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();
}


// Rotaciona a face triangular no eixo z.
void TriangularFace::rotateZ(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	Eigen::Vector4d vertexes4[3];
	for (int i = 0; i < 3; i++)
	{
		vertexes4[i] << vertexes[i][0], vertexes[i][1], vertexes[i][2], 1;
		vertexes4[i] = rx * vertexes4[i];
		vertexes[i] << vertexes4[i][0], vertexes4[i][1], vertexes4[i][2];
	}

	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();
}


// Converte a face triangular para o sistema de coordenadas da câmera.	
void TriangularFace::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d vertexes4[3];
	for (int i = 0; i < 3; i++)
	{
		vertexes4[i] << vertexes[i][0], vertexes[i][1], vertexes[i][2], 1;
		vertexes4[i] = transformationMatrix * vertexes4[i];
		vertexes[i] << vertexes4[i][0], vertexes4[i][1], vertexes4[i][2];
	}

	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();
}