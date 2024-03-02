//
// Created by oleksandra on 23/02/24.
//
#include "../inc/header.h"

bool is_point_collide_rect(int point_x, int point_y, SDL_Rect rect){
    if (point_x >= rect.x && point_x <= rect.x + rect.w && point_y >= rect.y && point_y <= rect.y + rect.h) {
        return true;
    }
    return false;
}

void check_main_menu_btns(int x, int y){
    if (is_point_collide_rect(x, y, game.menu->buttons[PLAY_BTN].rect)) {
        printf("Play button clicked!\n");
        quit_menu();
        init_play();
        game.Activity = PLAY;
        game.prev_activity = MAIN_MENU;
    } else if (is_point_collide_rect(x, y, game.menu->buttons[SETTINGS_BTN].rect)) {
        printf("Settings button clicked!\n");
        game.Activity = SETTINGS;
        game.prev_activity = MAIN_MENU;
    } else if (is_point_collide_rect(x, y, game.menu->buttons[QUIT_BTN].rect)) {
        game.Activity = QUIT;
        game.prev_activity = MAIN_MENU;
    } else if (is_point_collide_rect(x, y, game.menu->buttons[DEVELOPERS_BTN].rect)){
        printf("Developers button clicked!\n");
        game.Activity = DEVELOPERS;
        game.prev_activity = MAIN_MENU;
    } else if (is_point_collide_rect(x, y, game.menu->buttons[HELP_BTN].rect)) {
        printf("Help button clicked!\n");
        game.Activity = HELP;
        game.prev_activity = MAIN_MENU;
    } else if (is_point_collide_rect(x, y, game.menu->buttons[CREDITS_BTN].rect)) {
        printf("Credits button clicked!\n");
        game.Activity = CREDITS;
        game.prev_activity = MAIN_MENU;
    }
}

void check_settings_btns(int x, int y){
    if (is_point_collide_rect(x, y, game.menu->buttons[MUSIC_BTN].rect)){
        printf("Music button clicked!\n");
        settings.musicOn = !settings.musicOn; // Переключаем состояние музыки
        game.menu->buttons[MUSIC_BTN].text = (settings.musicOn)? "music:on": "music:off";
        SDL_DestroyTexture(game.menu->buttons[MUSIC_BTN].unactive);
        SDL_DestroyTexture(game.menu->buttons[MUSIC_BTN].active);
        char path[128];
        if (settings.musicOn){
            sprintf(path, "%s/music:on_basic.png", BTN_PATH);
            game.menu->buttons[MUSIC_BTN].unactive = IMG_LoadTexture(game.gRenderer, path);
            sprintf(path, "%s/music:on_focused.png", BTN_PATH);
            game.menu->buttons[MUSIC_BTN].active = IMG_LoadTexture(game.gRenderer, path);
            // Включаем музыку
            playMusic();
        } else {
            sprintf(path, "%s/music:off_basic.png", BTN_PATH);
            game.menu->buttons[MUSIC_BTN].unactive = IMG_LoadTexture(game.gRenderer, path);
            sprintf(path, "%s/music:off_focused.png", BTN_PATH);
            game.menu->buttons[MUSIC_BTN].active = IMG_LoadTexture(game.gRenderer, path);
            // Выключаем музыку
            stopMusic();
        }
        if (game.menu->buttons[MUSIC_BTN].active == NULL || game.menu->buttons[MUSIC_BTN].unactive == NULL){
            quit_menu();
            destroy_tools();
            quit_libraries();
            sdl_fail_exit("failed to load btn image");
        }
    } else if (is_point_collide_rect(x, y, game.menu->buttons[SOUND_BTN].rect)){
        printf("Sound button clicked!\n");
        settings.soundOn = !settings.soundOn; // Переключаем состояние звука
        game.menu->buttons[SOUND_BTN].text = (settings.soundOn)? "sound:on": "sound:off";
        SDL_DestroyTexture(game.menu->buttons[SOUND_BTN].unactive);
        SDL_DestroyTexture(game.menu->buttons[SOUND_BTN].active);
        char path[128];
        if (settings.soundOn){
            sprintf(path, "%s/sound:on_basic.png", BTN_PATH);
            game.menu->buttons[SOUND_BTN].unactive = IMG_LoadTexture(game.gRenderer, path);
            sprintf(path, "%s/sound:on_focused.png", BTN_PATH);
            game.menu->buttons[SOUND_BTN].active = IMG_LoadTexture(game.gRenderer, path);
        } else {
            sprintf(path, "%s/sound:off_basic.png", BTN_PATH);
            game.menu->buttons[SOUND_BTN].unactive = IMG_LoadTexture(game.gRenderer, path);
            sprintf(path, "%s/sound:off_focused.png", BTN_PATH);
            game.menu->buttons[SOUND_BTN].active = IMG_LoadTexture(game.gRenderer, path);
        }
        if (game.menu->buttons[MUSIC_BTN].active == NULL || game.menu->buttons[MUSIC_BTN].unactive == NULL){
            quit_menu();
            destroy_tools();
            quit_libraries();
            sdl_fail_exit("failed to load btn image");
        }
    } else if (is_point_collide_rect(x, y, game.menu->buttons[BACK_BTN].rect)){
        game.prev_activity = SETTINGS;
        game.Activity = MAIN_MENU; // Возвращаемся в главное меню
    }
}


