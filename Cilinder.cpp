#include <vector>
#include "Cilinder.h"

/**
 * @brief Construtor da classe Cilinder.
 * 
 * @param radius O raio do cilindro.
 * @param centerBase O centro da base do cilindro.
 * @param centerTop O centro do topo do cilindro.
 * @param kAmbient O coeficiente de reflexão ambiente do cilindro.
 * @param kDif O coeficiente de reflexão difusa do cilindro.
 * @param kEsp O coeficiente de reflexão especular do cilindro.
 * @param specularIndex O índice especular do cilindro.
 */
Cilinder::Cilinder(double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->radius = radius;
	this->centerBase = centerBase;
	this->centerTop = centerTop;
	this->direction = (centerTop - centerBase).normalized();
	this->height = (centerTop - centerBase).norm();
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->structure = 0;
}

Cilinder::Cilinder(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->radius = radius;
	this->height = height;
	this->centerBase = centerBase;
	this->direction = direction.normalized();

	this->centerTop = centerBase + height * this->direction;

	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->structure = 0;
}

/**
 * Calcula o ponto de intersecção entre o raio e o cilindro.
 *
 * @param ray The ray to intersect with the cylinder.
 * @return The parameter value t at which the intersection occurs. Returns 1 if no intersection is found.
 */
double Cilinder::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d w = ray.initialPoint - this->centerBase;
	Eigen::Vector3d pInt(0, 0, 0);

	double returnValue = 1;

	double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(this->direction), 2);
	double b = 2 * w.dot(ray.direction) - 2 * w.dot(this->direction) * ray.direction.dot(this->direction);
	double c = w.dot(w) - pow(w.dot(this->direction), 2) - pow(this->radius, 2);

	double delta = b * b - 4 * a * c;
	// Se delta < 0, não há intersecção
	if (a != 0 && delta >= 0)
	{
		double tInt = (sqrt(delta) - b) / (2 * a);

		pInt = ray.initialPoint + tInt * ray.direction;
		double insideInterval = (pInt - this->centerBase).dot(this->direction);

		// Verifica se o ponto de intersecção está dentro do intervalo do cilindro
		if (insideInterval >= 0 && insideInterval <= this->height)
		{
			returnValue = tInt;
			this->structure = 0;
		}

	}
	// Verifica se o raio intercepta a base superior(e inferior) do cilindro
	double top = this->top->hasInterceptedRay(ray);
	double bottom = this->bottom->hasInterceptedRay(ray);

	double minimum = -INFINITY;
	int idx = -1;
	std::vector <double> distances = { returnValue, top, bottom };
	
	// Verifica qual é o ponto de intersecção mais próximo
	for (int i = 0; i < 3; i++)
	{
		// Se o ponto de intersecção for válido e menor que o mínimo atual
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
 * Função que calcular a cor de um cilindro.
 * 
 * @param tInt O valor de t da interseção do raio com o cilindro.
 * @param ray O raio que intersecta o cilindro.
 * @param sources Um vetor de ponteiros para as fontes de luz.
 * @param shadows Um vetor de booleanos indicando se há sombras nas fontes de luz.
 * 
 * @return A cor calculada para o cilindro.
 */
Eigen::Vector3d Cilinder::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{	
	// computa a cor do cilindro
	if (this->structure == 0)
	{
		Eigen::Vector3d intesityEye(0, 0, 0);
		Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

		Eigen::Vector3d intesityAmbient(0, 0, 0);
		Eigen::Vector3d intesityDifuse(0, 0, 0);
		Eigen::Vector3d intesitySpecular(0, 0, 0);
		Eigen::Vector3d singleDifuse;
		Eigen::Vector3d singleSpecular;

		Eigen::Vector3d v = pInt - this->centerBase;
		Eigen::Vector3d projection = (v.dot(this->direction)) * this->direction;
		Eigen::Vector3d normal = (v - projection).normalized();

		int idx = 0;
		for (auto& source : sources)
		{
			source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
			idx++;
		}

		intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;
		return intesityEye;
	}
	// computa a cor da tampa superior
	else if (this->structure == 1)
	{
		return this->top->computeColor(tInt, ray, sources, shadows);
	}
	// computa a cor da tampa inferior
	else
	{
		return this->bottom->computeColor(tInt, ray, sources, shadows);
	}
}


/**
 *  Função de translação do cilindro.	
 
*/
void Cilinder::translate(double x, double y, double z)
{
	Eigen::Matrix4d m;
	m << 1, 0, 0, x,
		 0, 1, 0, y,
	  	 0, 0, 1, z,
		 0, 0, 0, 1;

	Eigen::Vector4d centerTop4;
	Eigen::Vector4d centerBase4;

	// Adiciona uma quarta coordenada para realizar a translação
	centerTop4 << this->centerTop[0], this->centerTop[1], this->centerTop[2], 1;
	centerBase4 << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	centerTop4 = m * centerTop4;
	centerBase4 = m * centerBase4;

	// Atualiza os valores do centro do topo e da base
	this->centerTop << centerTop4[0], centerTop4[1], centerTop4[2];
	this->centerBase << centerBase4[0], centerBase4[1], centerBase4[2];

	// Atualiza a direção do cilindro
	this->direction = (this->centerTop - this->centerBase).normalized();
	this->bottom->translate(x, y, z);
	this->top->translate(x, y, z);
}

void  Cilinder::scale(double x, double y, double z)
{
	/*
	x -> Raio
	y -> Altura
	z -> Nada
	*/

	this->radius *= x;
	this->height *= y;

	// Atualiza o centro do topo e da base
	this->centerTop = this->centerBase + this->height * this->direction;
	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}


/**
 * Rotaciona o cilindro em torno do eixo X por um determinado ângulo.
 * 
 * @param angle O ângulo de rotação em radianos.
 */
void  Cilinder::rotateX(double angle)
{
	Eigen::Matrix4d rx;
	rx << 1, 0, 0, 0,
		  0, cos(angle), -sin(angle), 0,
		  0, sin(angle), cos(angle), 0,
		  0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	newDir = rx * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	this->centerTop = this->centerBase + this->height * this->direction;
	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

/**
 * Rotaciona o cilindro em torno do eixo Y por um determinado ângulo.
 * 
 * @param angle O ângulo de rotação em radianos.
 */
void  Cilinder::rotateY(double angle)
{
	Eigen::Matrix4d ry;
	ry << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	newDir = ry * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	this->centerTop = this->centerBase + this->height * this->direction;
	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

/**
 * Rotaciona o cilindro em torno do eixo Z por um determinado ângulo.
 * 
 * @param angle O ângulo de rotação em radianos.
 */
void  Cilinder::rotateZ(double angle)
{
	Eigen::Matrix4d rz;
	rz << cos(angle), -sin(angle), 0, 0,
		  sin(angle), cos(angle), 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	newDir = rz * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	this->centerTop = this->centerBase + this->height * this->direction;
	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

// Converte o cilindro para o sistema de coordenadas da câmera
void Cilinder::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d centerTop;
	Eigen::Vector4d centerBase;

	centerTop << this->centerTop[0], this->centerTop[1], this->centerTop[2], 1;
	centerBase << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	centerTop = transformationMatrix * centerTop;
	centerBase = transformationMatrix * centerBase;

	this->centerTop << centerTop[0], centerTop[1], centerTop[2];
	this->centerBase << centerBase[0], centerBase[1], centerBase[2];

	this->direction = (this->centerTop - this->centerBase).normalized();
	this->bottom->convertToCamera(transformationMatrix);
	this->top->convertToCamera(transformationMatrix);
}