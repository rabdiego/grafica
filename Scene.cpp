#include "Scene.h"

void Scene::addObject(Object* object) {
	this->objects.push_back(object);
}

int Scene::getNumElements() {
	return (this->objects).size();
}