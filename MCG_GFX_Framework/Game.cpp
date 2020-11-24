#include "Game.h"

// Framework includes.
#include "MCG_GFX_Lib.h"

// Data includes.
#include "Buffer.h"

// SDL includes.
#include <SDL.h>

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
	std::cout << "Rendering with " << (int)m_threads << " threads at " << (int)m_samples << "x resolution" << std::endl;

	// Start the main timer and ray timer from here.
	std::chrono::time_point<std::chrono::steady_clock> mainTimer = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> rayTimer = std::chrono::high_resolution_clock::now();

	// Draw the world at full res and save it to a buffer.
	fullResBuffer = &m_world.Draw(m_threads);

	// Print to the console that the raycasting has been finished.
	double renderTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - rayTimer).count();;
	std::cout << "Render completed in " << renderTime << "ms" << std::endl;

	// If the sample rate is greater than 1, sample and draw, otherwise draw the full res.
	if (m_samples > 1)
	{
		// Print to the console that the sampling will now take place.
		std::cout << "Super sampling at " << (int)m_samples << "x." << std::endl;

		// Start the sampling timer.
		std::chrono::time_point<std::chrono::steady_clock> sampleTimer = std::chrono::high_resolution_clock::now();

		// Super sample the buffer and save it.
		superSampledBuffer = &fullResBuffer->SuperSample(m_samples, m_threads);

		// Set the sampled buffer to be drawn.
		drawBuffer = superSampledBuffer;

		// Print the time taken to sample.
		double sampleTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - sampleTimer).count();;
		std::cout << "Sampling completed in " << sampleTime << "ms" << std::endl;
	}
	else { drawBuffer = fullResBuffer; }

	// Print that the upload is starting.
	std::cout << "Uploading texture data to GPU" << std::endl;

	// Start the upload timer here.
	std::chrono::time_point<std::chrono::steady_clock> uploadTimer = std::chrono::high_resolution_clock::now();

	// Upload the data to the GPU.
	SDL_Texture* texture = drawBuffer->CreateTexture(*MCG::GetRenderer());

	// Draw the texture.
	MCG::DrawTexture(texture);

	// Calculate the upload time and print it.
	double uploadTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - uploadTimer).count();;
	std::cout << "Uploaded texture data in " << uploadTime << "ms" << std::endl;

	// Get the time taken to render and output it to the console.
	double mainTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mainTimer).count();
	std::cout << "Took " << mainTime << "ms to render with " << (int)m_threads << " threads at " << (int)m_samples << "x super-sampling." << std::endl;

	// Now that it has been used, delete the full res and sampled buffer.
	delete fullResBuffer;
	delete superSampledBuffer;
	fullResBuffer = NULL;
	superSampledBuffer = NULL;
	drawBuffer = NULL;

	SDL_DestroyTexture(texture);
	texture = nullptr;
}