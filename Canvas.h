#include <Eigen>

#include "Tensor.h"
#include "Ray.h"
#include "Scene.h"

#ifndef Canvas_H
#define Canvas_H

class Canvas
{
	/*
	Classe do Canvas
	*/
public:
	double windowDistance;
	double windowWidth;
	double windowHeight;
	double numLines;
	double numColumns;
	double deltaX;
	double deltaY;
	double jXMin;
	double jYMax;

	// Construtor da Classe Canvas
	Canvas(double windowDistance, double windowWidth, double windowHeight, double numLines, double numColumns);


	/**
	 * Realiza um lançamento de raio a partir de um ponto de observação para a cena especificada.
	 * 
	 * @param observable O ponto de observação a partir do qual o raio é lançado.
	 * @param scene A cena na qual o raio é lançado.
	 * @param toCamera Um valor booleano que indica se o raio deve ser lançado em direção à câmera.
	 * @return Um tensor contendo as informações resultantes do lançamento de raio.
	 */
	Tensor raycast(Eigen::Vector3d observable, Scene scene, bool toCamera);
};

#endif