#ifndef RAY_H
#define RAY_H

// Framework includes.
#include <glm.hpp>

/// <summary> Represents a ray with an origin and a direction. </summary>
struct Ray
{
	/// <summary> Creates an empty ray starting at the world origin and pointing towards nothing. </summary>
	Ray() : m_origin(glm::vec3(0, 0, 0)), m_direction(glm::vec3(0, 0, 0)) { }

	/// <summary> Creates a ray at the given position pointing in the given direction. </summary>
	/// <param name="_origin"> The origin position. </param>
	/// <param name="_direction"> The direction. </param>
	Ray(const glm::vec3 _origin, const glm::vec3 _direction) : m_origin(_origin), m_direction(_direction) { }

	/// <summary> The position whence the ray starts. </summary>
	glm::vec3 m_origin;

	/// <summary> The position towards which the ray points. </summary>
	glm::vec3 m_direction;

	/// <summary> Calculates the closest point on this ray to the given position. </summary>
	/// <param name="_position"> The position to find the closest point to. </param>
	/// <returns> The closest point on this ray to the given position. </returns>
	inline glm::vec3 ClosestPoint(const glm::vec3 _position) const { return m_origin + glm::dot<float_t>(_position - m_origin, m_direction) * m_direction; }
};
#endif