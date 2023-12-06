#include "Plane.h"
#include <iostream>
#include <cmath>

/**
 * Retorna a cor de um pixel específico em uma superfície SDL(Textura).
 *
 * @param pSurface A superfície SDL da qual obter a cor do pixel.
 * @param X A coordenada X do pixel.
 * @param Y A coordenada Y do pixel.
 * @return A cor do pixel na forma de uma estrutura SDL_Color.
 */
SDL_Color GetPixelColor(const SDL_Surface* pSurface, const int X, const int Y)
{
	// Bytes per pixel
	const Uint8 Bpp = pSurface->format->BytesPerPixel;

	/*
	Retrieve the address to a specific pixel
	pSurface->pixels	= an array containing the SDL_Surface' pixels
	pSurface->pitch		= the length of a row of pixels (in bytes)
	X and Y				= the offset on where on the image to retrieve the pixel, (0, 0) is in the upper left corner of the image
	*/
	Uint8* pPixel = (Uint8*)pSurface->pixels + Y * pSurface->pitch + X * Bpp;

	Uint32 PixelData = *(Uint32*)pPixel;

	SDL_Color Color = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };

	// Retrieve the RGB values of the specific pixel
	SDL_GetRGB(PixelData, pSurface->format, &Color.r, &Color.g, &Color.b);

	return Color;
}

/**
 * @brief Construtor da classe Plane.
 * 
 * @param texture Superfície SDL que representa a textura do plano.
 * @param normal Vetor 3D que representa a normal do plano.
 * @param center Vetor 3D que representa o centro do plano.
 * @param kAmbient Vetor 3D que representa o coeficiente de reflexão ambiente do plano.
 * @param kDif Vetor 3D que representa o coeficiente de reflexão difusa do plano.
 * @param kEsp Vetor 3D que representa o coeficiente de reflexão especular do plano.
 * @param specularIndex Índice de especularidade do plano.
 */
Plane::Plane(SDL_Surface* texture, Eigen::Vector3d normal, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, double specularIndex)
{
	this->texture = texture;
	this->normal = normal.normalized();
	this->center = center;
	this->kAmbient = kAmbient;
	this->kDif = kDif;
	this->kEsp = kEsp;
	this->specularIndex = specularIndex;

	int menor;
	double menorValor = INFINITY;
	for (int i = 1; i < 3; i++)
	{
		if (std::abs(normal[i]) < menorValor)
		{
			menor = i;
			menorValor = normal[i];
		}
	}

	if (menor == 0)
	{
		this->axis1 << 0, -normal[2], normal[1];
	}
	else if (menor == 1)
	{
		this->axis1 << -normal[2], 0, normal[0];
	}
	else
	{
		this->axis1 << -normal[1], normal[0], 0;
	}

	this->axis1 = this->axis1.normalized();
	this->axis2 = (normal.cross(this->axis1)).normalized();
}

/**
 * @brief Verifica se um raio intercepta o plano.
 *
 * @param ray Raio a ser verificado.
 */
double Plane::hasInterceptedRay(Ray ray)
{
	Eigen::Vector3d w = ray.initialPoint - this->center;
	double tInt = -(this->normal.dot(w)) / (this->normal.dot(ray.direction));

	if (tInt < 0)
		return tInt;

	return 1;
}


/**
 * @brief Calcula a cor do plano no ponto de interseção com um raio.
 *
 * @param tInt Valor do parâmetro t no ponto de interseção.
 * @param ray Raio de interseção.
 * @param sources Vetor de fontes de luz.
 * @param shadows Vetor de booleanos indicando se há sombra no ponto de interseção.
 * @return Cor do plano no ponto de interseção.
 */
Eigen::Vector3d Plane::computeColor(double tInt, Ray ray, std::vector<LightSource*> sources, std::vector<bool> shadows)
{
	Eigen::Vector3d intesityEye(0, 0, 0);

	Eigen::Vector3d pInt = ray.initialPoint + tInt * ray.direction;

	Eigen::Vector2d pIntBase;
	pIntBase << abs(((int)(this->axis1.dot(pInt - this->center))) % 256), abs(((int)(this->axis2.dot(pInt - this->center))) % 256);

	Eigen::Vector3d intesityAmbient;
	Eigen::Vector3d intesityDifuse(0, 0, 0);
	Eigen::Vector3d intesitySpecular(0, 0, 0);
	Eigen::Vector3d singleDifuse;
	Eigen::Vector3d singleSpecular;
	Eigen::Vector3d normal = this->normal;

	if (this->texture == NULL)
	{
		intesityAmbient << 0, 0, 0;
	}
	else
	{
		SDL_Color colorToPaint = GetPixelColor(this->texture, pIntBase[0], pIntBase[1]);
		intesityAmbient << (int)colorToPaint.r, (int)colorToPaint.g, (int)colorToPaint.b;
	}

	int idx = 0;
	for (auto& source : sources)
	{
		source->computeIntensity(pInt, ray, &intesityAmbient, &intesityDifuse, &intesitySpecular, normal, this->kAmbient, this->kDif, this->kEsp, this->specularIndex, shadows[idx]);
		idx++;
	}

	intesityEye = intesityDifuse + intesitySpecular + intesityAmbient;

	return intesityEye;
}

