#include "Sphere.h"

// Framework includes.
#include <gtx/norm.hpp>

/// <summary> Calculates the colour of a certain point on the sphere. </summary>
/// <param name="_intersection"> The point on the sphere for which to calculate the colour. </param>
/// <param name="_normal"> The pre-calculated normal from the centre of the sphere to the intersection point. </param>
/// <param name="_lightSource"> The light source to check against. </param>
/// <returns> The calculated colour on the given intersection point on this sphere. </returns>
Colour Shapes::Sphere::Shade(const glm::vec3 _intersection, const glm::vec3 _normal, const PointLight _lightSource) const
{
	// Calulate the direction from the intersection point to the light source.
	glm::vec3 directionToLight = glm::normalize(_lightSource.m_position - _intersection);

	// Calculate the scalar for the light intensity based off the dot product of the normal and the direction towards the light.
	float_t facingAmount = glm::dot(_normal, directionToLight);

	// If the facing is 0 or lower, just return black.
	if (facingAmount <= 0.0f) { return Colour::Black(); }

	// Calculate and return the final colour.
	return m_properties.m_colour * _lightSource.m_colour * facingAmount * _lightSource.m_intensity;
}

/// <summary> Finds if the given ray intersects with this sphere. </summary>
/// <param name="_ray"> The ray to check against. </param>
/// <returns> The result of the check. </returns>
SphereIntersection Shapes::Sphere::RayIntersects(const Ray _ray) const
{
	// Create an empty intersection object to hold the result.
	SphereIntersection result = SphereIntersection::Empty();

	// If the ray starts within this sphere, return the empty result.
	if (glm::length2(m_centre - _ray.m_origin) < glm::pow(m_radius, 2)) { return result; }

	// Otherwise, calculate the intersection as normal.
	else
	{
		// Calculate the dot product between the ray's direction and the direction towards the centre of the sphere from the ray's origin.
		float_t sphereRayDot = glm::dot(m_centre - _ray.m_origin, _ray.m_direction);

		// If the dot product is less than or equal to 0, the sphere is beyond the ray intersecting it, so return the empty result.
		if (sphereRayDot <= 0) { return result; }

		// Otherwise, calculate the intersection.
		else
		{
			// Calculates the closest point of the ray to this sphere.
			glm::vec3 closestPoint = _ray.ClosestPoint(m_centre);

			// Calculate the squared distance between the closest point and the centre of this sphere.
			float_t squaredDistance = glm::length2(m_centre - closestPoint);

			// If the distance is exactly the radius, there was one intersection.
			if (squaredDistance == glm::pow(m_radius, 2))
			{
				result.m_didHit = true;
				result.m_firstIntersection = closestPoint;
				result.m_secondIntersection = closestPoint;
				result.m_distance = glm::length(closestPoint - _ray.m_origin);

				return result;
			}

			// If the distance is shorter than the radius, there were two intersections.
			else if (squaredDistance < glm::pow(m_radius, 2))
			{
				// Calculate the length between the closest point and circle radius.
				float_t closestRadiusLength = glm::sqrt(glm::pow(m_radius, 2) - squaredDistance);

				result.m_didHit = true;
				result.m_firstIntersection = _ray.m_origin + (sphereRayDot - closestRadiusLength) * _ray.m_direction;
				result.m_secondIntersection = _ray.m_origin + (sphereRayDot + closestRadiusLength) * _ray.m_direction;
				result.m_distance = glm::length(result.m_firstIntersection - _ray.m_origin);

				return result;
			}

			// Otherwise, there were none.
			else { return result; }
		}
	}
}
