#include <Eigen>

#ifndef Tensor_H
#define Tensor_H

class Tensor {
	/*
	Classe para representar a matriz de cores
	São 3 matrizes de tamanho (numCol, numLin),
	cada uma representando um canal de cor.
	*/
public:
	Eigen::ArrayXXd red;
	Eigen::ArrayXXd green;
	Eigen::ArrayXXd blue;
	int numColumns, numLines;

	Tensor(int numColumns, int numLines);
	void normalize();
};

#endif