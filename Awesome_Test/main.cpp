#include "SDL\include\SDL.h"
#include <cstdlib>
#include <stdio.h>
#define BLUE 0x00,0x00,0xFF
#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

int main(int argc, char* argv[]) {

	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("This doesnt work");
	}

	else

	{
		//Create Window(this only creates the "marco" of the windows, here we cannot draw anything)
		window = SDL_CreateWindow("SDL TUTORIAL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
		}
		else {
			//get window surface(whit this we can draw on the windows we've already created before)
			screenSurface = SDL_GetWindowSurface(window);
			//fill the surface blue
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, BLUE));
			//UPdate the surface ( we have to do this every time we want to draw something in screen)
			SDL_UpdateWindowSurface(window);

			SDL_Delay(2000);
		}
	}
	//Destroy window
	SDL_DestroyWindow(window);
	// Quit from SDL subsystems
	SDL_Quit();

	return 0;
}