#include<iostream>
#include<vector>
#include<math.h>
#include<string>

#include<SDL.h>
#include<SDL_image.h>

#include "Car.h"


using namespace std;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 512;

SDL_Window *gWindow = NULL;
SDL_Renderer *renderer;


bool running = true;
//bool spawnEnemies = false;
bool _pause = true;
bool gameOver = false;


//int mode = 0;


//int score = 0;


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

void Start() {
    gameOver = false;

    roadRect.x = 256;
    roadRect.y = -64;
    roadRect.w = 128;
    roadRect.h = 576;

    explosionFrame.x = 0;
    explosionFrame.y = 0;
    explosionFrame.w = 64;
    explosionFrame.h = 64;

    explosionRect.x = 0;
    explosionRect.y = 0;
    explosionRect.w = 128;
    explosionRect.h = 128;

    player = new Car(320, 384, renderer, CarColorRed);

    enemies.clear();
}

void Update() {
    if (!gameOver) {
        roadRect.y += 4;
        if (roadRect.y >= 0) {
            roadRect.y = -64;
        }

        player->Update();

        //enemies {...}
    }

    if (gameOver) {
        explosionFrame.x += 64;
        if (explosionFrame.x >= 1472) {
            _pause = true;
            menuState = 8;
        }
    }
}
void Render() {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, road, NULL, &roadRect);

    player->Draw(renderer);

    if (gameOver) {
        SDL_RenderCopy(renderer, explosion, &explosionFrame, &explosionRect);
    }

    if (menuState > 0) {
        SDL_RenderCopy(renderer, menuFrames[menuState-1], NULL, NULL);
    }

    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[]) {

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("SDL_image failed to initialize!\n");
        return EXIT_FAILURE;
    }

    gWindow = SDL_CreateWindow("my_car_game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(gWindow, 0, SDL_RENDERER_ACCELERATED);

    LoadResources();

    Start();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (menuState == 0) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        _pause = true;
                        menuState = 6;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                        player->SwitchLane();
                    }
                }
                else if (menuState > 0) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        if (menuState == 3 || menuState == 4 || menuState == 5) {
                            menuState = 1;
                        }
                        if (menuState == 6 || menuState == 7) {
                            menuState = 0;
                            _pause = false;
                        }
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                        switch (menuState) {
                            case 2:
                                menuState = 1;
                                break;
                            case 4:
                                menuState = 3;
                                break;
                            case 5:
                                menuState = 4;
                                break;
                            case 7:
                                menuState = 6;
                                break;
                            case 9:
                                menuState = 8;
                                break;

                            default:
                                break;
                        }
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        switch (menuState) {
                            case 1:
                                menuState = 2;
                                break;
                            case 3:
                                menuState = 4;
                                break;
                            case 4:
                                menuState = 5;
                                break;
                            case 6:
                                menuState = 7;
                                break;
                            case 8:
                                menuState = 9;
                                break;

                            default:
                                break;
                        }
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        switch (menuState) {
                            case 1:
                                menuState = 4;
                                break;
                            case 2:
                                running = false;
                                break;
                            case 3:
                                menuState = 0;
                                _pause = false;
                                break;
                            case 4:
                                menuState = 0;
                                _pause = false;
                                break;
                            case 5:
                                menuState = 0;
                                _pause = false;
                                break;
                            case 6:
                                menuState = 0;
                                _pause = false;
                                break;
                            case 7:
                                menuState = 1;
                                Start();
                                break;
                            case 8:
                                menuState = 0;
                                Start();
                                _pause = false;
                                break;
                            case 9:
                                menuState = 1;
                                Start();
                                break;

                            default:
                                break;
                        }
                    }
                }
            }
        }

        if (!_pause) {
            Update();
        }

        Render();
    }

    enemies.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