void check_developers_btns(int x, int y){
    if (is_point_collide_rect(x, y, game.menu->buttons[BACK_BTN].rect)) {
        game.prev_activity = DEVELOPERS;
        game.Activity = MAIN_MENU; // Возвращаемся в главное меню
    }
}

void check_help_btns(int x, int y){
    if (is_point_collide_rect(x, y, game.menu->buttons[BACK_BTN].rect)) {
        game.prev_activity = HELP;
        game.Activity = MAIN_MENU; // Возвращаемся в главное меню
    }
}

void check_credits_btns(int x, int y){
    if (is_point_collide_rect(x, y, game.menu->buttons[BACK_BTN].rect)) {
        game.prev_activity = CREDITS;
        game.Activity = MAIN_MENU; // Возвращаемся в главное меню
    }
}

void check_btn_focused(void){
    int x, y;
    SDL_GetMouseState(&x, &y);
    for (int btn = 0; btn < BTN_AMOUNTS; ++btn) {
        if (is_point_collide_rect(x, y, game.menu->buttons[btn].rect)){
            game.menu->buttons[btn].is_focused = 1;
        } else {
            game.menu->buttons[btn].is_focused = 0;
        }
    }
}

void mouse_events_handler(void) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    switch (game.Activity) {
        case MAIN_MENU:
            check_main_menu_btns(x, y);
            break;
        case SETTINGS:
            check_settings_btns(x, y);
            break;
        case DEVELOPERS:
            check_developers_btns(x, y);
            break;
        case HELP:
            check_help_btns(x, y);
            break;
        case CREDITS: // Добавляем проверку для раздела "Credits"
            check_credits_btns(x, y);
            break;
    }
}

