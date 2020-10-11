#ifndef WORLD_H
#define WORLD_H

// Framework includes.
#include <GLM/glm.hpp>

// Data includes
#include "Sphere.h"
#include "Camera.h"
#include "PointLight.h"
#include "Buffer.h"

// Utility includes.
#include <vector>

/// <summary> Represents a world with spheres, a camera, and a light source. </summary>
class World
{
public:
	/// <summary> Creates a world with the given window size for the camera. </summary>
	/// <param name="_windowSize"> The size of the camera's viewport in pixels. </param>
	World(const glm::vec2 _windowSize) : m_spheres(), m_camera(Rendering::Camera::FromLookAt(_windowSize, glm::vec3(0, 0, -50), glm::vec3(0, 0, 0))), m_lightSource(glm::vec3(-20, 0, -20), 2.0f, Colour(94, 85, 64)) { initialiseSpheres(); }

	Buffer& Draw(uint8_t);
private:
	/// <summary> The source of light. </summary>
	PointLight m_lightSource;

	/// <summary> Every sphere that exists within the world. </summary>
	std::vector<Shapes::Sphere> m_spheres;

	/// <summary> The camera used to draw the world. </summary>
	Rendering::Camera m_camera;

	void drawSection(uint16_t, uint16_t, Buffer&);

	void initialiseSpheres();
};
#endif