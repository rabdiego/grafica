#include "Scene.h"

void Scene::addObject(Object* object)
{
	this->objects.push_back(object);
}

void Scene::addSource(LightSource* source)
{
	this->sources.push_back(source);
}

void Scene::addHitBox(HitBox* hitbox)
{
	this->hitboxes.push_back(hitbox);
}

int Scene::getNumElements()
{
	return (this->objects).size();
}

int Scene::getNumHitBoxes()
{
	return (this->hitboxes).size();
}