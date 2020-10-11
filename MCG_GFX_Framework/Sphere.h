#ifndef SPHERE_H
#define SPHERE_H

// Framework includes.
#include <GLM/glm.hpp>

// Data includes.
#include "ShapeProperties.h"
#include "SphereIntersection.h"
#include "Colour.h"
#include "Ray.h"
#include "PointLight.h"

// Typedef includes.
#include <cmath>

namespace Shapes
{
	/// <summary> Represents a sphere within the world. </summary>
	struct Sphere
	{
		/// <summary> Creates a default sphere with no radius. </summary>
		Sphere() : Sphere(glm::vec3(0, 0, 0), 0, ShapeProperties::MatteGrey()) { }

		/// <summary> Creates a sphere with the given properties. </summary>
		/// <param name="_centre"> The centre position. </param>
		/// <param name="_radius"> The size of the radius. </param>
		/// <param name="_properties"> The properties of the surface. </param>
		Sphere(glm::vec3 _centre, float_t _radius, ShapeProperties _properties) : m_centre(_centre), m_radius(_radius), m_properties(_properties) {}

		/// <summary> The centre of the sphere. </summary>
		glm::vec3 m_centre;

		/// <summary> The radius of the sphere. </summary>
		float_t m_radius;

		/// <summary> The properties of the sphere. </summary>
		ShapeProperties m_properties;

		Colour Shade(glm::vec3, glm::vec3, PointLight) const;

		SphereIntersection RayIntersects(Ray) const;
	};
}
#endif