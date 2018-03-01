
#include "SDL\include\SDL.h"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "Colors.h"

#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;
SDL_Surface* screenSurface =nullptr;

SDL_KeyboardEvent Button;

bool init() {

	//initialization variable
	bool succes = true;

	//initialize SDL


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf( "This doesn't work" );
		succes = false;
	}
	else {
		//Create Window(this only creates the "marco" of the windows, here we cannot draw anything)
		window = SDL_CreateWindow("AWESOME GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf(" Window could not be created! SDL_ERROR: %s \n", SDL_GetError());
			succes = false;
		}
		else {
			//Getting the windows.
			screenSurface = SDL_GetWindowSurface(window);
		}

	}
	return succes;
}


void close() {
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit from SDL subsystems
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	
	srand(time(NULL));
	bool quit = false;
	bool collx = false;
	bool colly = false;
	//DETECTION CONTROLS
	bool UP = false;
	bool DOWN = false;
	bool LEFT = false;
	bool RIGHT = false;
	int colorVar = 0;
	int nosameColor;
	SDL_Event e;
	Uint32 rectColor;
	Uint32 rectColorPickup;
	SDL_Rect rect;
	SDL_Rect rectPickup;
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	rect.x = 200;
	rect.y = 120+50;
	rect.w = 150;
	rect.h = 150;
	rectPickup.x=rand()%641; //40
	rectPickup.y = rand() % 480; //40
	rectPickup.w = 30;
	rectPickup.h = 30;
	//handle events on queue
	const Uint8 *state = SDL_GetKeyboardState(NULL);

		//start up SDL and create a window
	if (!init()) {
		
	}
	else {
		//fill the surface blue
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, BLUE));
		//UPdate the surface ( we have to do this every time we want to draw something in screen)
		SDL_UpdateWindowSurface(window);
		rectColor = SDL_MapRGB(screenSurface->format, RED);
		rectColorPickup = SDL_MapRGB(screenSurface->format, GREEN);
		SDL_FillRect(screenSurface, &rect, rectColor);
	}

	while (!quit) {

		while (SDL_PollEvent(&e) != 0) // This gets an event so this will happens until SDLQUIT(in this case pres the x button) happens)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//User Prees a key;
		
				//while (rect.x < 640 || rect.x>0 || rect.y < 480 || rect.y>0) {  //Delimitation zone
				
				if (state[SDL_SCANCODE_A]) {
					rect.x-= 8;
				}
				else if (state[SDL_SCANCODE_W]) {
					rect.y -= 8;
				}
				else if (state[SDL_SCANCODE_D]) {
					rect.x += 8;
				}
				else if (state[SDL_SCANCODE_S]) {
					rect.y += 8;
				}
			
		}
		//Updating the windows surface.
		SDL_UpdateWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, BLUE));
		SDL_FillRect(screenSurface, &rect, rectColor);
		SDL_FillRect(screenSurface, &rectPickup, rectColorPickup);
		SDL_Delay(1);
	}
close();

return 0;
}
	 

// Change the color of the pickups and the Main block and respawn.
/*for (int i = rect.x; i < rect.x + 150; ++i) {
for (int j = rect.y; j < rect.y + 150; ++j) {
if ((i >= rectPickup.x && i <= rectPickup.x + rectPickup.w) && (j >= rectPickup.y && j <= rectPickup.y + rectPickup.h)) {
rectColor = rectColorPickup;
rectPickup.x = rand() % 500 + 20;
rectPickup.y = rand() % 300 + 20;
nosame = colorVar;
colorVar = rand() % 10;
while (colorVar == nosame) {
colorVar = rand() % 10;
}
if (colorVar == 0) {
rectColorPickup = SDL_MapRGB(screenSurface->format, RED);
}
else if (colorVar == 1) {
rectColorPickup = SDL_MapRGB(screenSurface->format, BLACK);
}
else if (colorVar == 2) {
rectColorPickup = SDL_MapRGB(screenSurface->format, WHITE);
}
else if (colorVar == 3) {
rectColorPickup = SDL_MapRGB(screenSurface->format, YELLOW);
}
else if (colorVar == 4) {
rectColorPickup = SDL_MapRGB(screenSurface->format, GREEN);
}
else if (colorVar == 5) {
rectColorPickup = SDL_MapRGB(screenSurface->format, MAGENTA);
}
else if (colorVar == 6) {
rectColorPickup = SDL_MapRGB(screenSurface->format, CYAN);
}
else if (colorVar == 7) {
rectColorPickup = SDL_MapRGB(screenSurface->format, PINK);
}
else if (colorVar == 8) {
rectColorPickup = SDL_MapRGB(screenSurface->format, BROWN);
}
else if (colorVar == 9) {
rectColorPickup = SDL_MapRGB(screenSurface->format, ORANGE);
}

break;
}
}
}*/


