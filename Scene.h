#include <vector>
#include "Object.h"
#include "LightSource.h"

#ifndef Scene_H
#define Scene_H

class Scene
{
public:
	std::vector <Object*> objects;
	std::vector <LightSource*> sources;

	void addObject(Object* object);
	void addSource(LightSource* source);
	int getNumElements();
};

#endif