#include<iostream>
#include<vector>
#include<math.h>
#include<string>

//4 thư viện chính cơ bản
#include<SDL.h>
#include<SDL_image.h>

#include "Car.h"


using namespace std;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 512;
const int FPS = 64;
const int countDownTime = 3;
int total_frames = 0;


SDL_Window *window;
SDL_Renderer *renderer;


bool running = true;
bool spawnEnemies = false;
bool _pause = true;
bool gameOver = false;
int mode = 0;


int score = 0;


std::vector<SDL_Texture*> menuFrames;
int menuState = 1;


SDL_Texture *road;
SDL_Rect roadRect;
Car *player;
std::vector<Car*> enemies;
SDL_Texture *explosion;
SDL_Rect explosionFrame;
SDL_Rect explosionRect;


void LoadResources();
void Start();
void GameLoop();
void Update();
void Render();
//void SpawnEnemy();

void LoadResources() {
    SDL_Surface *surface;

    surface = IMG_Load("Play.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("Quit.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("Easy.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("Medium.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("Hard.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("Resume.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("End.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("Restart.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    surface = IMG_Load("End2.png");
    menuFrames.push_back(SDL_CreateTextureFromSurface(renderer, surface));

    surface = IMG_Load("Road.png");
    road = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("Explosion.png");
    explosion = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

}
int main(int argc, char* argv[]) {

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("SDL_image failed to initialize!\n");
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("car_game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    LoadResources();


    enemies.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
