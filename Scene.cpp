#include "Scene.h"

void Scene::addObject(Object* object)
{
	this->objects.push_back(object);
}

void Scene::addSource(LightSource* source)
{
	this->sources.push_back(source);
}

int Scene::getNumElements()
{
	return (this->objects).size();
}