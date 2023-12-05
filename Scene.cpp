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

void Scene::cleanObjects()
{
	this->objects.clear();
	this->hitboxes.clear();
}

void Scene::setCamera(Camera* camera)
{
	this->camera = camera;
}

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

int Scene::getNumElements()
{
	return (this->objects).size();
}

int Scene::getNumHitBoxes()
{
	return (this->hitboxes).size();
}