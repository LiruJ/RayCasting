#ifndef GAME_H
#define GAME_H

// Framework includes.
#include <GLM/glm.hpp>

// Data includes.
#include "World.h"

// Typedef includes.
#include <stdint.h>

/// <summary> Represents a container that allows for functions to be called to manipulate the world. </summary>
class Game
{
public:
	/// <summary> Creates the game with the given window size, threads, and sample rate. </summary>
	/// <param name="_windowSize"> The size of the window in pixels. </param>
	/// <param name="_threadAmount"> The number of threads to use for rendering. Defaults to <c>1</c>. </param>
	/// <param name="_samples"> The sample rate to use for rendering. Defaults to <c>1</c>. </param>
	Game(const glm::ivec2 _windowSize, const uint8_t _threadAmount = 1, const uint8_t _samples = 1) : m_windowSize(_windowSize), m_world(World(_windowSize * (int)_samples)), m_threads(_threadAmount), m_samples(_samples) { draw(); }

	/// <summary> Change the sample rate multiplier, then draw. </summary>
	/// <param name="_newSamples"> The number of samples to use. </param>
	inline void ChangeSampleRate(const uint8_t _newSamples) { m_samples = _newSamples; m_world = World(m_windowSize * (int)_newSamples); draw(); }

	/// <summary> Change the amount of threads used to draw, then draw. </summary>
	/// <param name="_newThreads"> The new amount of threads to use. </param>
	inline void ChangeThreads(const uint8_t _newThreads) { m_threads = _newThreads; draw(); }
private:
	/// <summary> The size of the window. </summary>
	glm::ivec2 m_windowSize;

	/// <summary> The world to render and manipulate. </summary>
	World m_world;

	/// <summary> The amount of threads with which to render. </summary>
	uint8_t m_threads;

	/// <summary> The number of samples to make of the final buffer. </summary>
	uint8_t m_samples;

	void draw();
};
#endif