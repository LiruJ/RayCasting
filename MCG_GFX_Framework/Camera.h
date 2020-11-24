#ifndef CAMERA_H
#define CAMERA_H

// Framework includes.
#include <glm.hpp>

// Data includes.
#include "Ray.h"
#include "Colour.h"
#include "Sphere.h"
#include "PointLight.h"

// Utility includes.
#include <vector>

// Typedef includes.
#include <stdint.h>

namespace Rendering
{
	/// <summary> Represents a camera in 3D space. </summary>
	class Camera
	{
	public:
		Ray CreateRay(glm::vec2) const;

		/// <summary> Gets the width of the viewport. </summary>
		/// <returns> The width of the viewport in pixels. </returns>
		inline uint16_t GetWidth() const { return (uint16_t)m_viewportSize.x; }

		/// <summary> Gets the width of the viewport. </summary>
		/// <returns> The width of the viewport in pixels. </returns>
		inline uint16_t GetHeight() const { return (uint16_t)m_viewportSize.y; }

		Colour TraceRay(Ray, std::vector<Shapes::Sphere>, PointLight, const uint8_t _remainingReflections = 5) const;

		/// <summary> Traces a ray from the given pixel position on the screen. </summary>
		/// <param name="_pixelPosition"> The position on the screen in pixels. </param>
		/// <param name="_spheres"> The spheres within the world. </param>
		/// <param name="_lightSource"> The world's light source. </param>
		/// <returns> The colour at the end of the ray. </returns>
		inline Colour TraceRay(const glm::vec2 _pixelPosition, const std::vector<Shapes::Sphere> _spheres, const PointLight _lightSource) const { return TraceRay(CreateRay(_pixelPosition), _spheres, _lightSource); }

		static Camera& FromLookAt(glm::vec2, glm::vec3, glm::vec3);
	private:
		/// <summary> The private constructor to create a basic camera with just the width and height. </summary>
		/// <param name="_viewportSize"> The size of the viewport in pixels. </param>
		Camera(const glm::vec2 _viewportSize) : m_viewportSize(_viewportSize) { }

		/// <summary> The width and height of the viewport. </summary>
		glm::vec2 m_viewportSize;

		/// <summary> The projection matrix. </summary>
		glm::mat4 m_projection;

		/// <summary> The inverted projection matrix. </summary>
		glm::mat4 m_invertedProjection;

		/// <summary> The view matrix. </summary>
		glm::mat4 m_view;

		/// <summary> The inverted view matrix. </summary>
		glm::mat4 m_invertedView;
	};
}
#endif