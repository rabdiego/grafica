#include "Tensor.h"

Tensor::Tensor(int numColumns, int numLines) {
	this->numLines = numLines;
	this->numColumns = numColumns;

	this->red = Eigen::ArrayXXd::Zero(this->numLines, this->numColumns);
	this->green = Eigen::ArrayXXd::Zero(this->numLines, this->numColumns);
	this->blue = Eigen::ArrayXXd::Zero(this->numLines, this->numColumns);
}

void Tensor::normalize() {
	/*
	Como nada garante que o resultado do raycast
	com cor retorna valores entre 0 e 255,
	desenvolvi essa função para
	normalizar as matrizes nesse intervalo.
	*/
	double minimum = this->red(0, 0), maximum = this->red(0, 0);

	for (int c = 0; c < this->numColumns; c++) {
		for (int l = 0; l < this->numLines; l++) {
			if (this->red(l, c) <= 0) {
				this->red(l, c) = 0;
			}
			else if (this->red(l, c) < minimum) {
				minimum = this->red(l, c);
			}

			if (this->green(l, c) <= 0) {
				this->green(l, c) = 0;
			}
			else if (this->green(l, c) < minimum) {
				minimum = this->green(l, c);
			}

			if (this->blue(l, c) <= 0) {
				this->blue(l, c) = 0;
			}
			else if (this->blue(l, c) < minimum) {
				minimum = this->blue(l, c);
			}

			if (this->red(l, c) > maximum) {
				maximum = this->red(l, c);
			}
			if (this->green(l, c) > maximum) {
				maximum = this->green(l, c);
			}
			if (this->blue(l, c) > maximum) {
				maximum = this->blue(l, c);
			}
		}
	}

	this->red = 255 * (this->red - minimum) / (maximum - minimum);
	this->green = 255 * (this->green - minimum) / (maximum - minimum);
	this->blue = 255 * (this->blue - minimum) / (maximum - minimum);
}