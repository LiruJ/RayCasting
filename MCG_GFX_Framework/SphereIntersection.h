#ifndef SPHEREINTERSECTION_H
#define SPHEREINTERSECTION_H

// Framework includes.
#include <GLM/glm.hpp>

// Typedef includes.
#include <cmath>

/// <summary> Represents the outcome of a sphere-ray intersection check. </summary>
struct SphereIntersection
{
	/// <summary> Creates an empty intersection object. </summary>
	SphereIntersection() : m_didHit(false), m_distance(0), m_firstIntersection(glm::vec3(0, 0, 0)), m_secondIntersection(glm::vec3(0, 0, 0)) { }

	/// <summary> <c>true</c> if the intersection happened; otherwise, <c>false</c>. </summary>
	bool m_didHit;

	/// <summary> The distance from the origin of the first intersection. </summary>
	float_t m_distance;

	/// <summary> The position of the first intersection. </summary>
	glm::vec3 m_firstIntersection;

	/// <summary> The position of the second intersection. </summary>
	glm::vec3 m_secondIntersection;

	/// <summary> Returns an empty intersection. </summary>
	/// <returns> An empty intersection. </returns>
	/// <remarks> For some reason C++ doesn't call the default constructor, so I made a function that calls it instead and C++ is stupid enough to fall for it. </remarks>
	static SphereIntersection& Empty() { return SphereIntersection(); }
};
#endif