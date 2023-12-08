#include "Cone.h"
#include <iostream>

/**
 * @brief Construtor da classe Cone.
 * 
 * @param angle O ângulo do cone em radianos.
 * @param centerBase O centro da base do cone.
 * @param vertex O vértice do cone.
 * @param kAmbient O coeficiente de reflexão ambiente do cone.
 * @param kDif O coeficiente de reflexão difusa do cone.
 * @param kEsp O coeficiente de reflexão especular do cone.
 * @param specularIndex O índice de especularidade do cone.
 */
Cone::Cone(double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->structure = 0;
	this->angle = angle;
	this->centerBase = centerBase;
	this->vertex = vertex;
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	// calculando valor da altura atraves do vertice(vetor) e do centro da base(vetor)
	this->height = (vertex - centerBase).norm();
	// calculando o raio atraves da altura e da tangente do angulo
	this->radius = this->height * tan(this->angle);
	this->direction = (vertex - centerBase).normalized();
	// base do cone, feita com um plano circular
	this->bottom = new CircularPlane(-this->direction, centerBase, radius, kAmbient, kDif, kEsp, specularIndex);
}

/**
 * @brief Construtor da classe Cone.
 * 
 * @param radius O raio do cone.
 * @param height A altura do cone.
 * @param centerBase O centro da base do cone.
 * @param direction A direção do cone.
 * @param kAmbient O coeficiente de reflexão ambiente do cone.
 * @param kDif O coeficiente de reflexão difusa do cone.
 * @param kEsp O coeficiente de reflexão especular do cone.
 * @param specularIndex O índice de especularidade do cone.
 */
Cone::Cone(double radius, double height, Eigen::Vector3d centerBase, Eigen::Vector3d direction, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)
{
	this->radius = radius;
	this->height = height;
	this->centerBase = centerBase;
	this->direction = direction.normalized();
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;
	this->structure = 0;

	// calculando o vertice do cone
	this->vertex = centerBase + height * this->direction;
	// calculando o angulo do cone pela arcotangente do raio pela altura
	this->angle = atan(radius / height);
	this->bottom = new CircularPlane(-this->direction, centerBase, radius, kAmbient, kDif, kEsp, specularIndex);
}

/**
 * Verifica se um raio intercepta o cone e retorna a distância do ponto de interseção ao ponto inicial do raio.
 * 
 * @param ray O raio a ser verificado.
 * @return A distância do ponto de interseção ao ponto inicial do raio. Retorna 1 se não houver interseção.
 */
double Cone::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d v = (this->vertex - ray.initialPoint);
	Eigen::Vector3d pInt(0, 0, 0);

	double returnValue = 1;
	// calculando os coeficientes da equacao de segundo grau
	double a = pow((ray.direction).dot(this->direction), 2) - ((ray.direction).dot(ray.direction)) * pow(cos(this->angle), 2);
	double b = v.dot(ray.direction) * pow(cos(this->angle), 2) - (v.dot(this->direction)) * ((ray.direction).dot(this->direction));
	double c = pow(v.dot(this->direction), 2) - v.dot(v) * pow(cos(this->angle), 2);

	double delta = b * b - a * c;

	// se o delta for maior ou igual a zero, o raio intercepta o cone
	if (a != 0 && delta >= 0)
	{
		double tInt = (-sqrt(delta) - b) / a;
		pInt = ray.initialPoint + tInt * ray.direction;
		double insideInterval = ((pInt - this->centerBase).dot(this->direction)) / this->direction.norm();

		// se o ponto de intersecao estiver dentro do intervalo da altura do cone, retorna o valor de tInt
		if (insideInterval >= 0 && insideInterval <= this->height)
		{
			returnValue = tInt;
		}
	}

	double base = this->bottom->hasInterceptedRay(ray);

	std::vector <double> distances = { returnValue, base };

	double minimum = -INFINITY;
	int idx = -1;

	for (int i = 0; i < 2; i++)
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
 * Calcula a cor resultante da interseção do raio com o cone.
 * 
 * @param tInt O parâmetro de interseção do raio com o cone.
 * @param ray O raio que intersecta o cone.
 * @param sources Um vetor de fontes de luz.
 * @param shadows Um vetor de booleanos indicando se há sombras nas fontes de luz.
 * @return A cor resultante da interseção do raio com o cone.
 */
