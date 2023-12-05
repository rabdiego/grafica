#include <Eigen>

#ifndef Camera_H
#define Camera_H

class Camera
{
public:
	Eigen::Vector3d position;
	Eigen::Vector3d lookAt;
	Eigen::Vector3d viewUp;

	Eigen::Vector3d i;
	Eigen::Vector3d j;
	Eigen::Vector3d k;

	Eigen::Matrix4d transformationMatrix;

	Camera(Eigen::Vector3d position, Eigen::Vector3d lookAt, Eigen::Vector3d viewUp);
	Eigen::Matrix4d getTransformationMatrix();
};

#endif