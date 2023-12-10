#include "Tensor.h"

/**
 * @brief Construtor da classe Tensor.
 * 
 * @param numColumns O número de colunas do tensor.
 * @param numLines O número de linhas do tensor.
 */
Tensor::Tensor(int numColumns, int numLines)
{
	this->numLines = numLines;
	this->numColumns = numColumns;

	this->red = Eigen::ArrayXXd::Zero(this->numLines, this->numColumns);
	this->green = Eigen::ArrayXXd::Zero(this->numLines, this->numColumns);
	this->blue = Eigen::ArrayXXd::Zero(this->numLines, this->numColumns);
}

/**
 * Normaliza o tensor.
 */
void Tensor::normalize()
{
	/*
	Como nada garante que o resultado do raycast
	com cor retorna valores entre 0 e 255,
	desenvolvi essa fun��o para
	normalizar as matrizes nesse intervalo.
	*/
	double  maximum = this->red(0, 0);

	for (int c = 0; c < this->numColumns; c++)
	{
		for (int l = 0; l < this->numLines; l++)
		{
			if (this->red(l, c) <= 0)
			{
				this->red(l, c) = 0;
			}

			if (this->green(l, c) <= 0)
			{
				this->green(l, c) = 0;
			}

			if (this->blue(l, c) <= 0)
			{
				this->blue(l, c) = 0;
			}

			if (this->red(l, c) > maximum)
			{
				maximum = this->red(l, c);
			}
			if (this->green(l, c) > maximum)
			{
				maximum = this->green(l, c);
			}
			if (this->blue(l, c) > maximum)
			{
				maximum = this->blue(l, c);
			}
		}
	}

	this->red = 255 * (this->red / maximum);
	this->green = 255 * (this->green / maximum);
	this->blue = 255 * (this->blue / maximum);
}