void key_down_handler(SDL_Event event){
    switch (game.Activity) {
        case MAIN_MENU:
            if (event.key.keysym.sym == SDLK_SPACE){
                game.prev_activity = MAIN_MENU;
                game.Activity = PLAY;
            }
            else if (event.key.keysym.sym == SDLK_ESCAPE) {
                game.Activity = QUIT;
                game.prev_activity = MAIN_MENU;
            }
            break;
        case PLAY:
            if (event.key.keysym.sym == SDLK_UP){
                game.play->player_direction = UP_DIRECTION;
                game.play->movement_vector.y = UP_OFFST; // переміщення карти вниз
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                game.play->player_direction = DOWN_DIRECTION;
                game.play->movement_vector.y = DOWN_OFFST; // переміщення карти вгору
            } else {
                game.play->movement_vector.y = NONE_OFFST;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                game.play->player_direction = LEFT_DIRECTION;
                game.play->movement_vector.x = LEFT_OFFST; // переміщення вправо
            } else if (event.key.keysym.sym == SDLK_RIGHT) {
                game.play->player_direction = RIGHT_DIRECTION;
                game.play->movement_vector.x = RIGHT_OFFST; // переміщення вліво
            } else {
                game.play->movement_vector.x = NONE_OFFST;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quit_play();
                init_menu();
                game.Activity = MAIN_MENU;
                game.prev_activity = PLAY;
            } else if (event.key.keysym.sym == SDLK_e){
                game.prev_activity = PLAY;
                game.Activity = INVENTORY;
            }
            break;
        case SETTINGS:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game.prev_activity = SETTINGS;
                game.Activity = MAIN_MENU;
            }
            break;
        case DEVELOPERS:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game.Activity = MAIN_MENU;
                game.prev_activity = DEVELOPERS;
            }
            break;
        case HELP:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game.Activity = MAIN_MENU;
                game.prev_activity = HELP;
            }
            break;
        case CREDITS:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game.Activity = MAIN_MENU;
                game.prev_activity = CREDITS;
            }
            break;
        case QTE:
            if (event.key.keysym.sym == SDLK_UP && game.qte->key_up_off){
                game.qte->key_up_on = true;
                game.qte->key_up_off = false;
            } else if (event.key.keysym.sym == SDLK_DOWN && game.qte->key_down_off){
                game.qte->key_down_on = true;
                game.qte->key_down_off = false;
            } else if (event.key.keysym.sym == SDLK_RETURN){
                game.qte->mode = QTE_MY_TURN;
                game.prev_activity = QTE;
                game.Activity = FIGHT;
            }
            break;
        case FIGHT:
            if (event.key.keysym.sym == SDLK_SPACE){
                game.qte->mode = QTE_MOB_TURN;
                game.qte->success = true;
                game.qte->result = game.qte->indicator_rect.x + game.qte->indicator_rect.w / 2;
            }
            break;
        case INVENTORY:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game.prev_activity = INVENTORY;
                game.Activity = PLAY;
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                if (game.essenceCount == 5) {
                    game.Activity = QUIT;
                    quit_inventory();
                }
            }
            break;
    }
}

void key_up_handler(SDL_Event event){
    switch (game.Activity) {
        case PLAY:
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
                game.play->movement_vector.y = NONE_OFFST;
            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
                game.play->movement_vector.x = NONE_OFFST;
            break;
        case QTE:
            if (event.key.keysym.sym == SDLK_UP)
            {
                game.qte->key_up_off = true;
            } else if (event.key.keysym.sym == SDLK_DOWN)
            {
                game.qte->key_down_off = true;
            }
    }
}

void eventloop(void){
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            game.prev_activity = game.Activity;
            game.Activity = QUIT;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouse_events_handler();
        }
        else if (event.type == SDL_KEYDOWN) {
            key_down_handler(event);
        }
        else if (event.type == SDL_KEYUP){
            key_up_handler(event);
        }
    }
}

void update_mobs_animation(void){
    for (int i = 0; i < game.play->mobs_amount; ++i) {
        if (game.play->mob[i].frame_counter == game.play->mob[i].frame_delay){
            game.play->mob[i].current_frame++;
            game.play->mob[i].frame_counter = 0;
            if (game.play->mob[i].current_frame == MOB_ANIMATION_FRAMES){
                game.play->mob[i].current_frame = 0;
            }
        } else {
            game.play->mob[i].frame_counter++;
        }

    }
}

int distance(SDL_Point cords1, SDL_Point cords2){
    return sqrt((cords2.x - cords1.x) * (cords2.x - cords1.x) + (cords2.y - cords1.y) * (cords2.y - cords1.y));
}

