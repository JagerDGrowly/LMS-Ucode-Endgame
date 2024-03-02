//
// Created by oleksandra on 24/02/24.
//
#include "../inc/header.h"

void init_libs(void){
    // initializing libraries
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        sdl_fail_exit("SDL could not initialize! SDL_Error");
    }

    if (TTF_Init() == -1) {
        SDL_Quit();
        sdl_fail_exit("SDL_ttf could not initialize! SDL_ttf Error");
    }

    if (IMG_Init(IMG_INIT_PNG) == 0){
        SDL_Quit();
        TTF_Quit();
        sdl_fail_exit("SDL_image could not initialize! SDL_img Error");
    }

    // Открытие аудиоустройства
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Failed to open audio: %s\n", Mix_GetError());
        return;
    }

    if (Mix_PlayingMusic() == 0) {

        game.music = Mix_LoadMUS(BACKGROUND_MUSIC);
        if (game.music == NULL) {
            printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
            exit(-1);
        } else {
            Mix_PlayMusic(game.music, -1);
        }
    }
}

void create_tools(void){
    game.gWindow = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (game.gWindow == NULL) {
        quit_libraries();
        sdl_fail_exit("Window could not be created! SDL_Error");
    }

    game.gRenderer = SDL_CreateRenderer(game.gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (game.gRenderer == NULL) {
        SDL_DestroyWindow(game.gWindow);
        quit_libraries();
        sdl_fail_exit("Renderer could not be created! SDL_Error");
    }

    game.clock.delay = (Func) delay;
}

void set_default_parameters(void) {
    settings.musicOn = 1; // По умолчанию музыка включена
    settings.soundOn = 1; // По умолчанию звук включен
    game.Activity = MAIN_MENU;
    game.prev_activity = MAIN_MENU;
    game.essenceCount = 0;
}

SDL_Texture *render_text(char *text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return textTexture;
}

void quit_qte(void){
    SDL_DestroyTexture(game.qte->player_texture);
    SDL_DestroyTexture(game.qte->mob_texture);
    SDL_DestroyTexture(game.qte->indicator_texture);
    TTF_CloseFont(game.qte->font);

    for (int i = 0; i < FIGHT_OPTIONS; i++) {
        SDL_DestroyTexture(game.qte->qte_backgrounds[i]);
    }

    for (int i = 0; i < HINT_OPTIONS; ++i) {
        SDL_DestroyTexture(game.qte->hints[i]);
    }

    for (int i = 0; i < FIGHT_OPTIONS; ++i) {
        SDL_DestroyTexture(game.qte->options[i].active);
        SDL_DestroyTexture(game.qte->options[i].unactive);
    }
    free(game.qte);
    game.qte = NULL;
}

void create_btns(void) {
    char *button_names[BTN_AMOUNTS] = {"play", "settings", "help", "developers", "exit", "music:on", "sound:on", "credits",  "back"};
    for (int btn = 0; btn < BTN_AMOUNTS; ++btn) {
        char path[128];

        sprintf(path, "%s/%s_basic.png", BTN_PATH, button_names[btn]);
        game.menu->buttons[btn].unactive = IMG_LoadTexture(game.gRenderer, path);

        if (game.menu->buttons[btn].unactive == NULL){
            for (int i = 0; i < btn; ++i) {
                free(game.menu->buttons[i].unactive);
                free(game.menu->buttons[i].active);
            }
            quit_menu();
            destroy_tools();
            quit_libraries();
            sdl_fail_exit("faild to load button texture");
        }

        sprintf(path, "%s/%s_focused.png", BTN_PATH, button_names[btn]);

        game.menu->buttons[btn].active = IMG_LoadTexture(game.gRenderer, path);

        if (game.menu->buttons[btn].active == NULL) {
            for (int i = 0; i < btn; ++i) {
                free(game.menu->buttons[i].unactive);
                free(game.menu->buttons[i].active);
            }
            free(game.menu->buttons[btn].unactive);
            quit_menu();
            destroy_tools();
            quit_libraries();
            sdl_fail_exit("faild to load button texture");
        }

        game.menu->buttons[btn].text = button_names[btn];
        game.menu->buttons[btn].is_focused = 0;

        if (btn <= QUIT_BTN){
            game.menu->buttons[btn].rect.x = 100;
            game.menu->buttons[btn].rect.y = 125 + 100 * btn;
            game.menu->buttons[btn].rect.h = 70;
            game.menu->buttons[btn].rect.w = 380;
            game.menu->buttons[btn].text = button_names[btn];
        }
    }
    game.menu->buttons[CREDITS_BTN].rect = (SDL_Rect){952, 630, 170, 50};
    game.menu->buttons[MUSIC_BTN].rect = (SDL_Rect){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, 300, 50};
    game.menu->buttons[SOUND_BTN].rect = (SDL_Rect){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 300, 50};
    game.menu->buttons[BACK_BTN].rect = (SDL_Rect){40, SCREEN_HEIGHT - 90, 100, 50};
}

void init_menu(void){
    game.menu = (Menu *)(malloc(sizeof(Menu)));
    game.menu->background_texture = IMG_LoadTexture(game.gRenderer, BACKGROUND_MENU_PATH);
    if (game.menu->background_texture == NULL){
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create background texture! SDL Error:");
    }
    game.menu->second_background = IMG_LoadTexture(game.gRenderer, BACKGROUND_MENU_SECOND_PATH);
    if (game.menu->background_texture == NULL){
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create background texture! SDL Error:");
    }
    game.menu->font = TTF_OpenFont(FONT_MENU_PATH, 24);
    if (game.menu->font == NULL){
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to load font! SDL_ttf Error");
    }
    create_btns();
}

void quit_menu(void){
    TTF_CloseFont(game.menu->font);
    SDL_DestroyTexture(game.menu->background_texture);
    SDL_DestroyTexture(game.menu->second_background);
    for (int btn = 0; btn < BTN_AMOUNTS; ++btn) {
        SDL_DestroyTexture(game.menu->buttons[btn].active);
        SDL_DestroyTexture(game.menu->buttons[btn].unactive);
    }
    free(game.menu);
    game.menu = NULL;
}

void init_play(void){
    game.play = malloc(sizeof(Play));

    game.play->player_rect = (SDL_Rect){SCREEN_WIDTH / 2 - TILE_GAME_SIZE / 2, SCREEN_HEIGHT / 2 - TILE_GAME_SIZE / 2, TILE_GAME_SIZE, TILE_GAME_SIZE};
    game.play->player_texture = IMG_LoadTexture(game.gRenderer, PLAYER_IMG);
    game.play->movement_vector = (SDL_Point){0, 0};
    game.play->player_direction = UP_DIRECTION;
    game.play->player_current_frame = (SDL_Point){0, UP_DIRECTION};
    game.play->speed = DEFAULT_PLAYER_SPEED;
    for (int i = 0; i < DIRECTION_AMOUNTS; ++i) {
        game.play->movement_modes[i] = MAP_MOVE_MODE;
    }

    game.play->map_cords = (SDL_Point){-SCREEN_WIDTH, -SCREEN_HEIGHT};
    game.play->init_chank = get_init_chunk_cords(); // load_map.c
    game.play->tileset = IMG_LoadTexture(game.gRenderer, TILESET_PATH);
    load_map(&game.play->visible_map);
    load_collision(&game.play->collision_map);

    load_mob();
    for (int i = 0; i < game.play->mobs_amount; ++i) {
        printf("mob rect: %d %d %d %d\n", game.play->mob[i].rect.x, game.play->mob[i].rect.y, game.play->mob[i].rect.w, game.play->mob[i].rect.h);
    }
}

void quit_play(void){
    SDL_DestroyTexture(game.play->player_texture);
    SDL_DestroyTexture(game.play->tileset);
    free(game.play->mob);
    FILE *file = fopen("resources/map/init_chunk.txt", "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу.\n");
        exit(-1);
    }
    fprintf(file, "%d %d\n", game.play->init_chank.x, game.play->init_chank.y);
    fclose(file);

    free(game.play);
    game.play = NULL;
}

void init_inventory(void) {
    game.inventory = (Inventory *)(malloc(sizeof(Inventory)));
    game.inventory->background_texture = IMG_LoadTexture(game.gRenderer, BACKGROUND_INVENTORY_PATH);
    if (game.inventory->background_texture == NULL){
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create background texture! SDL Error:");
    }
    
    game.inventory->gEssenceTexture = IMG_LoadTexture(game.gRenderer, ESSENCE_PATH);
    if (game.inventory->gEssenceTexture == NULL){
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create background texture! SDL Error:");
    }
    
    game.inventory->font = TTF_OpenFont(FONT_MENU_PATH, 24);
    if (game.inventory->font == NULL){
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to load font! SDL_ttf Error");
    }
}

void quit_inventory(void) {
    TTF_CloseFont(game.inventory->font);
    SDL_DestroyTexture(game.inventory->background_texture);
    free(game.inventory);
    game.inventory = NULL;
}

void setup(void){
    init_libs();
    create_tools();
    set_default_parameters();
    init_menu();
    init_inventory();
}
