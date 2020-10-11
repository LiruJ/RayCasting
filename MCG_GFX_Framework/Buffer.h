#ifndef BUFFER_H
#define BUFFER_H

// Data includes.
#include "Colour.h"

// Utility includes.
#include <vector>

// Typedef includes.
#include <stdint.h>

/// <summary> Represents a buffer of colours to be drawn. </summary>
/// <remarks> Removes some multi-threading issues with SDL. </remarks>
class Buffer
{
public:
	/// <summary> Create a new buffer with the given size. </summary>
	/// <param name="_width"> The width in pixels. </param>
	/// <param name="_height"> The height in pixels. </param>
	Buffer(const uint16_t _width, const uint16_t _height) : m_width(_width), m_height(_height), m_data(std::vector<std::vector<Colour>>(_width))
	{
		// Initialise the vectors.
		for (uint16_t x = 0; x < _width; x++) { m_data[x] = std::vector<Colour>(_height); }
	}

	/// <summary> Gets the colour at the given pixel position, or black if the given position is out of range. </summary>
	/// <param name="_x"> The x position of the pixel. </param>
	/// <param name="_y"> The y position of the pixel. </param>
	/// <returns> The colour at the given pixel position, or black if the given position is out of range. </returns>
	inline Colour AtPixel(const uint16_t _x, const uint16_t _y) const { return (inBounds(_x, _y)) ? m_data[_x][_y] : Colour::Black(); }

	/// <summary> Sets the colour at the given pixel position to the given colour, does nothing if the given position is out of range. </summary>
	/// <param name="_x"> The x position of the pixel. </param>
	/// <param name="_y"> The y position of the pixel. </param>
	/// <param name="_colour"> The colour to which the pixel is set. </param>
	inline void SetPixel(const uint16_t _x, const uint16_t _y, const Colour _colour) { if (inBounds(_x, _y)) { m_data[_x][_y] = _colour; } }
	
	/// <summary> Gets the width of the buffer. </summary>
	/// <returns> The width of the buffer in pixels. </returns>
	inline uint16_t GetWidth() const { return m_width; }

	/// <summary> Gets the height of the buffer. </summary>
	/// <returns> The height of the buffer in pixels. </returns>
	inline uint16_t GetHeight() const { return m_height; }

	Buffer& SuperSample(uint8_t) const;
private:
	/// <summary> The width of the buffer. </summary>
	uint16_t m_width;

	/// <summary> The height of the buffer. </summary>
	uint16_t m_height;

	/// <summary> the colour data. </summary>
	std::vector<std::vector<Colour>> m_data;

	/// <summary> Finds if the given position is in bounds. </summary>
	/// <param name="_x"> The x position. </param>
	/// <param name="_y"> The y position. </param>
	/// <returns> <c>true</c> if the given position is in range; otherwise, <c>false</c>. </returns>
	inline bool inBounds(const uint16_t _x, const uint16_t _y) const { return _x >= 0 && _y >= 0 && _x < m_width && _y < m_height; }

	Colour GetAverage(uint16_t, uint16_t, uint8_t) const;
};
#endif