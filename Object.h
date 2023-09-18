#include <Eigen>

#include "Ray.h"
#include "PontualSource.h"

#ifndef Object_H
#define Object_H

class Object {
public:
	virtual Eigen::Vector4d hasInterceptedRay(Ray ray, PontualSource source) = 0;
};

#endif