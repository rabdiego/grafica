#include <vector>
#include "Object.h"
#include "HitBox.h"
#include "LightSource.h"
#include "Camera.h"

#ifndef Scene_H
#define Scene_H

/**
 * Classe que representa uma cena.
 */
class Scene
{
public:
	std::vector <Object*> objects; /**< Vetor de objetos da cena. */
	std::vector <HitBox*> hitboxes; /**< Vetor de hitboxes da cena. */
	std::vector <LightSource*> sources; /**< Vetor de fontes de luz da cena. */
	Camera* camera; /**< Câmera da cena. */

	/**
	 * Adiciona um objeto à cena.
	 * @param object O objeto a ser adicionado.
	 */
	void addObject(Object* object);

	/**
	 * Adiciona uma hitbox à cena.
	 * @param hitbox A hitbox a ser adicionada.
	 */
	void addHitBox(HitBox* hitbox);

	/**
	 * Adiciona uma fonte de luz à cena.
	 * @param source A fonte de luz a ser adicionada.
	 */
	void addSource(LightSource* source);

	/**
	 * Limpa todos os objetos da cena.
	 */
	void cleanObjects();

	/**
	 * Define a câmera da cena.
	 * @param camera A câmera a ser definida.
	 */
	void setCamera(Camera* camera);

	/**
	 * Converte os objetos da cena para o sistema de coordenadas da câmera.
	 * @param lights Indica se as luzes também devem ser convertidas.
	 */
	void convertObjectsToCamera(bool lights);

	/**
	 * Obtém o número de elementos na cena.
	 * @return O número de elementos na cena.
	 */
	int getNumElements();

	/**
	 * Obtém o número de hitboxes na cena.
	 * @return O número de hitboxes na cena.
	 */
	int getNumHitBoxes();
};

#endif