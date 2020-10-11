#include "Camera.h"

// Framework includes.
#include <GLM/gtc/matrix_transform.hpp>

/// <summary> Creates a ray from the given screen position. </summary>
/// <param name="_pixelPosition"> The pixel position on the screen. </param>
/// <returns> A ray from the given pixel in world space in the direction of the projection. </returns>
Ray Rendering::Camera::CreateRay(const glm::vec2 _pixelPosition) const
{
	// Convert the pixel position to device position.
	float_t deviceX = ((_pixelPosition.x / m_viewportSize.x) * 2) - 1;
	float_t deviceY = ((_pixelPosition.y / m_viewportSize.y) * 2) - 1;

	// Calculate the start and end points.
	glm::vec4 start = m_invertedProjection * glm::vec4(-deviceX, -deviceY, -1, 1);
	glm::vec4 end = m_invertedProjection * glm::vec4(-deviceX, -deviceY, 1, 1);

	// Divide by w as the previous calculations lose it.
	start /= start.w;
	end /= end.w;

	// Convert into world space.
	start = m_invertedView * start;
	end = m_invertedView * end;

	// Create and return the ray.
	return Ray(glm::vec3(start), glm::normalize(glm::vec3(end - start)));
}

/// <summary> Calculates the final colour found at the end of the ray. </summary>
/// <param name="_ray"> The ray. </param>
/// <param name="_spheres"> The spheres within the world. </param>
/// <param name="_lightSource"> The world's light source. </param>
/// <param name="_remainingReflections"> The amount of reflections to do, reduced every time a reflection is made. Defaults to <c>5</c>. </param>
/// <returns> The colour at the end of the ray. </returns>
Colour Rendering::Camera::TraceRay(const Ray _ray, const std::vector<Shapes::Sphere> _spheres, const PointLight _lightSource, const uint8_t _remainingReflections) const
{
	// Store a sphere intersection, as well as the sphere it pertains to.
	SphereIntersection sphereIntersect = SphereIntersection::Empty();
	Shapes::Sphere intersectedSphere = Shapes::Sphere();

	// Keep track of the shortest distance, initialise to a very large number.
	float_t shortestDistance = INT32_MAX;

	// Iterate through the spheres to find the closest one hit by the ray.
	for (uint16_t sphereIndex = 0; sphereIndex < _spheres.size(); sphereIndex++)
	{
		// Test the ray against this sphere.
		SphereIntersection currentSphereIntersect = _spheres[sphereIndex].RayIntersects(_ray);

		// If the ray hit and the distance is shorter than the current shortest distance.
		if (currentSphereIntersect.m_didHit && currentSphereIntersect.m_distance < shortestDistance)
		{
			// Set the shortest distance to this distance.
			shortestDistance = currentSphereIntersect.m_distance;

			// Set the sphere data.
			sphereIntersect = currentSphereIntersect;
			intersectedSphere = _spheres[sphereIndex];
		}
	}

	// If the ray hit nothing, return the background colour.
	if (!sphereIntersect.m_didHit) { return Colour(0, 0, 64); }

	// Otherwise, work out what should happen with the resulting hit.
	else
	{
		// Get the normal of the intersection on the sphere.
		glm::vec3 intersectionNormal = glm::normalize(sphereIntersect.m_firstIntersection - intersectedSphere.m_centre);

		// Create a ray starting from the intersection point and travelling towards the light source.
		Ray shadowRay(sphereIntersect.m_firstIntersection, glm::normalize(_lightSource.m_position - sphereIntersect.m_firstIntersection));

		// Check the shadow ray against every sphere, if any are hit, return black.
		for (uint16_t sphereIndex = 0; sphereIndex < _spheres.size(); sphereIndex++)
		{
			if (_spheres[sphereIndex].m_centre != intersectedSphere.m_centre && _spheres[sphereIndex].RayIntersects(shadowRay).m_didHit) { return Colour::Black(); }
		}

		// If the hit sphere is reflective, get the colour from the reflection.
		if (intersectedSphere.m_properties.m_reflectiveness > 0.0f)
		{
			// Calculate the direction of the reflection.
			glm::vec3 reflectionNormal = 2.0f * glm::dot(-_ray.m_direction, intersectionNormal) * intersectionNormal + _ray.m_direction;

			// Create a ray starting from the intersection point and travelling directly away from the sphere.
			Ray reflectionRay(sphereIntersect.m_firstIntersection, reflectionNormal);

			// Get the current colour of the hit sphere, with its inverse reflectiveness applied.
			Colour currentColour = intersectedSphere.Shade(sphereIntersect.m_firstIntersection, intersectionNormal, _lightSource) * (1.0f - intersectedSphere.m_properties.m_reflectiveness);

			// Get the colour of the reflected ray, with the reflectiveness of the hit sphere applied.
			Colour reflectedColour = TraceRay(reflectionRay, _spheres, _lightSource, _remainingReflections - 1) * intersectedSphere.m_properties.m_reflectiveness;

			// If there are reflections remaining, trace the ray recursively and combine the colours based off the hit sphere's reflectiveness.
			if (_remainingReflections > 0) { return reflectedColour + currentColour; }
		}

		// Return the basic shade.
		return intersectedSphere.Shade(sphereIntersect.m_firstIntersection, intersectionNormal, _lightSource);
	}
}

/// <summary> Creates and returns a new camera with the given size at the given position looking at the second position. </summary>
/// <param name="_viewportSize"> The size of the viewport in pixels </param>
/// <param name="_position"> The position of the camera within the world. </param>
/// <param name="_lookAt"> The world position at which to look. </param>
/// <returns> The complete camera. </returns>
Rendering::Camera& Rendering::Camera::FromLookAt(const glm::vec2 _viewportSize, const glm::vec3 _position, const glm::vec3 _lookAt)
{
	// Create a basic camera with just the width and height set.
	Camera* camera = new Camera(_viewportSize);

	// Initilise the projection matrix to a standard fov.
	camera->m_projection = glm::perspective<float_t>(glm::radians(45.0f), _viewportSize.x / _viewportSize.y, 0.1f, 1000.0f);

	// Initialise the view matrix.
	camera->m_invertedView = glm::lookAt(_position, _lookAt, glm::vec3(0, 1, 0));
	camera->m_view = glm::inverse(camera->m_invertedView);

	// Save the inverted projection matrix.
	camera->m_invertedProjection = glm::inverse(camera->m_projection);

	// Return the camera.
	return *camera;
}
