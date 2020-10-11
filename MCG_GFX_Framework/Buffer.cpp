#include "Buffer.h"

/// <summary> Creates and returns a buffer based off of this buffer, with each pixel being averaged based on the given level. </summary>
/// <param name="_level"> The level of super-sampling to perform. </param>
/// <returns> The super-sampled buffer. </returns>
Buffer& Buffer::SuperSample(const uint8_t _level) const
{
	// Create a new buffer for the output.
	Buffer* sampledBuffer = new Buffer(m_width / _level, m_height / _level);

	// Go over every pixel between each sampled point and get the average colour.
	for (uint16_t x = 0; x < sampledBuffer->GetWidth(); x++)
	{
		for (uint16_t y = 0; y < sampledBuffer->GetHeight(); y++)
		{
			sampledBuffer->SetPixel(x, y, GetAverage(x * _level, y * _level, _level));
		}
	}

	// Dereference and return the created buffer.
	return *sampledBuffer;
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
			// Add the squared rgb values.
			r += glm::pow(m_data[dataX][dataY].r, 2);
			g += glm::pow(m_data[dataX][dataY].g, 2);
			b += glm::pow(m_data[dataX][dataY].b, 2);
		}
	}

	// Calculate the total number of covered pixels.
	uint32_t coveredPixels = (maxX - _x) * (maxY - _y);

	// Return a colour with the average values.
	return Colour(glm::min((uint32_t)glm::sqrt(r / coveredPixels), (uint32_t)CHAR_MAX), glm::min((uint32_t)glm::sqrt(g / coveredPixels), (uint32_t)CHAR_MAX), glm::min((uint32_t)glm::sqrt(b / coveredPixels), (uint32_t)CHAR_MAX));
}
