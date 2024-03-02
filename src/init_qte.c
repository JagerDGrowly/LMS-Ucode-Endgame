//
// Created by oleksandra on 27/02/24.
//
#include "../inc/header.h"

void init_player(void){
    FILE *file = fopen(PLAYER_HEALTH_PATH, "r");
    if (file == NULL) {
        destroy_tools();
        quit_libraries();
        printf("Failed to open player health file\n");
        exit(EXIT_FAILURE);
    }
    char buffer[5];
    fscanf(file, "%s", buffer);
    int player_health = atoi(buffer);
    fclose(file);
    
    game.qte->player_max_health = 100;
    game.qte->player_health = player_health;
    game.qte->player_attack = 15;
    game.qte->player_defense = 10;
    game.qte->player_heal = 10;
    game.qte->player_texture = IMG_LoadTexture(game.gRenderer, QTE_PLAYER_TEXTURE_PATH);
    if (game.qte->player_texture == NULL){
        free(game.qte);
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create player texture! SDL Error:");
    }
}

void init_mob(void){
    if (game.qte->type_mob == 0) {
        game.qte->mob_texture = IMG_LoadTexture(game.gRenderer, mob0_IMG);
        game.qte->mob_max_health = 40;
        game.qte->mob_health = game.qte->mob_max_health;
        game.qte->mob_attack = 10;
        game.qte->mob_defense = 15;
        game.qte->mob_heal = 5;
    } else if (game.qte->type_mob  == 1) {
        game.qte->mob_texture = IMG_LoadTexture(game.gRenderer, mob1_IMG);
        game.qte->mob_max_health = 50;
        game.qte->mob_health = game.qte->mob_max_health;
        game.qte->mob_attack = 12;
        game.qte->mob_defense = 5;
        game.qte->mob_heal = 7;
    } else if (game.qte->type_mob  == 2) {
        game.qte->mob_texture = IMG_LoadTexture(game.gRenderer, mob2_IMG);
        game.qte->mob_max_health = 25;
        game.qte->mob_health = game.qte->mob_max_health;
        game.qte->mob_attack = 5;
        game.qte->mob_defense = 15;
        game.qte->mob_heal = 10;
    } else if (game.qte->type_mob  == 3) {
        game.qte->mob_texture = IMG_LoadTexture(game.gRenderer, mob3_IMG);
        game.qte->mob_max_health = 60;
        game.qte->mob_health = game.qte->mob_max_health;
        game.qte->mob_attack = 10;
        game.qte->mob_defense = 5;
        game.qte->mob_heal = 5;
    }
    if (game.qte->mob_texture == NULL){
        SDL_DestroyTexture(game.qte->player_texture);
        free(game.qte);
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create mob texture! SDL Error:");
    }
}

void init_indicator(void){
    game.qte->indicator_rect = (SDL_Rect){300, SCREEN_HEIGHT - 172, 6, 12};
    game.qte->indicator_texture = IMG_LoadTexture(game.gRenderer, INDICATOR_PATH);
    if (game.qte->indicator_texture == NULL){
        SDL_DestroyTexture(game.qte->player_texture);
        SDL_DestroyTexture(game.qte->mob_texture);
        free(game.qte);
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create mob texture! SDL Error:");
    }
}

void init_keys(void){
    game.qte->key_up_on = false;
    game.qte->key_down_on = false;
    game.qte->key_up_off = true;
    game.qte->key_down_off = true;
}

void init_font(void){
    game.qte->font = TTF_OpenFont(FONT_PATH, 50);
    if (game.qte->font == NULL){
        SDL_DestroyTexture(game.qte->player_texture);
        SDL_DestroyTexture(game.qte->mob_texture);
        SDL_DestroyTexture(game.qte->indicator_texture);
        free(game.qte);
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create font! SDL Error:");
    }
}

void init_backgrounds(void){
    game.qte->basic_background = IMG_LoadTexture(game.gRenderer, BACKGROUND_QTE_PATH);
    if (game.qte->basic_background == NULL){
        SDL_DestroyTexture(game.qte->player_texture);
        SDL_DestroyTexture(game.qte->mob_texture);
        SDL_DestroyTexture(game.qte->indicator_texture);
        TTF_CloseFont(game.qte->font);
        free(game.qte);
        destroy_tools();
        quit_libraries();
        sdl_fail_exit("Failed to create background texture! SDL Error:");
    }
    char *option_paths[FIGHT_OPTIONS] = {"resources/img/background_attack.png",
                                         "resources/img/background_defend.png",
                                         "resources/img/background_heal.png"};
    for (int i = 0; i < FIGHT_OPTIONS; i++) {
        game.qte->qte_backgrounds[i] = IMG_LoadTexture(game.gRenderer, option_paths[i]);
        if (game.qte->qte_backgrounds[i] == NULL){
            SDL_DestroyTexture(game.qte->player_texture);
            SDL_DestroyTexture(game.qte->mob_texture);
            SDL_DestroyTexture(game.qte->indicator_texture);
            SDL_DestroyTexture(game.qte->basic_background);
            TTF_CloseFont(game.qte->font);
            for (int j = 0; j < i; ++j) {
                SDL_DestroyTexture(game.qte->qte_backgrounds[j]);
            }
            free(game.qte);
            destroy_tools();
            quit_libraries();
            sdl_fail_exit("Failed to create option texture! SDL Error:");
        }
    }
}

