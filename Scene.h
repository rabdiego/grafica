#include <vector>
#include "Object.h"
#include "HitBox.h"
#include "LightSource.h"
#include "Camera.h"

#ifndef Scene_H
#define Scene_H

/**
 * @brief Classe que representa uma cena.
 * 
 * A classe Scene é responsável por armazenar os objetos, hitboxes, fontes de luz e câmera de uma cena gráfica.
 * Ela fornece métodos para adicionar objetos, hitboxes e fontes de luz, limpar os objetos da cena, definir a câmera
 * e converter os objetos para o sistema de coordenadas da câmera.
 */
class Scene
{
public:
	std::vector<Object*> objects;       ///< Vetor de objetos da cena.
	std::vector<HitBox*> hitboxes;      ///< Vetor de hitboxes da cena.
	std::vector<LightSource*> sources;  ///< Vetor de fontes de luz da cena.
	Camera* camera;                     ///< Ponteiro para a câmera da cena.

	/**
	 * @brief Adiciona um objeto à cena.
	 */
	 * 
	 * @param object Ponteiro para o objeto a ser adicionado.
	 */
	void addObject(Object* object);

	/**
	 * @brief Adiciona uma hitbox à cena.
	 * 
	 * @param hitbox Ponteiro para a hitbox a ser adicionada.
	 */
	void addHitBox(HitBox* hitbox);

	/**
	 * @brief Adiciona uma fonte de luz à cena.
	 * 
	 * @param source Ponteiro para a fonte de luz a ser adicionada.
	 */
	void addSource(LightSource* source);

	/**
	 * @brief Limpa os objetos da cena.
	 */
	void cleanObjects();

	/**
	 * @brief Define a câmera da cena.
	 * 
	 * @param camera Ponteiro para a câmera a ser definida.
	 */
	void setCamera(Camera* camera);

	/**
	 * @brief Converte os objetos para o sistema de coordenadas da câmera.
	 * 
	 * @param lights Flag que indica se as luzes também devem ser convertidas.
	 */
	void convertObjectsToCamera(bool lights);

	/**
	 * @brief Obtém o número de elementos da cena.
	 * 
	 * @return O número de elementos da cena.
	 */
	int getNumElements();

	/**
	 * @brief Obtém o número de hitboxes da cena.
	 * 
	 * @return O número de hitboxes da cena.
	 */
	int getNumHitBoxes();
};

#endif