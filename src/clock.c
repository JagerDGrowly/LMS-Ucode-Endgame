//
// Created by oleksandra on 24/02/24.
//
#include "../inc/header.h"

void delay(Clock clock, unsigned int delay) {
    fflush(stdout);
    // затримка, якщо час кадра менше ніж затримка кадра
    clock.frame_time = SDL_GetTicks() - clock.frame_start;
    if (SDL_GetTicks() - clock.frame_start < delay) {
        SDL_Delay(delay - clock.frame_time);
    }
}
