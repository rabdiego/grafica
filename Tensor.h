#include <Eigen>

#ifndef Tensor_H
#define Tensor_H

/**
 * Classe para representar a matriz de cores.
 * São 3 matrizes de tamanho (numCol, numLin),
 * cada uma representando um canal de cor.
 */
class Tensor
{
public:
	Eigen::ArrayXXd red;    /**< Matriz de cores vermelhas. */
	Eigen::ArrayXXd green;  /**< Matriz de cores verdes. */
	Eigen::ArrayXXd blue;   /**< Matriz de cores azuis. */
	int numColumns;         /**< Número de colunas da matriz. */
	int numLines;           /**< Número de linhas da matriz. */

	/**
	 * Construtor da classe Tensor.
	 * @param numColumns Número de colunas da matriz.
	 * @param numLines Número de linhas da matriz.
	 */
	Tensor(int numColumns, int numLines);

	/**
	 * Normaliza os valores das matrizes de cores.
	 */
	void normalize();
};
class Tensor

#endif