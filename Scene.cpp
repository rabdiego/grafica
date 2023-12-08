#include "Scene.h"


/**
 * @brief Construtor da classe Scene.
 */
void Scene::addObject(Object* object)
{
	this->objects.push_back(object);
}

/**
 * @brief Obtém o objeto da cena que é atingido pelo raio.
 * @param ray O raio que atinge o objeto.
 * @param ptrIntersection Ponteiro para armazenar o ponto de interseção.
 * @param ptrNormal Ponteiro para armazenar a normal do ponto de interseção.
 * @param ptrMaterial Ponteiro para armazenar o material do objeto.
 * @param ptrDistance Ponteiro para armazenar a distância entre o ponto de origem do raio e o ponto de interseção.
 * @return O objeto atingido pelo raio.
 */
void Scene::addSource(LightSource* source)
{
	this->sources.push_back(source);
}

/**
 * @brief Obtém o objeto da cena que é atingido pelo raio.
 * @param ray O raio que atinge o objeto.
 * @param ptrIntersection Ponteiro para armazenar o ponto de interseção.
 * @param ptrNormal Ponteiro para armazenar a normal do ponto de interseção.
 * @param ptrMaterial Ponteiro para armazenar o material do objeto.
 * @param ptrDistance Ponteiro para armazenar a distância entre o ponto de origem do raio e o ponto de interseção.
 * @return O objeto atingido pelo raio.
 */
void Scene::addHitBox(HitBox* hitbox)
{
	this->hitboxes.push_back(hitbox);
}

/**
 * @brief Obtém o objeto da cena que é atingido pelo raio.
 * @param ray O raio que atinge o objeto.
 * @param ptrIntersection Ponteiro para armazenar o ponto de interseção.
 * @param ptrNormal Ponteiro para armazenar a normal do ponto de interseção.
 * @param ptrMaterial Ponteiro para armazenar o material do objeto.
 * @param ptrDistance Ponteiro para armazenar a distância entre o ponto de origem do raio e o ponto de interseção.
 * @return O objeto atingido pelo raio.
 */
void Scene::cleanObjects()
{
	this->objects.clear();
	this->hitboxes.clear();
}

/**
 * @brief Obtém o objeto da cena que é atingido pelo raio.
 * @param ray O raio que atinge o objeto.
 * @param ptrIntersection Ponteiro para armazenar o ponto de interseção.
 * @param ptrNormal Ponteiro para armazenar a normal do ponto de interseção.
 * @param ptrMaterial Ponteiro para armazenar o material do objeto.
 * @param ptrDistance Ponteiro para armazenar a distância entre o ponto de origem do raio e o ponto de interseção.
 * @return O objeto atingido pelo raio.
 */
void Scene::setCamera(Camera* camera)
{
	this->camera = camera;
}

/**
 * @brief Obtém o objeto da cena que é atingido pelo raio.
 * @param ray O raio que atinge o objeto.
 * @param ptrIntersection Ponteiro para armazenar o ponto de interseção.
 * @param ptrNormal Ponteiro para armazenar a normal do ponto de interseção.
 * @param ptrMaterial Ponteiro para armazenar o material do objeto.
 * @param ptrDistance Ponteiro para armazenar a distância entre o ponto de origem do raio e o ponto de interseção.
 * @return O objeto atingido pelo raio.
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

/**
 * @brief Obtém o objeto da cena que é atingido pelo raio.
 * @param ray O raio que atinge o objeto.
 * @param ptrIntersection Ponteiro para armazenar o ponto de interseção.
 * @param ptrNormal Ponteiro para armazenar a normal do ponto de interseção.
 * @param ptrMaterial Ponteiro para armazenar o material do objeto.
 * @param ptrDistance Ponteiro para armazenar a distância entre o ponto de origem do raio e o ponto de interseção.
 * @return O objeto atingido pelo raio.
 */
int Scene::getNumElements()
{
	return (this->objects).size();
}

/**
 * @brief Obtém o objeto da cena que é atingido pelo raio.
 * @param ray O raio que atinge o objeto.
 * @param ptrIntersection Ponteiro para armazenar o ponto de interseção.
 * @param ptrNormal Ponteiro para armazenar a normal do ponto de interseção.
 * @param ptrMaterial Ponteiro para armazenar o material do objeto.
 * @param ptrDistance Ponteiro para armazenar a distância entre o ponto de origem do raio e o ponto de interseção.
 * @return O objeto atingido pelo raio.
 */
int Scene::getNumHitBoxes()
{
	return (this->hitboxes).size();
}