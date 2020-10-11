#include "Game.h"

// Framework includes.
#include "MCG_GFX_Lib.h"

// Data includes.
#include "Buffer.h"

// Utility includes.
#include <chrono>
#include <iostream>

/// <summary> Draws the world and super samples it. </summary>
void Game::draw()
{
	// Create a buffer for the full res and a buffer for the sampled res, then a buffer that simply points to the buffer that needs to be drawn.
	Buffer* superSampledBuffer = NULL;
	Buffer* fullResBuffer = NULL;
	Buffer* drawBuffer = NULL;

	// Clear the screen.
	MCG::SetBackground(glm::ivec3(0, 64, 0));

	// Print to the console that rendering has started.
	std::cout << "Render begin." << std::endl;

	// Start the timer from here.
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();

	// Draw the world at full res and save it to a buffer.
	fullResBuffer = &m_world.Draw(m_threads);

	// If the sample rate is greater than 1, sample and draw, otherwise draw the full res.
	if (m_samples > 1)
	{
		// Print to the console that the render has been finished, and the sampling will now take place.
		std::cout << "Render complete, now super sampling at " << (int)m_samples << "x." << std::endl;

		// Super sample the buffer and save it.
		superSampledBuffer = &fullResBuffer->SuperSample(m_samples);

		// Set the sampled buffer to be drawn.
		drawBuffer = superSampledBuffer;
	}
	else { drawBuffer = fullResBuffer; }

	// Draw the contents of the chosen buffer.
	for (uint16_t x = 0; x < drawBuffer->GetWidth(); x++)
	{
		for (uint16_t y = 0; y < drawBuffer->GetHeight(); y++)
		{
			MCG::DrawPixel(glm::ivec2(x, y), drawBuffer->AtPixel(x, y));
		}
	}

	// Get the time taken to render and output it to the console.
	double timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	std::cout << "Took " << timeTaken << "ms to render with " << (int)m_threads << " threads at " << (int)m_samples << "x super-sampling." << std::endl;

	// Now that it has been used, delete the full res and sampled buffer.
	delete fullResBuffer;
	delete superSampledBuffer;
	fullResBuffer = NULL;
	superSampledBuffer = NULL;
	drawBuffer = NULL;
}