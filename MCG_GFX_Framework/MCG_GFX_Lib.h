#ifndef __MCG_MAIN__
#define __MCG_MAIN__

// SDL includes.
#include <SDL.h>

// The GLM library contains vector and matrix functions and classes for us to use
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations

// Forward declaration.
class Game;

/// The MCG namespace provides all the functions to draw a pixel to the screen.
/// You should not be modifying this code for your assignment, you must use it as-is.
namespace MCG
{
	/// Initialises window to specified size
	/// The windowSize parameter specifies how many pixels wide and high the window should be
	/// \return False if something went wrong
	bool Init( glm::ivec2 windowSize );

	/// Sets every pixel to specified colour
	/// The colour parameter ranges from 0 to 255. Values outside this range may give unpredictable results.
	void SetBackground( glm::ivec3 colour );

	/// Draws a single pixel to screen
	/// The position parameter is in pixel-coordinates, ranging from 0,0 to the size of the screen set with the Init function. If coordinates are out of bounds, does nothing.
	/// The colour parameter ranges from 0 to 255. Values outside this range may give unpredictable results.
	void DrawPixel( glm::ivec2 position, glm::ivec3 colour );

	void DrawTexture(SDL_Texture* texture);

	/// Displays graphics to screen and keeps window open until user requests exit (pressing escape key or closing window)
	int ShowAndHold();

	/// \return False when user requests program exit
	bool ProcessFrame(Game&);

	/// For cleanly shutting down the graphics system
	void Cleanup();

	SDL_Renderer* GetRenderer();
};
#endif