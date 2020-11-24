#include "Buffer.h"

// Threading includes.
#include <thread>

// Utility includes.
#include <iostream>

/// <summary> Creates and returns a buffer based off of this buffer, with each pixel being averaged based on the given level. </summary>
/// <param name="_level"> The level of super-sampling to perform. </param>
/// <returns> The super-sampled buffer. </returns>
Buffer& Buffer::SuperSample(const uint8_t _level, const uint8_t _threadAmount)
{
	// Track each thread.
	std::vector<std::thread> threads(_threadAmount);

	// Create a new buffer for the output.
	Buffer* sampledBuffer = new Buffer(m_width / _level, m_height / _level);

	// Begin each thread and add them to the vector.
	for (uint8_t t = 0; t < _threadAmount; t++)
	{
		threads[t] = std::thread(&Buffer::sampleVertical, this, t, _threadAmount, _level, std::ref(*sampledBuffer));
	}

	// Wait for each thread to be done before returning.
	for (uint8_t t = 0; t < _threadAmount; t++)
	{
		// Wait for the thread to finish.
		threads[t].join();

		// Output the progress.
		std::cout << ((100.0f / _threadAmount) * (t + 1)) << "% sampled." << std::endl;
	}

	// Dereference and return the created buffer.
	return *sampledBuffer;
}

SDL_Texture* Buffer::CreateTexture(SDL_Renderer& renderer)
{
	// Create a surface with the pixel data.
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(m_data, m_width, m_height, 24, m_width * 3, SDL_PIXELFORMAT_RGB24);

	// Create a texture from the surface.
	SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, surface);

	// Free the surface.
	SDL_FreeSurface(surface);
	surface = nullptr;

	// Return the texture.
	return texture;
}

void Buffer::sampleVertical(const uint8_t _threadNumber, const uint8_t _threadCount, const uint8_t _level, Buffer& o_buffer)
{
	// Go over every pixel between each sampled point and get the average colour.
	for (uint16_t x = _threadNumber; x < o_buffer.GetWidth(); x += _threadCount)
	{
		for (uint16_t y = 0; y < o_buffer.GetHeight(); y++)
		{
			o_buffer.SetPixel(x, y, GetAverage(x * _level, y * _level, _level));
		}
	}
}

/// <summary> Gets the average colour of the pixels at the given position with the given size. </summary>
/// <param name="_x"> The x position of the pixel. </param>
/// <param name="_y"> The y position of the pixel. </param>
/// <param name="_level"> The width and height of the area to average. </param>
/// <returns> The average colour from the given area. </returns>
Colour Buffer::GetAverage(const uint16_t _x, const uint16_t _y, const uint8_t _level) const
{
	// Start with black rgb.
	uint32_t r = 0, g = 0, b = 0;

	// Calculate the max x and y.
	uint16_t maxX = glm::min(_x + _level, m_width - 1);
	uint16_t maxY = glm::min(_y + _level, m_height - 1);

	// Go over every pixel in range.
	for (uint16_t dataX = _x; dataX < maxX; dataX++)
	{
		for (uint16_t dataY = _y; dataY < maxY; dataY++)
		{
			Colour pixel = AtPixel(dataX, dataY);

			// Add the squared rgb values.
			r += pixel.r * pixel.r;
			g += pixel.g * pixel.g;
			b += pixel.b * pixel.b;
		}
	}

	// Calculate the total number of covered pixels.
	uint32_t coveredPixels = (maxX - _x) * (maxY - _y);

	// Return a colour with the average values.
	return Colour(glm::min((uint32_t)glm::sqrt(r / coveredPixels), (uint32_t)CHAR_MAX), glm::min((uint32_t)glm::sqrt(g / coveredPixels), (uint32_t)CHAR_MAX), glm::min((uint32_t)glm::sqrt(b / coveredPixels), (uint32_t)CHAR_MAX));
}
