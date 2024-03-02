//
// Created by oleksandra on 27/02/24.
//
#include "../inc/header.h"

void draw_background(void){
    if (game.Activity == QTE){
        SDL_RenderCopy(game.gRenderer, game.qte->basic_background, NULL, NULL);
    } else if (game.Activity == FIGHT){
        SDL_RenderCopy(game.gRenderer, game.qte->qte_backgrounds[game.qte->active_option], NULL, NULL);
    }
}

void print_info(void) {
    if (game.Activity == QTE) {
        SDL_RenderCopy(game.gRenderer, game.qte->hints[game.qte->active_option], NULL, &game.qte->hint_rects[game.qte->active_option]);
    }
    if (game.Activity == FIGHT) {
        SDL_RenderCopy(game.gRenderer, game.qte->hints[3], NULL, &game.qte->hint_rects[3]);
    }
}

void draw_options(void)
{
    for (int i = 0; i < FIGHT_OPTIONS; ++i) {
        if (i == game.qte->active_option){
            SDL_RenderCopy(game.gRenderer, game.qte->options[i].active, NULL, &game.qte->options[i].rect);
            continue;
        }
        SDL_RenderCopy(game.gRenderer, game.qte->options[i].unactive, NULL, &game.qte->options[i].rect);
    }
}

void draw_in_progress(void){
    SDL_RenderCopy(game.gRenderer, game.qte->indicator_texture, NULL, &game.qte->indicator_rect);
}

void draw_health(void) {
    if (game.qte->player_health <= 0) {
        game.qte->player_health = 0;
    }
    int player_health_bar_width = (int)((float)game.qte->player_health / game.qte->player_max_health * HEALTHBAR_WIDTH);

    if (game.qte->mob_health <= 0) {
        game.qte->mob_health = 0;
    }
    int mob_health_bar_width = (int)((float)game.qte->mob_health / game.qte->mob_max_health * HEALTHBAR_WIDTH);

    int remaining_health_width = HEALTHBAR_WIDTH - mob_health_bar_width;
    int new_x = SCREEN_WIDTH - 10 - HEALTHBAR_WIDTH + remaining_health_width;

    SDL_Rect player_outline_rect = {10 - HEALTHBAR_PADDING,
                                    50 - HEALTHBAR_PADDING,
                                    HEALTHBAR_WIDTH + HEALTHBAR_PADDING * 2,
                                    HEALTHBAR_HEIGHT + HEALTHBAR_PADDING * 2};

    SDL_Rect mob_outline_rect = {SCREEN_WIDTH - 10 - HEALTHBAR_WIDTH - HEALTHBAR_PADDING,
                                 50 - HEALTHBAR_PADDING,
                                 HEALTHBAR_WIDTH + HEALTHBAR_PADDING * 2,
                                 HEALTHBAR_HEIGHT + HEALTHBAR_PADDING * 2};

    SDL_SetRenderDrawColor(game.gRenderer, 255, 255, 255, 255);

    SDL_RenderDrawRect(game.gRenderer, &player_outline_rect);
    SDL_RenderDrawRect(game.gRenderer, &mob_outline_rect);

    SDL_SetRenderDrawColor(game.gRenderer, 255, 0, 0, 255);
    SDL_Rect player_health_rect = {10, 50, player_health_bar_width, HEALTHBAR_HEIGHT};
    SDL_RenderFillRect(game.gRenderer, &player_health_rect);


    SDL_Rect mob_health_rect = {new_x, 50, mob_health_bar_width, HEALTHBAR_HEIGHT};
    SDL_RenderFillRect(game.gRenderer, &mob_health_rect);
}

void draw_entities(void) {
    SDL_Rect mob_rect = {SCREEN_WIDTH - 318, 235, 167, 180};
    SDL_Rect player_rect = {151, 240, 95, 170};

    SDL_RenderCopy(game.gRenderer, game.qte->player_texture, NULL, &player_rect);
    SDL_RenderCopy(game.gRenderer, game.qte->mob_texture, NULL, &mob_rect);
}

