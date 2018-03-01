
#include "SDL\include\SDL.h"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <time.h>
#define BLUE			0x00,0x00,0xFF
#define RED				0xFF,0x00,0x00
#define BLACK           0x00,0x00,0x00
#define WHITE           0xFF,0xFF,0xFF
#define YELLOW          0xFF,0xFF,0x00
#define GREEN           0x00,0xFF,0x00
#define MAGENTA         0xFF,0x00,0xFF
#define CYAN            0x00,0xFF,0xFF
#define PINK            0xFF,0xAF,0xAF
#define BROWN           0x60,0x30,0x00
#define ORANGE          0xFF,0x80,0x00
#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface ;
using namespace std;


bool init() {

	//initialization variable
	bool succes = true;

	//initialize SDL


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "This doesn't work" << endl;
		succes = false;
	}
	else {
		//Create Window(this only creates the "marco" of the windows, here we cannot draw anything)
		window = SDL_CreateWindow("AWESOME GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if (window == NULL) {
			cout << "Window could not be created! SDL_ERROR: " << SDL_GetError() << endl;
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
	int colorVar = 0;
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

		//start up SDL and create a window
	if (!init()) {
		cout << "Failed to initialize" << endl;
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

	while(!quit){

		while (SDL_PollEvent(&e) != 0) // This gets an event so this will happens until SDLQUIT(in this case pres the x button) happens)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		while (rect.x < 640||rect.x>0||rect.y<480||rect.y>0) {  //Delimitation zone
			
			//Change the color of the pickups and the Main block and respawn.
			for (int i = rect.x; i < rect.x + 150; ++i) {
				for (int j = rect.y; j < rect.y + 150; ++j) {
					if ((i >= rectPickup.x && i <= rectPickup.x + rectPickup.w) && (j >= rectPickup.y && j <= rectPickup.y + rectPickup.h)) {
						rectColor = rectColorPickup;
						rectPickup.x = rand() % 500 + 20;
						rectPickup.y = rand() % 300 + 20;
						colorVar = rand() % 10;
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
		}

			// the movement in X direction.
			// the collX is the boolean variable to determine if the box has reached the end and then change the direction.
			if (rect.x < 490 && (collx==false)) { 
				rect.x++;
			}
			else if (rect.x >= 490) {
				collx = true;
				rect.x--;
			}
			else if(rect.x>0&&(collx==true)){
				rect.x--;
			}
			else if (rect.x <=0) {
				rect.x++;
				collx = false;
			}


			// The Y direction update
			if (rect.y < 330 && (colly == false)) {
				rect.y++;
			}
			else if (rect.y >= 330) {
				colly = true;
				rect.y--;
			}
			else if (rect.y>0 && (colly == true)) {
				rect.y--;
			}
			else if (rect.y <= 0) {
				rect.y++;
				colly = false;
			}

			//Updating the windows surface.
			SDL_UpdateWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, BLUE));
			SDL_FillRect(screenSurface, &rect, rectColor);
			SDL_FillRect(screenSurface, &rectPickup, rectColorPickup);
			SDL_Delay(1);			
		}
	}	
	close();

	return 0;
}