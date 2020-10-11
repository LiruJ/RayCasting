#ifndef POINTLIGHT_H
#define POINTLIGHT_H

// Framework includes.
#include <GLM/glm.hpp>

// Data includes.
#include "Colour.h"

// Typedef includes.
#include <cmath>

/// <summary> Represents a light source that exists within a single position and emits a coloured light in all directions. </summary>
struct PointLight
{
	/// <summary> Creates a point light at the given position with the given intensity, with a default white colour. </summary>
	/// <param name="_position"> The position within the world. </param>
	/// <param name="_intensity"> The intensity of the light. </param>
	PointLight(const glm::vec3 _position, const float_t _intensity) : m_position(_position), m_intensity(_intensity), m_colour(Colour::White()) { }

	/// <summary> Creates a point light at the given position with the given intensity and colour. </summary>
	/// <param name="_position"> The position within the world. </param>
	/// <param name="_intensity"> The intensity of the light. </param>
	/// <param name="_colour"> The colour. </param>
	PointLight(const glm::vec3 _position, const float_t _intensity, const Colour _colour) : m_position(_position), m_intensity(_intensity), m_colour(_colour) { }

	/// <summary> The position of the light within the world. </summary>
	glm::vec3 m_position;

	/// <summary> The intensity of the light. </summary>
	float_t m_intensity;

	/// <summary> The colour of the light. </summary>
	Colour m_colour;
};
#endif