void init_hints(void){
    char *hints_path[HINT_OPTIONS] = {"Info: Heal yourself. Press [ENTER] to start QTE",
                                      "Info: Defend yourself from the opponent's attack. Press [ENTER] to start QTE",
                                      "Info: Damage your opponent. Press [ENTER] to start QTE",
                                      "Hint: Press [SPACE]",
                                      "Mob's turn"
    };
    SDL_Color black = {0, 255, 0, 0};
    for (int i = 0; i < HINT_OPTIONS; ++i) {
        SDL_Texture *texture = render_text(hints_path[i], game.qte->font, black, game.gRenderer);
        if (texture == NULL){
            SDL_DestroyTexture(game.qte->player_texture);
            SDL_DestroyTexture(game.qte->mob_texture);
            SDL_DestroyTexture(game.qte->indicator_texture);
            SDL_DestroyTexture(game.qte->basic_background);
            TTF_CloseFont(game.qte->font);
            for (int j = 0; j < FIGHT_OPTIONS; j++){
                SDL_DestroyTexture(game.qte->qte_backgrounds[j]);
            }
            free(game.qte);
            destroy_tools();
            quit_libraries();
            sdl_fail_exit("Failed to create hint! SDL Error:");
        }
        game.qte->hints[i] = texture;
        game.qte->hint_rects[i] = (SDL_Rect){0, SCREEN_HEIGHT - 50, 0, 25};
        game.qte->hint_rects[i].w = strlen(hints_path[i]) * 10;
        game.qte->hint_rects[i].x = SCREEN_WIDTH / 2 - strlen(hints_path[i]) * 5;
    }
}

void init_options(void){
    char* names[FIGHT_OPTIONS] = {"attack", "defend", "heal"};
    for (int i = 0; i < FIGHT_OPTIONS; ++i) {
        game.qte->options[i].rect = (SDL_Rect){30, SCREEN_HEIGHT - 212 + 48 * i, OPTION_BTN_WIDTH, OPTION_BTN_HEIGHT};
        game.qte->options[i].text = names[i];

        char act[60];
        sprintf(act, "resources/img/active_%d.png", i);
        char unact[60];
        sprintf(unact, "resources/img/unactive_%d.png", i);

        // textures
        game.qte->options[i].active = IMG_LoadTexture(game.gRenderer, act);
        game.qte->options[i].unactive = IMG_LoadTexture(game.gRenderer, unact);

        if (game.qte->options[i].active == NULL || game.qte->options[i].unactive == NULL){
            SDL_DestroyTexture(game.qte->player_texture);
            SDL_DestroyTexture(game.qte->mob_texture);
            SDL_DestroyTexture(game.qte->indicator_texture);
            SDL_DestroyTexture(game.qte->basic_background);
            TTF_CloseFont(game.qte->font);
            for (int j = 0; j < FIGHT_OPTIONS; j++){
                SDL_DestroyTexture(game.qte->qte_backgrounds[j]);
            }
            for (int j = 0; j < i; ++j) {
                SDL_DestroyTexture(game.qte->options[j].active);
                SDL_DestroyTexture(game.qte->options[j].unactive);
            }
            free(game.qte);
            destroy_tools();
            quit_libraries();
            sdl_fail_exit("Failed to create options! SDL Error:");
        }
    }
}

void init_qte(int typemob, int index){
    game.qte = malloc(sizeof(Qte));

    init_player();
    //init_mob(mob);
    init_indicator();
    init_keys();
    init_font();
    init_backgrounds();
    init_hints();
    init_options();

    game.qte->mode = QTE_MENU;
    game.qte->speed = (rand() % 11) + 5;
    game.qte->frame_counter = 0;
    game.qte->active_option = 0;
    game.qte->result = 0;
    game.qte->print_result = false;
    game.qte->success = false;
    game.qte->index_mob = index;
    game.qte->type_mob = typemob;
    init_mob();
}
