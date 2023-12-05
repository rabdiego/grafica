#include <vector>
#include "Object.h"
#include "HitBox.h"
#include "LightSource.h"
#include "Camera.h"

#ifndef Scene_H
#define Scene_H

class Scene
{
public:
	std::vector <Object*> objects;
	std::vector <HitBox*> hitboxes;
	std::vector <LightSource*> sources;
	Camera* camera;

	void addObject(Object* object);
	void addHitBox(HitBox* hitbox);
	void addSource(LightSource* source);
	void cleanObjects();
	void setCamera(Camera* camera);
	void convertObjectsToCamera(bool lights);
	int getNumElements();
	int getNumHitBoxes();
};

#endif