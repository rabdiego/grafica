#include "TriangularFace.h"
#include <iostream>

/**
 * @brief Construtor da classe TriangularFace.
 * 
 * @param v1 Vetor 3D representando o primeiro vértice da face.
 * @param v2 Vetor 3D representando o segundo vértice da face.
 * @param v3 Vetor 3D representando o terceiro vértice da face.
 * @param kAmbient Vetor 3D representando o coeficiente de reflexão ambiente da face.
 * @param kDif Vetor 3D representando o coeficiente de reflexão difusa da face.
 * @param kEsp Vetor 3D representando o coeficiente de reflexão especular da face.
 * @param specularIndex Índice especular da face.
 */
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

/**
 * Verifica se um raio intercepta a face triangular e retorna o parâmetro de interseção.
 *
 * @param ray O raio a ser verificado.
 * @return O parâmetro de interseção do raio com a face triangular. Retorna 1 se não houver interseção.
 */
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

/**
 * @brief Calcula a cor da face triangular.
 *
 * Esta função calcula a cor da face triangular com base no parâmetro tInt.
 *
 * @param tInt O parâmetro tInt usado para calcular a cor da face triangular.
 * @param ray O raio usado para calcular a cor da face triangular.
 * @param sources Um vetor de ponteiros para as fontes de luz.
 * @param shadows Um vetor de booleanos indicando se há sombras na cena.
 * @return A cor calculada da face triangular.
 */
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

/**
 * Translada a face triangular pelos valores especificados em x, y e z.
 *
 * @param x O valor de translação no eixo x.
 * @param y O valor de translação no eixo y.
 * @param z O valor de translação no eixo z.
 */
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

/**
 * Rotaciona a face triangular em torno de um eixo arbitrário definido pelos pontos p1 e p2.
 *
 * @param angle O ângulo de rotação em radianos.
 * @param p1 O primeiro ponto que define o eixo de rotação.
 * @param p2 O segundo ponto que define o eixo de rotação.
 */
void TriangularFace::rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2)
{
	// vetor de rotacao
	Eigen::Vector3d V = p2 - p1;
	Eigen::Vector3d u = V.normalized();

	// componentes do vetor de rotacao
	double a = u[0];
	double b = u[1];
	double c = u[2];
	double d = sqrt(b * b + c * c);

	// matriz de transformacao
	Eigen::Matrix4d T1;
	Eigen::Matrix4d T2;
	Eigen::Matrix4d RX1;
	Eigen::Matrix4d RX2;
	Eigen::Matrix4d RY1;
	Eigen::Matrix4d RY2;
	Eigen::Matrix4d RZ;
	Eigen::Matrix4d M;

	// matrizes de translacao
	T1 << 1, 0, 0, -p1[0],
		0, 1, 0, -p1[1],
		0, 0, 1, -p1[2],
		0, 0, 0, 1;

	T2 << 1, 0, 0, p1[0],
		0, 1, 0, p1[1],
		0, 0, 1, p1[2],
		0, 0, 0, 1;

	// matrizes de rotacao
	RX1 << 1, 0, 0, 0,
		1, c / d, -b / d, 0,
		0, b / d, c / d, 0,
		0, 0, 0, 1;

	RX2 << 1, 0, 0, 0,
		1, c / d, b / d, 0,
		0, -b / d, c / d, 0,
		0, 0, 0, 1;

	RY1 << d, 0, -a, 0,
		0, 1, 0, 0,
		a, 0, d, 0,
		0, 0, 0, 1;

	RY2 << d, 0, a, 0,
		0, 1, 0, 0,
		-a, 0, d, 0,
		0, 0, 0, 1;

	RZ << cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	// matriz de rotacao em torno de um eixo arbitrario
	M = T2 * RX2 * RY2 * RZ * RY1 * RX1 * T1;

	// rotaciona os vertices
	Eigen::Vector4d vertexes4[3];
	for (int i = 0; i < 3; i++)
	{
		vertexes4[i] << vertexes[i][0], vertexes[i][1], vertexes[i][2], 1;
		vertexes4[i] = M * vertexes4[i];
		vertexes[i] << vertexes4[i][0], vertexes4[i][1], vertexes4[i][2];
	}

	// recalcula a normal
	this->r1 = this->vertexes[1] - this->vertexes[0];
	this->r2 = this->vertexes[2] - this->vertexes[1];
	this->normal = (r2.cross(r1)).normalized();
}

/**
 * Converte a face triangular para o sistema de coordenadas da câmera.
 *
 * @param transformationMatrix A matriz de transformação para o sistema de coordenadas da câmera.
 */
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