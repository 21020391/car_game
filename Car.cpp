#include "Car.h"

Car::Car(int x, int y, SDL_Renderer *renderer, CarColor color) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = CAR_WIDTH;
    this->rect.h = CAR_HEIGHT;
    this->defaultLanePos = x;

    const char *path = nullptr;

    if (color == CarColorRed)
        path = "red.png";
    if (color == CarColorYellow)
        path = "yellow.png";

    SDL_Surface *surface = IMG_Load(path);
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Car::Draw(SDL_Renderer *renderer) {
    SDL_RenderCopyEx(renderer, this->texture, NULL, &this->rect, rotation, NULL, SDL_FLIP_NONE);
}

void Car::SetDirection(int dir) {
    if (dir > 0) {
        direction = 1;
        rotation = 0;
    }
    if (dir < 0) {
        direction = -1;
        rotation = 180;
    }
}

void Car::SetSpeed(float speed) {
    this->speed = speed;
}

void Car::SwitchLane() {
    if (lane == 0) {
        lane = 1;
    } else {
        lane = 0;
    }
    switchingLane = true;
}

void Car::Update() {
    this->rect.y -= speed * direction;

    if (switchingLane) {
        if (lane == 1 && this->rect.x < defaultLanePos) {
            this->rect.x += 2;
            rotation = 10;
        }
        else if (lane == 0 && this->rect.x > defaultLanePos - CAR_WIDTH) {
            this->rect.x -= 2;
            rotation = -10;
        }
        else {
            rotation = 0;
            switchingLane = false;
        }
    }
}

Car::~Car() {
    SDL_DestroyTexture(this->texture);
}
