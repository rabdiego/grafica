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

/**
 * @brief Construtor da classe Cilinder.
 * 
 * @param height A altura do cilindro.
 * 
 * Diferente do primeiro, esse possui a altura e nao o centro do topo.
 * Por tanto, calcula o centro do topo a partir da altura e da direção,
 * enquanto com o centro do topo calcula a direção(consequentemente a altura).
 */
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
 * @brief Verifica se o raio intercepta o cilindro.
 * 
 * @param ray O raio a ser verificado.
 * 
 * @return O valor do tInt, ou seja, o valor do t em que o raio intercepta o cilindro.
 */
double Cilinder::hasInterceptedRay(Ray ray)
{
	// w: vetor do centro da base até o ponto inicial do raio
	Eigen::Vector3d w = ray.initialPoint - this->centerBase;
	Eigen::Vector3d pInt(0, 0, 0); 

	// valor de retorno padrão: não houve interseção
	double returnValue = 1;

	// a*t^2 + b*t + c = 0: coeficientes da equação do segundo grau
	double a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(this->direction), 2);
	double b = 2 * w.dot(ray.direction) - 2 * w.dot(this->direction) * ray.direction.dot(this->direction);
	double c = w.dot(w) - pow(w.dot(this->direction), 2) - pow(this->radius, 2);

	double delta = b * b - 4 * a * c;

	// Delta menor que 0, então não houve interseção
	if (a != 0 && delta >= 0)
	{
		double tInt = (sqrt(delta) - b) / (2 * a);

		//? ponto de interseção: pInt = p0 + tInt * d
		pInt = ray.initialPoint + tInt * ray.direction;

		double insideInterval = (pInt - this->centerBase).dot(this->direction);

		// se o ponto de interseção está dentro do intervalo da altura do cilindro
		if (insideInterval >= 0 && insideInterval <= this->height)
		{
			// atualiza o valor de retorno e a estrutura que foi interceptada(0: cilindro, 1: topo, 2: base)
			returnValue = tInt;
			this->structure = 0;
		}

	}

	// verifica se o raio intercepta o topo ou a base do cilindro
	double top = this->top->hasInterceptedRay(ray);
	double bottom = this->bottom->hasInterceptedRay(ray);

	double minimum = -INFINITY;
	int idx = -1;
	std::vector <double> distances = { returnValue, top, bottom };

	// distancia minima entre as interseções do cilindro, topo e base
	for (int i = 0; i < 3; i++)
	{
		if (distances[i] < 0 && distances[i] > minimum)
		{
			minimum = distances[i];
			idx = i;
			this->structure = i;
		}
	}

	// idx == 1: topo, idx == 2: base
	if (idx != -1)
		return distances[idx];

	return 1;
}

/**
 * Calcula a cor usando o modelo de iluminação para um ponto de interseção em um cilindro.
 * 
 * @param tInt O parâmetro de interseção.
 * @param ray O raio de luz incidente.
 * @param sources As fontes de luz no ambiente.
 * @param shadows Um vetor de booleanos indicando se cada fonte de luz está bloqueada por sombras.
 * @return A cor calculada para o ponto de interseção.
 */
Eigen::Vector3d Cilinder::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	/**
	 * @param structure: define qual estrutura do cilindro foi interceptada
	 * [ 0 ] - cilindro
	 * [ 1 ] - topo
	 * [ 2 ] - base
	*/
	if (this->structure == 0)
	{
		
		Eigen::Vector3d intesityEye(0, 0, 0);
		Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

		// intensidades de cada componente da cor
		Eigen::Vector3d intesityAmbient(0, 0, 0);
		Eigen::Vector3d intesityDifuse(0, 0, 0);
		Eigen::Vector3d intesitySpecular(0, 0, 0);

		/**
		 * @param v: vetor do centro da base até o ponto de interseção
		 * @param projection: projeção de v na direção do cilindro
		 * @param normal: vetor normal ao cilindro no ponto de interseção
		*/
		Eigen::Vector3d v = pInt - this->centerBase;
		Eigen::Vector3d projection = (v.dot(this->direction)) * this->direction;
		Eigen::Vector3d normal = (v - projection).normalized();

		int idx = 0;
		//* Cada fonte de luz
		for (auto& source : sources)
		{
			// calcula a intensidade de cada componente da cor
			source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
			idx++;
		}

		// intensidade total
		intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;
		return intesityEye;
	}
	else if (this->structure == 1)
	{
		return this->top->computeColor(tInt, ray, sources, shadows);
		
	}
	else
	{
		return this->bottom->computeColor(tInt, ray, sources, shadows);
	}

}

