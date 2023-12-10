#include "Scene.h"


/**
 * Adiciona um objeto à cena.
 * @param object O objeto a ser adicionado.
 */
void Scene::addObject(Object* object)
{
	this->objects.push_back(object);
}

/**
 * Adiciona uma fonte de luz à cena.
 * @param source A fonte de luz a ser adicionada.
 */
void Scene::addSource(LightSource* source)
{
	this->sources.push_back(source);
}

/**
 * Adiciona uma hitbox à cena.
 * 
 * @param hitbox A hitbox a ser adicionada.
*/
void Scene::addHitBox(HitBox* hitbox)
{
	this->hitboxes.push_back(hitbox);
}


/**
 * Limpa todos os objetos e hitboxes da cena.
 */
void Scene::cleanObjects()
{
	this->objects.clear();
	this->hitboxes.clear();
}

/**
 * seta a camera da cena.
*/
void Scene::setCamera(Camera* camera)
{
	this->camera = camera;
}

/**
 * Converta todos os objetos da cena para o sistema de coordenadas da camera.
 * 
 * @param lights Indica se as fontes de luz também devem ser convertidas.
 */
void Scene::convertObjectsToCamera(bool lights)
{
	for (auto& o : this->objects)
	{
		o->convertToCamera(this->camera->getTransformationMatrix());
	}
	if (lights)
	{
		for (auto& s : this->sources)
		{
			s->convertToCamera(this->camera->getTransformationMatrix());
		}
	}
	for (auto& h : this->hitboxes)
	{
		h->convertToCamera(this->camera->getTransformationMatrix());
	}
}

// retorna o numeros de elemtnos na cena
int Scene::getNumElements()
{
	return (int) (this->objects).size();
}

// retorna o numeros de hitbox na cena
int Scene::getNumHitBoxes()
{
	return (int) (this->hitboxes).size();
}