Eigen::Vector3d Cone::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	// se o cone for o plano circular inferior, retorna a cor do plano0
	if (this->structure == 0)
	{
		Eigen::Vector3d intesityEye(0, 0, 0);
		Eigen::Vector3d intesityAmbient(0, 0, 0);
		Eigen::Vector3d intesityDifuse(0, 0, 0);
		Eigen::Vector3d intesitySpecular(0, 0, 0);
		Eigen::Vector3d singleDifuse;
		Eigen::Vector3d singleSpecular;

		Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

		Eigen::Vector3d PI = pInt - this->vertex;
		Eigen::Vector3d normal = -((this->direction.cross(PI)).cross(PI)).normalized();

		int idx = 0;
		for (auto& source : sources)
		{	
			// calculando a intensidade difusa e especular
			source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
			idx++;
		}

		intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;
		return intesityEye;
	}
	else
	{
		return this->bottom->computeColor(tInt, ray, sources, shadows);
	}
}

/**
 * Translada o cone nas coordenadas (x, y, z).
 * 
 * @param x A coordenada x do vetor de translação.
 * @param y A coordenada y do vetor de translação.
 * @param z A coordenada z do vetor de translação.
 */
void Cone::translate(double x, double y, double z)
{
	Eigen::Matrix4d m;
	// matriz de translacao
	m << 1, 0, 0, x,
		 0, 1, 0, y,
		 0, 0, 1, z,
		 0, 0, 0, 1;

	Eigen::Vector4d centerTop4;
	Eigen::Vector4d centerBase4;

	centerTop4 << this->vertex[0], this->vertex[1], this->vertex[2], 1;
	centerBase4 << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	centerTop4 = m * centerTop4;
	centerBase4 = m * centerBase4;

	this->vertex << centerTop4[0], centerTop4[1], centerTop4[2];
	this->centerBase << centerBase4[0], centerBase4[1], centerBase4[2];

	this->direction = (this->vertex - this->centerBase).normalized();
	this->bottom->translate(x, y, z);
}

/**
 * @brief Escala o cone nas direções x, y e z.
 * 
 * @param x Fator de escala na direção x (raio).
 * @param y Fator de escala na direção y (altura).
 * @param z Fator de escala na direção z (não utilizado).
 */
void Cone::scale(double x, double y, double z)
{
	/*
	x -> Raio
	y -> Altura
	z -> Nada
	*/
	// atualizando o raio e a altura
	this->radius *= x;
	this->height *= y;

	// atualizando o vertice e o centro da base
	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

/**
 * Rotaciona o cone em torno do eixo X por um determinado ângulo.
 * 
 * @param angle O ângulo de rotação em radianos.
 */
void  Cone::rotateX(double angle)
{
	Eigen::Matrix4d rx;
	// matriz de rotacao em torno do eixo x
	rx << 1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;
	
	// rotacionando o vetor direcao
	newDir = rx * newDir;
	
	// atualizando o vetor direcao
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	// atualizando o vertice e o centro da base
	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

/**
 * Rotaciona o cone em torno do eixo Y por um determinado ângulo.
 * 
 * @param angle O ângulo de rotação em radianos.
 */
void  Cone::rotateY(double angle)
{
	Eigen::Matrix4d ry;
	// matriz de rotacao em torno do eixo y
	ry << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	// rotacionando o vetor direcao
	newDir = ry * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();
	
	// atualizando o vertice e o centro da base
	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

/**
 * Rotaciona o cone em torno do eixo Z por um determinado ângulo.
 * 
 * @param angle O ângulo de rotação em radianos.
 */
void  Cone::rotateZ(double angle)
{	
	// matriz de rotacao em torno do eixo z
	Eigen::Matrix4d rz;
	rz << cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	// rotacionando o vetor direcao
	newDir = rz * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	// atualizando o vertice e o centro da base
	this->vertex = this->centerBase + this->height * this->direction;
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

/**
 * Converte a posição do cone para o sistema de coordenadas da câmera.
 * 
 * @param transformationMatrix A matriz de transformação que será aplicada à posição do cone.
 */
void Cone::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d vertex;
	Eigen::Vector4d centerBase4;

	// convertendo o vertice e o centro da base para coordenadas homogeneas
	vertex << this->vertex[0], this->vertex[1], this->vertex[2], 1;
	base << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;
	
	// convertendo o vertice e o centro da base para o sistema de coordenadas da camera
	vertex = transformationMatrix * vertex;
	base = transformationMatrix * base;
	
	// atualizando o vertice e o centro da base
	this->vertex << vertex[0], vertex[1], vertex[2];
	this->centerBase << base[0], base[1], base[2];

	// atualizando o vetor direcao
	this->direction = (this->vertex - this->centerBase).normalized();
	this->bottom->convertToCamera(transformationMatrix);
}