/**
 * Translada o cilindro nas coordenadas x, y e z.
 * 
 * @param x A coordenada x para a translação.
 * @param y A coordenada y para a translação.
 * @param z A coordenada z para a translação.
 */
void Cilinder::translate(double x, double y, double z)
{
	//? matriz de translação
	Eigen::Matrix4d m;
	m << 1, 0, 0, x,
		 0, 1, 0, y,
	  	 0, 0, 1, z,
		 0, 0, 0, 1;

	Eigen::Vector4d centerTop4;
	Eigen::Vector4d centerBase4;

	//? converte os centros para coordenadas homogêneas
	centerTop4 << this->centerTop[0], this->centerTop[1], this->centerTop[2], 1;
	centerBase4 << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	//? translada os centros
	centerTop4 = m * centerTop4;
	centerBase4 = m * centerBase4;

	//? atualiza os valores dos centros
	this->centerTop << centerTop4[0], centerTop4[1], centerTop4[2];
	this->centerBase << centerBase4[0], centerBase4[1], centerBase4[2];

	//? atualiza a direção
	this->direction = (this->centerTop - this->centerBase).normalized();

	//? atualiza os planos(topo e base)
	this->bottom->translate(x, y, z);
	this->top->translate(x, y, z);
}

/**
 * @brief Redimensiona o cilindro nas direções x, y e z.
 * 
 * @param x Fator de escala na direção x.
 * @param y Fator de escala na direção y.
 * @param z Fator de escala na direção z.
 */
void  Cilinder::scale(double x, double y, double z)
{
	// nao necessita matriz de escala, pois o raio e a altura sao escalados é suficiente
	this->radius *= x;
	this->height *= y;

	// atualiza o centro do topo
	this->centerTop = this->centerBase + this->height * this->direction;

	/**
	 * novos planos para o topo e base
	 * usando as novas dimensoes do cilindro
	*/
	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

/**
 * Metodos para rotação em torno dos eixos x, y e z.
 * essencialmente iguais, apenas mudando a matriz de rotação pro respectivo eixo.
 * 
 * @param angle O ângulo de rotação.
*/
void  Cilinder::rotateX(double angle)
{
	// matriz de rotação
	Eigen::Matrix4d rx;
	rx << 1, 0, 0, 0,
		  0, cos(angle), -sin(angle), 0,
		  0, sin(angle), cos(angle), 0,
		  0, 0, 0, 1;

	// Calcular novo vetor de direção
	Eigen::Vector4d newDir;
	newDir << this->direction[0], this->direction[1], this->direction[2], 0;

	newDir = rx * newDir;
	this->direction << newDir[0], newDir[1], newDir[2];
	this->direction = (this->direction).normalized();

	// atualiza o centro do topo
	this->centerTop = this->centerBase + this->height * this->direction;

	// atualiza os planos(topo e base)
	this->top = new CircularPlane(this->direction, this->centerTop, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
	this->bottom = new CircularPlane(-this->direction, this->centerBase, this->radius, this->kAmbient, this->kDif, this->kEsp, this->specularIndex);
}

void  Cilinder::rotateY(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
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

void  Cilinder::rotateZ(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), -sin(angle), 0, 0,
		  sin(angle), cos(angle), 0, 0,
		  0, 0, 1, 0,
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

// nao implementado para o cilindro
void Cilinder::rotateAny(double angle, Eigen::Vector3d p1, Eigen::Vector3d p2)
{}



/**
 * Converte as coordenadas do cilindro para o sistema de coordenadas da câmera.
 * 
 * @param transformationMatrix A matriz de transformação que será aplicada às coordenadas do cilindro.
 */
void Cilinder::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d centerTop4;
	Eigen::Vector4d centerBase4;

	centerTop4 << this->centerTop[0], this->centerTop[1], this->centerTop[2], 1;
	centerBase4 << this->centerBase[0], this->centerBase[1], this->centerBase[2], 1;

	centerTop4 = transformationMatrix * centerTop4;
	centerBase4 = transformationMatrix * centerBase4;

	this->centerTop << centerTop4[0], centerTop4[1], centerTop4[2];
	this->centerBase << centerBase4[0], centerBase4[1], centerBase4[2];

	this->direction = (this->centerTop - this->centerBase).normalized();
	this->bottom->convertToCamera(transformationMatrix);
	this->top->convertToCamera(transformationMatrix);
}