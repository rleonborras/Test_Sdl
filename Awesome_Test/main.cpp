
#include "SDL\include\SDL.h"
#include <iostream>
#include "SDL_image\include\SDL_image.h"
#include"SDL_Text\include\SDL_ttf.h"

#include "Colors.h"
#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#pragma comment(lib,"SDL_image/libx86/SDL2_image.lib")
#pragma comment(lib,"SDL_Text/libx86/SDL2_ttf.lib")

#define SHAPE_SIZE 100
#define PLSHOOT 30
#define SCORE_SIZEX 150
#define SCORE_SIZEY 50
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int NUMBERS_SHEET= 10;


SDL_Window* window = nullptr;
SDL_Renderer* Main_Renderer=nullptr;
SDL_Texture* Background_Texture=nullptr;
SDL_Texture* Player_shipTexture = nullptr;
SDL_Texture* Enemy_shipTexture = nullptr;
SDL_Texture* Shoot_Texture = nullptr;
SDL_Texture* Score_Texture = nullptr;
SDL_Texture* Numbers_Texture = nullptr;
TTF_Font* Oceanic = TTF_OpenFont("Text/arial.ttf",24);


SDL_Texture* Update_Text(std::string path) {

	SDL_Texture* new_Text = nullptr;
	SDL_Color White = { 255,255,255 };
	SDL_Surface* SurfaceMessage = TTF_RenderText_Solid(Oceanic,path.c_str(), White);
	new_Text = SDL_CreateTextureFromSurface(Main_Renderer, SurfaceMessage);
	SDL_FreeSurface(SurfaceMessage);
	return new_Text;

}

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
	Shoot_Texture = loadTexture("Images/Plasma_Shoot.png");
	Background_Texture = loadTexture("Images/Background.png");
	Player_shipTexture = loadTexture("Images/Player_Ship.png");
	Enemy_shipTexture = loadTexture("Images/Enemy_Ship.png");
	Score_Texture = loadTexture("Text/Score.png");
	Numbers_Texture = loadTexture("Text/Numbers.png");

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

void SpriteSheet(SDL_Rect Sprite[]) {

	for (int i = 1; i < NUMBERS_SHEET; ++i) {
		Sprite[i].x = Sprite[i-1].x+73;
		Sprite[i].y = 0;
		Sprite[i].w = 73;
		Sprite[i].h =102;
	}

}

int main(int argc, char* argv[]) {

	SDL_Rect Ship;
	SDL_Rect Shoot;
	SDL_Rect Enemy;
	SDL_Rect Score;
	SDL_Rect NumClipper[NUMBERS_SHEET];
	SDL_Rect Num_1;
	SDL_Rect Num_2;
	SDL_Rect Num_3;
	SDL_Rect Num_4;

	NumClipper[0].x = 0;
	NumClipper[0].y = 0;
	NumClipper[0].w = 73;
	NumClipper[0].h = 102;

	Num_1.x = 150;
	Num_1.y = 0;
	Num_1.w = 30;
	Num_1.h = 50;

	Num_2.x = 180;
	Num_2.y = 0;
	Num_2.w = 30;
	Num_2.h = 50;

	Num_3.x = 210;
	Num_3.y = 0;
	Num_3.w = 30;
	Num_3.h = 50;

	Num_4.x = 240;
	Num_4.y = 0;
	Num_4.w = 30;
	Num_4.h = 50;

	Score.w = SCORE_SIZEX;
	Score.h = SCORE_SIZEY;
	Score.x = NULL;
	Score.y = NULL;


	Shoot.w = PLSHOOT;
	Shoot.h = PLSHOOT;
	Shoot.x = NULL;
	Shoot.y = NULL;

	Score.w = SCORE_SIZEX;
	Score.h = SCORE_SIZEY;
	Score.x = NULL;
	Score.y = NULL;

	Ship.x = 200;
	Ship.y = 200;
	Ship.w = SHAPE_SIZE;
	Ship.h = SHAPE_SIZE;

	Enemy.x = SCREEN_WIDTH;
	Enemy.y = rand()%(SCREEN_HEIGHT-100)+100;
	Enemy.w = SHAPE_SIZE;
	Enemy.h = SHAPE_SIZE;


	int Velocity = 1;
	int PosSprite=0;
	int SpriteColumn1=0;
	int SpriteColumn2=0;
	int SpriteColumn3=0;
	int SpriteColumn4=0;

	srand(9);
	float timeCharging=0.0;
	bool ChargeShot = false;
	bool EnemyAlive= false;
	bool Charged = false;
	bool ePress = false;
	bool Up = false;
	bool Down = false;
	bool Left = false;
	bool Right = false;
	bool Space = false;
	bool Shoot_Enabled = false;
	bool Shooting = false;
	bool quit = false;
	bool collx = false;
	bool colly = false;
	int colorVar = 0;


	SDL_Event e;



	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect



	//start up SDL and create a window
	init();
	loadMedia();

	SpriteSheet(NumClipper);

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
					Shoot.x = Ship.x + Ship.w-50;
					Shoot.y = Ship.y + (Ship.h / 2)-40;
					Shooting = true;
					Shoot_Enabled=true;
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
					Shoot.x += 8;
					if (Hit(Shoot, Enemy) == true) {
						
						PosSprite++;
						if (PosSprite > 9) {
							PosSprite = 0;
							SpriteColumn1++;
							if (SpriteColumn1 > 9) {
								SpriteColumn1 = 0;
								SpriteColumn2++;
								if (SpriteColumn3 > 9) {
									SpriteColumn3 = 0;

								}
							}
						}
						Enemy.y = rand() % (SCREEN_HEIGHT - 100);
						EnemyAlive = false;
						//Shoot.x=-200;
						//Shoot.y =-200;
					}

				}
				else
					Shooting = false;
			}
			if(EnemyAlive) {
				Enemy.x -= 1;
				if (Enemy.x < 0 - Enemy.w) {
					Enemy.x = SCREEN_WIDTH;
					Enemy.y = rand() % (SCREEN_HEIGHT - 100);
				
				}
			}
			else {
				Enemy.x = SCREEN_WIDTH;
				EnemyAlive = true;
			}
			
			/*
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
			SDL_RenderCopy(Main_Renderer, Shoot_Texture, NULL, &Shoot);
			SDL_RenderCopy(Main_Renderer, Enemy_shipTexture, NULL, &Enemy);
			SDL_RenderCopy(Main_Renderer, Score_Texture, NULL, &Score);
			SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn3], &Num_1);
			SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn2], &Num_2);
			SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn1], &Num_3);
			SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[PosSprite], &Num_4);
			SDL_RenderPresent(Main_Renderer);
			SDL_Delay(2);

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