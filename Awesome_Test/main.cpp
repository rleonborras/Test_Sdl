
#include "SDL\include\SDL.h"
#include <iostream>
#include "SDL_image\include\SDL_image.h"
#include"SDL_Mixer\include\SDL_mixer.h"

#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#pragma comment(lib,"SDL_image/libx86/SDL2_image.lib")
#pragma comment(lib,"SDL_Mixer/libx86/SDL2_mixer.lib")

#define SHAPE_SIZE 100
#define PLSHOOT 30
#define SCORE_SIZEX 150
#define SCORE_SIZEY 50
#define OUTSCREEN 800

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
SDL_Texture* Enemy2_shipTexture = nullptr;
SDL_Texture* Enemy2_ShotTexture = nullptr;

SDL_Texture* loadTexture(const char* filename){

	//Final Texture
	SDL_Texture* newTexture = nullptr;

	//Load image from path
	SDL_Surface* loadedSurface = IMG_Load(filename);
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
	Enemy2_shipTexture = loadTexture("Images/Enemy_2.png");
	Enemy2_ShotTexture = loadTexture("Images/Shot_enemy.png");

	if (Background_Texture == NULL || Player_shipTexture == NULL || Enemy_shipTexture == NULL||Shoot_Texture==NULL||Score_Texture==NULL||Numbers_Texture==NULL) {
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

void Draw(SDL_Rect Enemy,SDL_Rect Enemy2, SDL_Rect Background,SDL_Rect Background2, SDL_Rect Ship, SDL_Rect Shoot,SDL_Rect Enemy2Shoot, SDL_Rect Score, SDL_Rect Num_1, SDL_Rect Num_2, SDL_Rect Num_3, SDL_Rect Num_4, SDL_Rect NumClipper[], int SpriteColumn1, int SpriteColumn2, int SpriteColumn3, int PosSprite) {
	
	SDL_RenderClear(Main_Renderer);

	SDL_RenderCopy(Main_Renderer, Background_Texture, NULL, &Background);
	SDL_RenderCopy(Main_Renderer, Background_Texture, NULL, &Background2);
	SDL_RenderCopy(Main_Renderer, Player_shipTexture, NULL, &Ship);
	SDL_RenderCopy(Main_Renderer, Shoot_Texture, NULL, &Shoot);
	SDL_RenderCopy(Main_Renderer, Enemy_shipTexture, NULL, &Enemy);
	SDL_RenderCopy(Main_Renderer, Enemy2_shipTexture, NULL, &Enemy2);
	SDL_RenderCopy(Main_Renderer, Enemy2_ShotTexture, NULL, &Enemy2Shoot);
	SDL_RenderCopy(Main_Renderer, Score_Texture, NULL, &Score);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn3], &Num_1);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn2], &Num_2);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[SpriteColumn1], &Num_3);
	SDL_RenderCopy(Main_Renderer, Numbers_Texture, &NumClipper[PosSprite], &Num_4);
	SDL_RenderPresent(Main_Renderer);
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

	srand(9);

	//-----------DECLARING SLD VARIABLES-----------//

	SDL_Rect Background;
	SDL_Rect Background2;
	SDL_Rect Ship;
	SDL_Rect Shoot;
	SDL_Rect Enemy;
	SDL_Rect Enemy2;
	SDL_Rect Enemy2Shoot;
	SDL_Rect Score;
	SDL_Rect NumClipper[NUMBERS_SHEET];
	SDL_Rect Num_1;
	SDL_Rect Num_2;
	SDL_Rect Num_3;
	SDL_Rect Num_4;
	SDL_Event e;

	//---------------INITIALIZINF VARIABLES--------//

	Background.x = 0;
	Background.y = 0;
	Background.w = SCREEN_WIDTH;
	Background.h = SCREEN_HEIGHT;

	Background2.x = SCREEN_WIDTH;
	Background2.y = 0;
	Background2.w = SCREEN_WIDTH;
	Background2.h = SCREEN_HEIGHT;

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
	Score.x = 0;
	Score.y = 0;


	Shoot.w = PLSHOOT;
	Shoot.h = PLSHOOT;
	Shoot.x = OUTSCREEN;
	Shoot.y = OUTSCREEN;

	Score.w = SCORE_SIZEX;
	Score.h = SCORE_SIZEY;
	Score.x = 0;
	Score.y = 0;

	Ship.x = 200;
	Ship.y = 200;
	Ship.w = SHAPE_SIZE;
	Ship.h = SHAPE_SIZE;

	Enemy.x = SCREEN_WIDTH;
	Enemy.y = rand()%(SCREEN_HEIGHT-100)+100;
	Enemy.w = SHAPE_SIZE;
	Enemy.h = SHAPE_SIZE;

	Enemy2.x = SCREEN_WIDTH;
	Enemy2.y = 120;
	Enemy2.w = SHAPE_SIZE;
	Enemy2.h = SHAPE_SIZE/2;

	Enemy2Shoot.x = OUTSCREEN;
	Enemy2Shoot.y = OUTSCREEN;
	Enemy2Shoot.w = PLSHOOT;
	Enemy2Shoot.h = PLSHOOT;

	//----- DECLARING LOGIC OPERANDS-------//

	int Velocity = 5;
	int VelocityShoot = 20;
	int PosSprite=0;
	int SpriteColumn1=0;
	int SpriteColumn2=0;
	int SpriteColumn3=0;
	int SpriteColumn4=0;



	float timeCharging=0.0;
	bool ChargeShot = false;
	bool EnemyAlive= false;
	bool Enemy2Alive = false;
	bool Enemy2reachedpoint = false;
	bool Enemy2Shooting = false;
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

			
			if (Shooting) {

				if (Shoot.x < SCREEN_WIDTH) {
					Shoot.x += VelocityShoot;
					if (Hit(Shoot, Enemy) == true&&Enemy.x<SCREEN_WIDTH-40) {
						
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
			if (Enemy2Alive) {
				if (Enemy2.x >= 428) {
					Enemy2.x-=Velocity;
				}
				else {
					Enemy2reachedpoint = true;
				}
				if (Enemy2reachedpoint&&!Enemy2Shooting) {
					Enemy2Shoot.x = Enemy2.x;
					Enemy2Shoot.y = Enemy2.y + 10;
					Enemy2Shooting = true;
				}
				if (Enemy2Shooting) {
					Enemy2Shoot.x -= VelocityShoot;
					if (Enemy2Shoot.x <= 0) {
						Enemy2Shooting = false;
					}
				}
			}
			else {
				Enemy.x = SCREEN_WIDTH;
				Enemy2Alive = true;
			}

			if(EnemyAlive) {
				Enemy.x -= Velocity;
				if (Enemy.x < 0 - Enemy.w) {
					Enemy.x = SCREEN_WIDTH;
					Enemy.y = rand() % (SCREEN_HEIGHT - 100);
				
				}
			}
			else {
				Enemy.x = SCREEN_WIDTH;
				EnemyAlive = true;
			}
			Background.x--;
			if (Background.x <= 0-SCREEN_WIDTH) {
				Background.x = SCREEN_WIDTH;
			}
			Background2.x--;
			if (Background2.x <= 0 - SCREEN_WIDTH) {
				Background2.x = SCREEN_WIDTH;
			}
			
			//Updating the windows surface.

			Draw(Enemy, Enemy2, Background, Background2, Ship, Shoot,Enemy2Shoot, Score, Num_1, Num_2, Num_3, Num_4, NumClipper, SpriteColumn1, SpriteColumn2, SpriteColumn3, PosSprite);

			SDL_Delay(12);

	}	
	close();

	return 0;
}


