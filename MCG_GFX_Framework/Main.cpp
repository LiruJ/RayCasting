// Framework includes.
#include "MCG_GFX_Lib.h"
#include <GLM/glm.hpp>

// Data includes.
#include "Game.h"

int main( int argc, char *argv[] )
{
	// The size of the window.
	glm::ivec2 windowSize( 1920, 1000 );

	// Initialise the window.
	if(!MCG::Init(windowSize)) { return -1; }

	// Create a game object to render and handle the world.
	Game game = Game(windowSize, 8, 2);

	// Keep rendering the same frame and taking user input until they wish to quit.
	while (MCG::ProcessFrame(game)) {};
}
