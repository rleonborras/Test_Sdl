
#include "SDL\include\SDL.h"
#include <iostream>
#include "SDL_image\include\SDL_image.h"



#include "Colors.h"
#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
//#pragma comment(lib,"SDL_Image/libx86/SDL2_image.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;
SDL_Surface* screenSurface= nullptr ;


bool init() {

	//initialization variable
	bool succes = true;

	//initialize SDL


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		succes = false;
	}
	else {
		//Create Window(this only creates the "marco" of the windows, here we cannot draw anything)
		window = SDL_CreateWindow("AWESOME GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if (window == NULL) {
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

bool Hit(SDL_Rect Shoot, SDL_Rect Objective) {

	for (int i = Shoot.x; i < Shoot.x + Shoot.w; ++i) {
		for (int j = Shoot.y; j < Shoot.y + Shoot.h; ++j) {
			if ((i >= Objective.x && i <= Objective.x + Objective.w) && (j >= Objective.y && j <= Objective.y + Objective.h)) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char* argv[]) {


	int Velocity = 3;
	srand(9);
	float timeCharging=0;
	bool ChargeShot = false;
	bool Charged = false;
	bool ePress = false;
	bool Up = false;
	bool Down = false;
	bool Left = false;
	bool Right = false;
	bool Space = false;
	bool Shooting = false;
	bool quit = false;
	bool collx = false;
	bool colly = false;
	int colorVar = 0;
	SDL_Event e;
	Uint32 rectColor;
	Uint32 rectColorPickup;
	Uint32 ShootColor;
	SDL_Rect rect;
	SDL_Rect rectPickup;
	SDL_Rect Shoot;

	rect.x = 200;
	rect.y = 120+50;
	rect.w = 40;
	rect.h = 40;
	Shoot.w = 30;
	Shoot.h= 5;
	rectPickup.x=rand()%SCREEN_WIDTH; //40
	rectPickup.y = rand() % SCREEN_HEIGHT; //40
	rectPickup.w = 30;
	rectPickup.h = 30;

	//handle events on queue

		//start up SDL and create a window
	
	init();

		//fill the surface blue
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, BLUE));
		//UPdate the surface ( we have to do this every time we want to draw something in screen)

		rectColor = SDL_MapRGB(screenSurface->format, RED);
		rectColorPickup = SDL_MapRGB(screenSurface->format, GREEN);
		ShootColor = SDL_MapRGB(screenSurface->format, GREEN);
		SDL_FillRect(screenSurface, &Shoot, ShootColor);
		SDL_FillRect(screenSurface, &rect, rectColor);

	

	while(!quit){

			while (SDL_PollEvent(&e) != 0) // This gets an event so this will happens until SDLQUIT(in this case pres the x button) happens)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				if (e.type == SDL_KEYDOWN) {

					switch (e.key.keysym.sym)
					{
					case SDLK_d:
						Right = true;
						break;
					case SDLK_a:
						Left = true;
						break;
					case SDLK_w:
						Up = true;
						break;
					case SDLK_s:
						Down = true;
						break;
					case SDLK_SPACE:
						Space = true;
						break;
					case SDLK_e:
						ePress = true;
						break;
					}
				}
				if (e.type == SDL_KEYUP) {
					switch (e.key.keysym.sym)
					{
					case SDLK_d:
						Right = false;
						break;
					case SDLK_a:
						Left = false;
						break;
					case SDLK_w:
						Up = false;
						break;
					case SDLK_s:
						Down = false;
						break;
					case SDLK_SPACE:
						Space = false;
						break;
					case SDLK_e:
						ePress = false;
						timeCharging += 0.1;
					default:
						break;
					}
				}
			}
		
				if (Left&&(rect.x>=0)) {
					rect.x -= Velocity;
				}
				if (Right&&(rect.x<=SCREEN_WIDTH - rect.w)) {
					rect.x += Velocity;
				}
				if (Up&&(rect.y>=0)) {
					rect.y -= Velocity;
				}
				if (Down&&(rect.y<=SCREEN_HEIGHT-rect.h)) {
					rect.y += Velocity;
				}
				if (Space && !Shooting) {
					Shoot.x = rect.x + rect.w;
					Shoot.y = rect.y + (rect.h / 2);
					Shooting = true;
				}
				if (ePress&!ChargeShot) {
					Shoot.x = rect.x + rect.w;
					Shoot.y = rect.y + (rect.h / 2);
					ChargeShot = true;
					Shoot.w = 30;
					Shoot.h = 5;
				}

			if (Shooting&&!ePress) {
				Shoot.w = 30;
				Shoot.h = 5;
				if (Shoot.x < SCREEN_WIDTH) {
					Shoot.x += 5;
					if (Hit(Shoot, rectPickup) == true) {
						rectPickup.x = rand() % 541 + 100; //40
						rectPickup.y = rand() % 380 + 100; //40
					}

				}
				else
					Shooting = false;
			}
			if (ChargeShot&&ePress) {	
			
				Shoot.x = rect.x + rect.w;
				Shoot.y = rect.y + (rect.h / 2);
				if(!Charged||Shoot.w<=70||Shoot.h<=70) {
					Shoot.w += 1;
					Shoot.h += 2;
	
					timeCharging += 0.1;
					if (timeCharging >= 0.2)
						Charged = true;
				}
			}
			if (Charged||Shoot.x<SCREEN_WIDTH) {
				Shoot.x += 25;
				if (Hit(Shoot, rectPickup) == true) {
					rectPickup.x = rand() % 541 + 100; //40
					rectPickup.y = rand() % 380 + 100; //40
				}
			
			}
			else {
			
				timeCharging = 0;
			
			}
	
			//Updating the windows surface.
	
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, BLUE));
			SDL_FillRect(screenSurface, &rect, rectColor);
			SDL_FillRect(screenSurface, &rectPickup, rectColorPickup);
			SDL_FillRect(screenSurface, &Shoot, ShootColor);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(10);
			
	}	
	close();

	return 0;
}


//	
//	//Change the color of the pickups and the Main block and respawn.
//	for (int i = rect.x; i < rect.x + 150; ++i) {
//		for (int j = rect.y; j < rect.y + 150; ++j) {
//			if ((i >= rectPickup.x && i <= rectPickup.x + rectPickup.w) && (j >= rectPickup.y && j <= rectPickup.y + rectPickup.h)) {
//				rectColor = rectColorPickup;
//				rectPickup.x = rand() % 500 + 20;
//				rectPickup.y = rand() % 300 + 20;
//				colorVar = rand() % 10;
//				if (colorVar == 0) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, RED);
//				}
//				else if (colorVar == 1) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, BLACK);
//				}	
//				else if (colorVar == 2) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, WHITE);
//				}
//				else if (colorVar == 3) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, YELLOW);
//				}
//				else if (colorVar == 4) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, GREEN);
//				}
//				else if (colorVar == 5) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, MAGENTA);
//				}
//				else if (colorVar == 6) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, CYAN);
//				}
//				else if (colorVar == 7) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, PINK);
//				}
//				else if (colorVar == 8) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, BROWN);
//				}
//				else if (colorVar == 9) {
//					rectColorPickup = SDL_MapRGB(screenSurface->format, ORANGE);
//				}	
//			
//				break;
//			}
//		}
//}