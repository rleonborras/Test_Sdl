
#include "SDL\include\SDL.h"
#include <iostream>
#include "SDL_image\include\SDL_image.h"



#include "Colors.h"
#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#pragma comment(lib,"SDL_image/libx86/SDL2_image.lib")
#define SHAPE_SIZE 100

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;
SDL_Surface* screenSurface= nullptr ;
SDL_Renderer* Main_Renderer=nullptr;
SDL_Texture* Background_Texture=nullptr;
SDL_Texture* Player_shipTexture = nullptr;
SDL_Texture* Enemy_shipTexture = nullptr;
SDL_Texture* Shoot_Texture = nullptr;





SDL_Texture* loadTexture(std::string path){

	//Final Texture
	SDL_Texture* newTexture = nullptr;

	//Load image from path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	newTexture = SDL_CreateTextureFromSurface(Main_Renderer, loadedSurface);
	//Delete the old loaded surface;
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

bool loadMedia() {
	bool succes = true;

	Background_Texture = loadTexture("Background.png");
	Player_shipTexture = loadTexture("Main_Ship.png");
	Enemy_shipTexture = loadTexture("Enemy_Ship.png");
	Shoot_Texture = loadTexture("Shoot_2.png");
	if (Background_Texture == NULL || Player_shipTexture == NULL || Enemy_shipTexture == NULL||Shoot_Texture==NULL) {
	succes = false;
	}
	return succes;
}

bool init() {

	//initialization variable
	bool succes = true;
	
	//initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	//Create Window(this only creates the "marco" of the windows, here we cannot draw anything)
	window = SDL_CreateWindow("AWESOME GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		succes = false;
	}
	else {
	if (window == NULL) {
		succes = false;
		}
		//Getting the windows.
		Main_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	}
	
return succes;
}

void close() {
	//free loaded images
	SDL_DestroyTexture(Background_Texture);
	Background_Texture = nullptr;
	//Destroy window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Main_Renderer);
	window = nullptr;
	Main_Renderer = nullptr;
	//Quit from SDL subsystems
	IMG_Quit();
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


	SDL_Rect SrcR;
	SDL_Rect DestR;
	SDL_Rect Ship;
	SDL_Rect Shoot;
	Shoot.w = SHAPE_SIZE;
	Shoot.h = SHAPE_SIZE;
	Shoot.x = 200;
	Shoot.y = 200;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = SHAPE_SIZE;
	SrcR.h = SHAPE_SIZE;

	Ship.x = 200;
	Ship.y = 200;
	Ship.w = SHAPE_SIZE;
	Ship.h = SHAPE_SIZE;




	int Velocity = 1;
	srand(9);
	float timeCharging=0.0;
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

	//start up SDL and create a window

	init();
	loadMedia();
	if (!loadMedia||!init) {
		quit = true;
	}
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
						
					default:
						break;
					}
				}
			}
		
				if (Left&&(Ship.x>=0)) {
					Ship.x -= Velocity;
				}
				if (Right&&(Ship.x<=SCREEN_WIDTH - Ship.w)) {
					Ship.x += Velocity;
				}
				if (Up&&(Ship.y>=0)) {
					Ship.y -= Velocity;
				}
				if (Down&&(Ship.y<=SCREEN_HEIGHT-Ship.h)) {
					Ship.y += Velocity;
				}
				if (Space && !Shooting) {
					Shoot.x = Ship.x + Ship.w;
					Shoot.y = Ship.y + (Ship.h / 2);
					Shooting = true;
				}

				/*		if (ePress&!ChargeShot) {
					Shoot.x = rect.x + rect.w;
					Shoot.y = rect.y + (rect.h / 2);
					ChargeShot = true;
					Shoot.w = 30;
					Shoot.h = 5;
				}
			*/
			if (Shooting) {

				if (Shoot.x < SCREEN_WIDTH) {
					Shoot.x += 5;
					//if (Hit(Shoot, rectPickup) == true) {
					//	rectPickup.x = rand() % 541 + 100; //40
					//	rectPickup.y = rand() % 380 + 100; //40
					//}

				}
				else
					Shooting = false;
			}/*
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
			
				timeCharging = 0.0;
			
			}*/
		
			//Updating the windows surface.
			SDL_RenderClear(Main_Renderer);
			SDL_RenderCopy(Main_Renderer, Background_Texture, NULL, NULL);
			SDL_RenderCopy(Main_Renderer,Player_shipTexture,NULL, &Ship);
			SDL_RenderCopy(Main_Renderer, Player_shipTexture, NULL, &Shoot);
			SDL_RenderPresent(Main_Renderer);
			SDL_Delay(3);

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