void Plane::translate(double x, double y, double z)
{
	Eigen::Matrix4d m;
	m << 1, 0, 0, x,
		 0, 1, 0, y,
		 0, 0, 1, z,
		 0, 0, 0, 1;

	Eigen::Vector4d center4;
	center4 << this->center[0], this->center[1], this->center[2], 1;

	center4 = m * center4;

	this->center << center4[0], center4[1], center4[2];
}

void Plane::scale(double x, double y, double z)
{

}

void  Plane::rotateX(double angle)
{
	Eigen::Matrix4d rx;
	rx << 1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->normal[0], this->normal[1], this->normal[2], 0;

	newDir = rx * newDir;
	this->normal << newDir[0], newDir[1], newDir[2];
	this->normal = (this->normal).normalized();

	int menor = 0, menorValor = normal[0];
	for (int i = 1; i < 3; i++)
	{
		if (normal[i] < menorValor)
		{
			menor = i;
			menorValor = normal[i];
		}
	}

	if (menor == 0)
	{
		this->axis1 << 0, -normal[2], normal[1];
	}
	else if (menor == 1)
	{
		this->axis1 << -normal[2], 0, normal[0];
	}
	else
	{
		this->axis1 << -normal[1], normal[0], 0;
	}

	this->axis1 = this->axis1.normalized();
	this->axis2 = (normal.cross(this->axis1)).normalized();
}

void  Plane::rotateY(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->normal[0], this->normal[1], this->normal[2], 0;

	newDir = rx * newDir;
	this->normal << newDir[0], newDir[1], newDir[2];
	this->normal = (this->normal).normalized();

	int menor = 0, menorValor = normal[0];
	for (int i = 1; i < 3; i++)
	{
		if (normal[i] < menorValor)
		{
			menor = i;
			menorValor = normal[i];
		}
	}

	if (menor == 0)
	{
		this->axis1 << 0, -normal[2], normal[1];
	}
	else if (menor == 1)
	{
		this->axis1 << -normal[2], 0, normal[0];
	}
	else
	{
		this->axis1 << -normal[1], normal[0], 0;
	}

	this->axis1 = this->axis1.normalized();
	this->axis2 = (normal.cross(this->axis1)).normalized();
}

void  Plane::rotateZ(double angle)
{
	Eigen::Matrix4d rx;
	rx << cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	Eigen::Vector4d newDir;
	newDir << this->normal[0], this->normal[1], this->normal[2], 0;

	newDir = rx * newDir;
	this->normal << newDir[0], newDir[1], newDir[2];
	this->normal = (this->normal).normalized();

	int menor = 0, menorValor = normal[0];
	for (int i = 1; i < 3; i++)
	{
		if (normal[i] < menorValor)
		{
			menor = i;
			menorValor = normal[i];
		}
	}

	if (menor == 0)
	{
		this->axis1 << 0, -normal[2], normal[1];
	}
	else if (menor == 1)
	{
		this->axis1 << -normal[2], 0, normal[0];
	}
	else
	{
		this->axis1 << -normal[1], normal[0], 0;
	}

	this->axis1 = this->axis1.normalized();
	this->axis2 = (normal.cross(this->axis1)).normalized();
}

void Plane::convertToCamera(Eigen::Matrix4d transformationMatrix)
{
	Eigen::Vector4d center4, normal4;
	center4 << this->center[0], this->center[1], this->center[2], 1;
	normal4 << this->normal[0], this->normal[1], this->normal[2], 0;

	center4 = transformationMatrix * center4;
	normal4 = transformationMatrix * normal4;

	this->center << center4[0], center4[1], center4[2];
	this->normal << normal4[0], normal4[1], normal4[2];
}