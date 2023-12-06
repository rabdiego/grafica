#include <Eigen>
#include "LightSource.h"

#ifndef AmbientSource_H
#define AmbientSource_H

/**
 * @brief Represents an ambient light source.
 * 
 * This class inherits from the LightSource class and provides functionality
 * for an ambient light source in a 3D scene.
 */
class AmbientSource : public LightSource
{
public:
	/**
	 * @brief Constructs an AmbientSource object with the given intensity.
	 * 
	 * @param intensity The intensity of the ambient light source.
	 */
	AmbientSource(Eigen::Vector3d intensity);

	/**
	 * @brief Calculates the direction from the ambient light source to a given point.
	 * 
	 * @param pInt The position of the point.
	 * @return The direction from the ambient light source to the point.
	 */
	Eigen::Vector3d getDirection(Eigen::Vector3d pInt);

	/**
	 * @brief Computes the intensity of the ambient light source at a given point.
	 * 
	 * This function calculates the ambient, diffuse, and specular intensities at
	 * the given point based on the provided parameters.
	 * 
	 * @param pInt The position of the point.
	 * @param ray The ray from the camera to the point.
	 * @param ptrIntesityAmbient Pointer to store the ambient intensity.
	 * @param ptrIntesityDifuse Pointer to store the diffuse intensity.
	 * @param ptrIntesitySpecular Pointer to store the specular intensity.
	 * @param normal The surface normal at the point.
	 * @param kAmbient The ambient reflection coefficient.
	 * @param kDif The diffuse reflection coefficient.
	 * @param kEsp The specular reflection coefficient.
	 * @param specularIndex The specular index.
	 * @param shadowed Flag indicating if the point is shadowed.
	 */
	void computeIntensity(Eigen::Vector3d pInt, Ray ray, Eigen::Vector3d* ptrIntesityAmbient, Eigen::Vector3d* ptrIntesityDifuse, Eigen::Vector3d* ptrIntesitySpecular, 
		Eigen::Vector3d normal, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex, bool shadowed);

	/**
	 * @brief Converts the ambient light source to camera space.
	 * 
	 * This function applies the given transformation matrix to convert the
	 * ambient light source from world space to camera space.
	 * 
	 * @param transformationMatrix The transformation matrix.
	 */
	void convertToCamera(Eigen::Matrix4d transformationMatrix);
};

#endif