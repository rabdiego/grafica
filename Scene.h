#include <vector>
#include "Object.h"
#include "HitBox.h"
#include "LightSource.h"

#ifndef Scene_H
#define Scene_H

class Scene
{
public:
	std::vector <Object*> objects;
	std::vector <HitBox*> hitboxes;
	std::vector <LightSource*> sources;

	void addObject(Object* object);
	void addHitBox(HitBox* hitbox);
	void addSource(LightSource* source);
	void cleanObjects();
	int getNumElements();
	int getNumHitBoxes();
};

#endif