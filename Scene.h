#include <vector>
#include "Object.h"

#ifndef Scene_H
#define Scene_H

class Scene {
public:
	std::vector <Object*> objects;

	void addObject(Object* object);
	int getNumElements();
};

#endif