void check_mob_active(void){
    SDL_Point player = {game.play->player_rect.x + (-game.play->map_cords.x) + game.play->player_rect.w / 2, game.play->player_rect.y + (-game.play->map_cords.y)  + game.play->player_rect.h / 2};
    for (int i = 0; i < game.play->mobs_amount; ++i) {
        SDL_Point mob = {game.play->mob[i].rect.x + game.play->mob[i].rect.w / 2, game.play->mob[i].rect.y + game.play->mob[i].rect.h / 2};
        if (game.play->mob[i].is_active == false && distance(player, mob) < ACTIVE_RADIUS_MOB){
            game.play->mob[i].is_active = true;
        } else if (game.play->mob[i].is_active == true && distance(player, mob) < ACTIVE_RADIUS_MOB * 2){
            game.play->mob[i].is_active = false;
        }
    }
}

SDL_Point get_movement_vector(SDL_Point object, SDL_Point goal){
    SDL_Point move_vector = {0, 0};
    if (goal.x < object.x) {
        move_vector.x = -1;  // left
    } else if (goal.x > object.x) {
        move_vector.x = 1;  // right
    }
    if (goal.y < object.y) {
        move_vector.y = -1; // Моб движется вверх
    } else if (goal.y > object.y) {
        move_vector.y = 1; // Моб движется вниз
    }
    return move_vector;
}

bool is_rect_collide_rect(SDL_Rect rect1, SDL_Rect rect2){
    bool x_overlap = rect1.x + rect1.w >= rect2.x && rect2.x + rect2.w >= rect1.x;
    bool y_overlap = rect1.y + rect1.h >= rect2.y && rect2.y + rect2.h >= rect1.y;

    // Якщо обидва умови перетину виконуються, то прямокутники перетинаються
    return x_overlap && y_overlap;
}

void update_mob_pos(void){
    SDL_Point move_vector = {0, 0};
    SDL_Point player = {game.play->player_rect.x + (-game.play->map_cords.x) + game.play->player_rect.w / 2, game.play->player_rect.y + (-game.play->map_cords.y)  + game.play->player_rect.h / 2};

    for (int i = 0; i < game.play->mobs_amount; ++i) {
        if (game.play->mob[i].is_active && game.play->mob[i].is_alive) {
            SDL_Point mob = {game.play->mob[i].rect.x + game.play->mob[i].rect.w / 2, game.play->mob[i].rect.y + game.play->mob[i].rect.h / 2};
            move_vector = get_movement_vector(mob, player);
            int speed = 3 + game.play->mob[i].typeMob;
            game.play->mob[i].rect.x += speed * move_vector.x;
            game.play->mob[i].rect.y += speed * move_vector.y;
            mob.x = game.play->mob[i].rect.x + game.play->mob[i].rect.w / 2;
            mob.y = game.play->mob[i].rect.y + game.play->mob[i].rect.h / 2;
            if (player.x - mob.x >= -speed &&  player.x - mob.x <= speed){
                game.play->mob[i].rect.x = player.x - game.play->player_rect.w / 2;
            }
            if (player.y - mob.y >= -speed &&  player.y - mob.y <= speed){
                game.play->mob[i].rect.y = player.y - game.play->player_rect.h / 2;
            }
            SDL_Rect mob_rect = {game.play->mob[i].rect.x, game.play->mob[i].rect.y - TILE_GAME_SIZE, TILE_GAME_SIZE, TILE_GAME_SIZE * 2};
            SDL_Rect player_rect = {game.play->player_rect.x + (-game.play->map_cords.x), game.play->player_rect.y + (-game.play->map_cords.y) - TILE_GAME_SIZE, TILE_GAME_SIZE, TILE_GAME_SIZE * 2};
            if (is_rect_collide_rect(mob_rect, player_rect)){
                game.prev_activity = PLAY;
                game.Activity = QTE;
                int type_mob = game.play->mob[i].typeMob;
                //quit_play();
                init_qte(type_mob, i);
                return;
            }
        }
    }
}