void print_qte(void) {
    SDL_Color c = {0, 255, 0, 0};
    SDL_Rect textRect = {300, SCREEN_HEIGHT - 140, strlen(game.qte->result_text) * 20, 50};
    SDL_Texture *textTexture = render_text(game.qte->result_text, game.qte->font, c, game.gRenderer);
    SDL_RenderCopy(game.gRenderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(game.gRenderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(textTexture);
}

void print_mob_info(void) {
    SDL_Color c = {0, 255, 0, 0};
    SDL_Rect info_health_rect = {SCREEN_WIDTH - 300, SCREEN_HEIGHT - 200, 0, 25};
    SDL_Rect info_attack_rect = {SCREEN_WIDTH - 300, SCREEN_HEIGHT - 170, 0, 25};
    SDL_Rect info_defense_rect = {SCREEN_WIDTH - 300, SCREEN_HEIGHT - 140, 0, 25};
    SDL_Rect info_heal_rect = {SCREEN_WIDTH - 300, SCREEN_HEIGHT - 110, 0, 25};

    char info_health[50];
    char info_attack[50];
    char info_defense[50];
    char info_heal[50];

    sprintf(info_health, "Mob's health: %.2f", game.qte->mob_health);
    sprintf(info_attack, "Mob's attack power: %d", game.qte->mob_attack);
    sprintf(info_defense, "Mob's defense: %.2f", game.qte->mob_defense);
    sprintf(info_heal, "Mob's heal: %d", game.qte->mob_heal);

    SDL_Texture *info_health_texture = render_text(info_health, game.qte->font, c, game.gRenderer);
    SDL_Texture *info_attack_texture = render_text(info_attack, game.qte->font, c, game.gRenderer);
    SDL_Texture *info_defense_texture = render_text(info_defense, game.qte->font, c, game.gRenderer);
    SDL_Texture *info_heal_texture = render_text(info_heal, game.qte->font, c, game.gRenderer);

    info_health_rect.w = strlen(info_health) * 10;
    info_attack_rect.w = strlen(info_attack) * 10;
    info_defense_rect.w = strlen(info_defense) * 10;
    info_heal_rect.w = strlen(info_heal) * 10;

    SDL_RenderCopy(game.gRenderer, info_health_texture, NULL, &info_health_rect);
    SDL_RenderCopy(game.gRenderer, info_attack_texture, NULL, &info_attack_rect);
    SDL_RenderCopy(game.gRenderer, info_defense_texture, NULL, &info_defense_rect);
    SDL_RenderCopy(game.gRenderer, info_heal_texture, NULL, &info_heal_rect);
}

void draw_result(bool success) {
    SDL_SetRenderDrawColor(game.gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(game.gRenderer);
    SDL_Color c;
    SDL_Rect success_rect = {0, SCREEN_HEIGHT / 2 - 50, 0, 100};
    char *text_success;

    if (success) {
        text_success = "You won!";
        c.r = 0;
        c.g = 255;
        c.b = 0;
        c.a = 255;
    } else {
        text_success = "You lost!";
        c.r = 255;
        c.g = 0;
        c.b = 0;
        c.a = 255;
    }

    SDL_Texture *info_health_texture = render_text(text_success, game.qte->font, c, game.gRenderer);

    success_rect.w = strlen(text_success) * 35;
    success_rect.x = (SCREEN_WIDTH / 2) - (success_rect.w / 2);

    SDL_RenderCopy(game.gRenderer, info_health_texture, NULL, &success_rect);
    SDL_RenderPresent(game.gRenderer);
    SDL_Delay(2000);
}

void fight(void) {

    srand(time(NULL));
    int mob_option = rand() % 3;
    double player_attack = 0;
    double player_defense = 0;
    double player_heal = 0;
    double mob_attack = 0;
    double mob_defense = 0;
    double mob_heal = 0;

    if (game.qte->active_option == ATTACK) {
        player_attack = game.qte->player_attack * game.qte->result_multiplier;
    } else if (game.qte->active_option == DEFENSE) {
        player_defense = game.qte->player_defense * game.qte->result_multiplier;
    } else if (game.qte->active_option == HEAL) {
        player_heal = game.qte->player_heal * game.qte->result_multiplier;
    }

    if (mob_option == ATTACK) {
        mob_attack = game.qte->mob_attack * ((rand() % 6) / 10.0 + 1);
    } else if (mob_option == DEFENSE) {
        mob_defense = game.qte->mob_defense * ((rand() % 6) / 10.0 + 1);
    } else if (mob_option == HEAL) {
        mob_heal = game.qte->mob_heal * ((rand() % 6) / 10.0 + 1);
    }

    if (player_attack - mob_defense >= 0) {
        game.qte->mob_health -= player_attack - mob_defense;
    }

    game.qte->player_health += player_heal;
    if (game.qte->player_health > game.qte->player_max_health) {
        game.qte->player_health = game.qte->player_max_health;
    }

    if (game.qte->mob_health <= 0) {
    	FILE *file = fopen(PLAYER_HEALTH_PATH, "w");
        if (file == NULL) {
            printf("Помилка відкриття файлу.\n");
            exit(-1);
        }
        fprintf(file, "%d\n", (int)game.qte->player_health);
        fclose(file);
        draw_result(true);
        game.essenceCount += 0.5f;
        game.Activity = PLAY;
        game.play->mob[game.qte->index_mob].is_alive = false;
        game.play->movement_vector.x = 0;
        game.play->movement_vector.y = 0;
        quit_qte();
    }
    else {

        SDL_Delay(1000);

        SDL_RenderCopy(game.gRenderer, game.qte->qte_backgrounds[mob_option], NULL, NULL);
        draw_health();
        draw_entities();
        SDL_RenderCopy(game.gRenderer, game.qte->hints[4], NULL, &game.qte->hint_rects[4]);
        SDL_RenderPresent(game.gRenderer);

        SDL_Delay(1000);

        if (mob_attack - player_defense >= 0) {
            game.qte->player_health -= mob_attack - player_defense;
        }

        game.qte->mob_health += mob_heal;
        if (game.qte->mob_health > game.qte->mob_max_health) {
            game.qte->mob_health = game.qte->mob_max_health;
        }

        if (game.qte->player_health <= 0) {
            draw_result(false);
            FILE *file = fopen(PLAYER_HEALTH_PATH, "w");
            if (file == NULL) {
                printf("Помилка відкриття файлу.\n");
                exit(-1);
            }
            fprintf(file, "%d\n", 100);
            fclose(file);
            game.Activity = MAIN_MENU;
            quit_qte();
            init_menu();
        }
    }
}

void draw_fight(void){

    draw_background();
    draw_entities();
    draw_health();
    print_mob_info();

    if (!game.qte->success && game.qte->indicator_rect.x < QTE_END){
        draw_in_progress();
    } else if (game.qte->success){
        draw_health();
        draw_entities();
        print_qte();
        fight();
    }
}

void draw_qte(void){
    draw_background();
    draw_options();
    draw_entities();
    print_info();
    draw_health();
    print_mob_info();
}
