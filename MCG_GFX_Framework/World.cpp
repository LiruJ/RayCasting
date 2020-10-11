#include "World.h"

// Framework includes.
#include "MCG_GFX_Lib.h"

// Threading includes.
#include <thread>

// Utility includes.
#include <iostream>

/// <summary> Draws everything in the world using the given number of threads. </summary>
/// <param name="_threadAmount"> The amount of threads to use. </param>
/// <returns> A colour buffer with the rendered scene. </returns>
Buffer& World::Draw(const uint8_t _threadAmount)
{
	// Calculates the height of each section.
	uint16_t sectionHeight = m_camera.GetHeight() / _threadAmount;
	
	// Track each thread.
	std::vector<std::thread> threads(_threadAmount);

	// Create a buffer to hold the colours.
	Buffer* buffer = new Buffer(m_camera.GetWidth(), m_camera.GetHeight());

	// Begin each thread and add them to the vector.
	for (uint8_t t = 0; t < _threadAmount; t++) 
	{
	 	threads[t] = std::thread(&World::drawSection, this, sectionHeight * t, sectionHeight, std::ref(*buffer));
	}

	// Wait for each thread to be done before returning.
	for (uint8_t t = 0; t < _threadAmount; t++)
	{
		// Wait for the thread to finish.
		threads[t].join();

		// Output the progress.
		std::cout << ((100.0f / _threadAmount) * (t + 1)) << "% rendered." << std::endl;
	}

	// Dereference and return the buffer.
	return *buffer;
}

/// <summary> Draws the given section of the screen onto the given buffer. </summary>
/// <param name="_startY"> The y of the pixel at which to start. </param>
/// <param name="_height"> The height to draw. </param>
/// <param name="o_buffer"> THe buffer object to which the output is drawn. </param>
void World::drawSection(const uint16_t _startY, const uint16_t _height, Buffer& o_buffer)
{
	// Go over each covered pixel and cast a ray, save the result to be buffer.
	for (uint16_t x = 0; x < m_camera.GetWidth(); x++)
	{
		for (uint16_t y = _startY; y < _startY + _height; y++)
		{
		    o_buffer.SetPixel(x, y, m_camera.TraceRay(glm::vec2(x, y), m_spheres, m_lightSource));
		}
	}
}

/// <summary> Creates every sphere needed in the world. </summary>
void World::initialiseSpheres()
{
	m_spheres.push_back(Shapes::Sphere(glm::vec3(0, 0, 0), 6.0f, Shapes::ShapeProperties(Colour::Red(), 0.5f)));

	m_spheres.push_back(Shapes::Sphere(glm::vec3(-8, 0, -8), 2.5f, Shapes::ShapeProperties::MatteGrey()));

	m_spheres.push_back(Shapes::Sphere(glm::vec3(-5.5f, -10, -8), 2.5f, Shapes::ShapeProperties(Colour(255, 215, 0), 0)));

	m_spheres.push_back(Shapes::Sphere(glm::vec3(0, 9, -15), 1.75f, Shapes::ShapeProperties(Colour(255, 0, 255), 0)));

	m_spheres.push_back(Shapes::Sphere(glm::vec3(8, 8, -8), 5.0f, Shapes::ShapeProperties(Colour::Green(), 0.85f)));

	m_spheres.push_back(Shapes::Sphere(glm::vec3(-20, 9.5f, 25), 20.0f, Shapes::ShapeProperties(Colour(235, 243, 246), 0.35f)));
}