void update_mobs(void){
    update_mobs_animation();
    check_mob_active();
    update_mob_pos();
}

void update_qte_options(void){
    if (game.qte->key_up_on)
    {
        game.qte->key_up_on = false;
        game.qte->active_option--;
        if (game.qte->active_option == -1)
        {
            game.qte->active_option = FIGHT_OPTIONS - 1;
        }
    }
    if (game.qte->key_down_on)
    {
        game.qte->key_down_on = false;
        game.qte->active_option++;

        if (game.qte->active_option == FIGHT_OPTIONS)
        {
            game.qte->active_option = 0;
        }
    }
}

void update_fight(void) {
    if (game.qte->print_result){
        game.qte->speed = (rand() % 11) + 5;
        game.qte->success = false;
        game.qte->print_result = false;
        game.qte->result = 0;
        game.qte->indicator_rect.x = 300;
        game.qte->mode = QTE_MENU;
        game.Activity = QTE;
    }
    if (game.qte->indicator_rect.x >= QTE_END){
        game.qte->success = true;
        game.qte->result = game.qte->indicator_rect.x + game.qte->indicator_rect.w / 2;
    } else if (!game.qte->success) {
        if (game.qte->frame_counter == 2){
            game.qte->indicator_rect.x += game.qte->speed;
            game.qte->frame_counter = 0;
        } else {
            game.qte->frame_counter++;
        }

    }

    if (game.qte->success){
        if (game.qte->result < QTE_END && game.qte->result > QTE_END - 25) {
            strcpy(game.qte->result_text, "You have X2.0 ");
            game.qte->result_multiplier = 2.0;
        } else if (game.qte->result < QTE_END && game.qte->result > QTE_END - 75) {
            strcpy(game.qte->result_text, "You have X1.5 ");
            game.qte->result_multiplier = 1.5;
        } else if (game.qte->result < QTE_END && game.qte->result > QTE_END - 150) {
            strcpy(game.qte->result_text, "You have X1.2 ");
            game.qte->result_multiplier = 1.2;
        } else if (game.qte->result < QTE_END && game.qte->result > QTE_END - 250) {
            strcpy(game.qte->result_text, "You have X1.0 ");
            game.qte->result_multiplier = 1.0;
        } else if (game.qte->result < QTE_END && game.qte->result > QTE_END - 375) {
            strcpy(game.qte->result_text, "You have X0.8 ");
            game.qte->result_multiplier = 0.8;
        } else {
            strcpy(game.qte->result_text, "You have X0.5 ");
            game.qte->result_multiplier = 0.5;
        }
        strcat(game.qte->result_text, game.qte->options[game.qte->active_option].text);
        game.qte->print_result = true;
    }
}

void player_animation(void){
    if (game.play->player_direction != game.play->player_current_frame.y){
        game.play->player_current_frame.y = game.play->player_direction;
        game.play->player_current_frame.x = 0;
        return;
    }
    if (game.play->player_animation_counter == PLAYER_ANIMATION_SPEED){
        if (game.play->movement_vector.x == NONE_OFFST && game.play->movement_vector.y == NONE_OFFST){
            return;
        }
        game.play->player_current_frame.x++;
        if (game.play->player_current_frame.x == PLAYER_ANIMATION_FRAMES){
            game.play->player_current_frame.x = 0;
        }
        game.play->player_animation_counter = 0;
    } else {
        game.play->player_animation_counter++;
    }
}

void update(void){
    eventloop();
    switch (game.Activity) {
        case MAIN_MENU:
            check_btn_focused();
            break;
        case SETTINGS:
            check_btn_focused();
            break;
        case HELP:
            check_btn_focused();
            break;
        case DEVELOPERS:
            check_btn_focused();
            break;
        case CREDITS:
            check_btn_focused();
            break;
        case PLAY:
            movement();
            player_animation();
            update_mobs();
            break;
        case QTE:
            update_qte_options();
            break;
        case FIGHT:
            update_fight();
            break;
    }
}
