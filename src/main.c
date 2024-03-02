#include "../inc/header.h"

void quit_libraries(void){
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

void destroy_tools(void){
    SDL_DestroyRenderer(game.gRenderer);
    SDL_DestroyWindow(game.gWindow);
    game.gWindow = NULL;
    game.gRenderer = NULL;
}

void sdl_fail_exit(char *msg){
    printf("%s: %s\n", msg, SDL_GetError());
    exit(EXIT_FAILURE);
}

void success_exit(void){
    destroy_tools();
    quit_libraries();
}

int main(void) {
    setup();
    while (game.Activity != QUIT) {
        game.clock.frame_start = SDL_GetTicks();
        update();
        render();
        game.clock.delay(game.clock, 1000 / 60);
    }
    success_exit();
    return 0;
}
