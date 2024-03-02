//
// Created by oleksandra on 25/02/24.
//
#include "../inc/header.h"

SDL_Point get_new_init_chunk(SDL_Point chunk){
    switch(game.play->player_direction) {
        case UP_DIRECTION:
            chunk.y--;
            break;
        case DOWN_DIRECTION:
            chunk.y++;
            break;
        case LEFT_DIRECTION:
            chunk.x--;
            break;
        case RIGHT_DIRECTION:
            chunk.x++;
            break;
        default:
            break;
    }
    return chunk;
}

SDL_Point get_chunk_cords(SDL_Point center, int x, int y){
    SDL_Point result = center;
    switch(game.play->player_direction) {
        case UP_DIRECTION:
            result.x = center.x - 1 + x;
            result.y = center.y - 1;
            return result;
        case DOWN_DIRECTION:
            result.x = center.x - 1 + x;
            result.y = center.y + 1;
            return result;
        case LEFT_DIRECTION:
            result.x = center.x - 1;
            result.y = center.y - 1 + y;
            return result;
        case RIGHT_DIRECTION:
            result.x = center.x + 1;
            result.y = center.y - 1 + y;
            return result;
        default:
            return result;
    }
}

bool try_to_move(int x, int y, Chunk map[3][3]){
    if (game.play->player_direction == UP_DIRECTION && y != 0){
        // зміщення існуючого чанка на нову позицію
        map[y][x] = game.play->visible_map[y - 1][x];
        return true;
    } else if (game.play->player_direction == DOWN_DIRECTION && y != 2){
        // зміщення існуючого чанка на нову позицію
        map[y][x] = game.play->visible_map[y + 1][x];
        return true;
    } else if (game.play->player_direction == LEFT_DIRECTION && x != 0){
        // зміщення існуючого чанка на нову позицію
        map[y][x] = game.play->visible_map[y][x - 1];
        return true;
    } else if (game.play->player_direction == RIGHT_DIRECTION && x != 2){
        // зміщення існуючого чанка на нову позицію
        map[y][x] = game.play->visible_map[y][x + 1];
        return true;
    }
    return false;
}

void update_map(void){
    // призначення змінних
    Chunk new_map[3][3];
    short int new_collision_map[CHUNK_ROWS * 6][CHUNK_COLS * 6];
    short int collision_indexes[CHUNK_ROWS * 2][CHUNK_COLS * 2];
    short int indexes[CHUNK_ROWS][CHUNK_COLS];
    SDL_Point new_init_chunk = get_new_init_chunk(game.play->init_chank);

    // заповнення новогго масиву чанків
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
             // отримуємо координати чанка
            SDL_Point chunk_cords = get_chunk_cords(new_init_chunk, x, y);
            // записуємо collision
            if (get_collision_chunk(chunk_cords, collision_indexes) == -1) {
                // зміна моду, вихід без змін
                game.play->movement_modes[game.play->player_direction] = PLAYER_MOVE_MOD;
                return;
            }

            for (int row = 0; row < CHUNK_ROWS * 2; ++row) {
                for (int col = 0; col < CHUNK_COLS * 2; ++col) {
                    new_collision_map[y * CHUNK_ROWS * 2 + row][x * CHUNK_COLS * 2 + col] = collision_indexes[row][col];
                }
            }

            //записуємо visible
            if (try_to_move(x, y, new_map)){
                continue;
            }
            if (get_chunk(chunk_cords, indexes) == -1) {
                // зміна моду, вихід без змін
                game.play->movement_modes[game.play->player_direction] = PLAYER_MOVE_MOD;
                return;
            }
            memcpy(new_map[y][x].indexes, indexes, sizeof(indexes));
        }
    }
    // збереження змін
    game.play->init_chank = new_init_chunk;
    memcpy(game.play->visible_map, new_map, sizeof(game.play->visible_map));
    memcpy(game.play->collision_map, new_collision_map, sizeof(game.play->visible_map));

    // apply map offset
    switch (game.play->player_direction) {
        case UP_DIRECTION:
            game.play->map_cords.y -= SCREEN_HEIGHT;
            break;
        case DOWN_DIRECTION:
            game.play->map_cords.y += SCREEN_HEIGHT;
            break;
        case LEFT_DIRECTION:
            game.play->map_cords.x -= SCREEN_WIDTH;
            break;
        case RIGHT_DIRECTION:
            game.play->map_cords.x += SCREEN_WIDTH;
            break;
    }
    free(game.play->mob);
    load_mob();
    for (int i = 0; i < game.play->mobs_amount; ++i) {
        printf("mob rect: %d %d %d %d\n", game.play->mob[i].rect.x, game.play->mob[i].rect.y, game.play->mob[i].rect.w, game.play->mob[i].rect.h);
    }
}

void check_map_update(void){
    if (game.play->movement_vector.y == 0 && game.play->movement_vector.x == 0){
        return;     // не рухається
    }
    if (game.play->player_direction == DOWN_DIRECTION || game.play->player_direction == UP_DIRECTION){
        if (game.play->map_cords.y < 0 && game.play->map_cords.y > -2 * SCREEN_HEIGHT){
            return;     // не біля границі
        }
        if (game.play->map_cords.y >= 0 && game.play->player_direction == DOWN_DIRECTION){
            // рухається в протилежному до границі напрямку
            game.play->map_cords.y = 0;
            game.play->movement_modes[DOWN_DIRECTION] = MAP_MOVE_MODE;
            return;
        }  else if (game.play->map_cords.y <= -2 * SCREEN_HEIGHT && game.play->player_direction == UP_DIRECTION){
            // рухається в протилежному до границі напрямку
            game.play->map_cords.y = -2 * SCREEN_HEIGHT;
            game.play->movement_modes[UP_DIRECTION] = MAP_MOVE_MODE;
            return;
        }
    }
    else {
        if (game.play->map_cords.x < 0 && game.play->map_cords.x > -2 * SCREEN_WIDTH){
            return;     // не біля границі
        }
        if ((game.play->map_cords.x >= 0 && game.play->player_direction == RIGHT_DIRECTION) ||
            (game.play->map_cords.x <= -2 * SCREEN_WIDTH && game.play->player_direction == LEFT_DIRECTION)){
            // рухається в протилежному до границі напрямку
            game.play->movement_modes[LEFT_DIRECTION] = MAP_MOVE_MODE;
            game.play->movement_modes[RIGHT_DIRECTION] = MAP_MOVE_MODE;
            return;
        }
    }
    update_map();
}

void apply_map_vertical(void){
    game.play->map_cords.y += game.play->movement_vector.y * game.play->speed;
    game.play->map_cords.y = (game.play->map_cords.y > 0)? 0: game.play->map_cords.y;
    game.play->map_cords.y = (game.play->map_cords.y < -2 * SCREEN_HEIGHT)? -2 * SCREEN_HEIGHT: game.play->map_cords.y;
}

void apply_map_horizontal(void){
    game.play->map_cords.x += game.play->movement_vector.x * game.play->speed;
    game.play->map_cords.x = (game.play->map_cords.x > 0)? 0: game.play->map_cords.x;
    game.play->map_cords.x = (game.play->map_cords.x < -2 * SCREEN_WIDTH)? -2 * SCREEN_WIDTH: game.play->map_cords.x;
}

void apply_player_vertical(void){
    SDL_Point prev_cords = {game.play->player_rect.x, game.play->player_rect.y};
    game.play->player_rect.y -= game.play->movement_vector.y * game.play->speed;
    game.play->player_rect.y = (game.play->player_rect.y < 0)? 0: game.play->player_rect.y;
    game.play->player_rect.y = (game.play->player_rect.y > SCREEN_HEIGHT - game.play->player_rect.h)? SCREEN_HEIGHT - game.play->player_rect.h: game.play->player_rect.y;
    if (game.play->player_rect.y > SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2 && prev_cords.y < SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2){
        game.play->player_rect.y = SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2;
    } else if (game.play->player_rect.y < SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2 && prev_cords.y > SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2){
        game.play->player_rect.y = SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2;
    }
}

void apply_player_horizontal(void){
    SDL_Point prev_cords = {game.play->player_rect.x, game.play->player_rect.y};
    game.play->player_rect.x -= game.play->movement_vector.x * game.play->speed;
    game.play->player_rect.x = (game.play->player_rect.x < 0)? 0: game.play->player_rect.x;
    game.play->player_rect.x = (game.play->player_rect.x > SCREEN_WIDTH - game.play->player_rect.w)? SCREEN_WIDTH - game.play->player_rect.w: game.play->player_rect.x;
    if (game.play->player_rect.x > SCREEN_WIDTH / 2 - game.play->player_rect.w / 2 && prev_cords.x < SCREEN_WIDTH / 2 - game.play->player_rect.w / 2){
        game.play->player_rect.x = SCREEN_WIDTH / 2 - game.play->player_rect.w / 2;
    } else if (game.play->player_rect.x < SCREEN_WIDTH / 2 - game.play->player_rect.w / 2 && prev_cords.x > SCREEN_WIDTH / 2 - game.play->player_rect.w / 2){
        game.play->player_rect.x = SCREEN_WIDTH / 2 - game.play->player_rect.w / 2;
    }
}

void vertical(void){
    if (game.play->player_direction == UP_DIRECTION){
        if (game.play->map_cords.y < 0 && game.play->player_rect.y == SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2){
            apply_map_vertical();
        } else if (game.play->map_cords.y > 0){
            game.play->map_cords.y = 0;
            apply_player_vertical();
        } else {
            apply_player_vertical();
        }
    } else {
        if (game.play->map_cords.y > -2 * SCREEN_HEIGHT && game.play->player_rect.y == SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2) {
            apply_map_vertical();
        } else if (game.play->map_cords.y < -2 * SCREEN_HEIGHT){
            game.play->map_cords.y = -2 * SCREEN_HEIGHT;
            apply_player_vertical();
        } else {
            apply_player_vertical();
        }
    }
}

void horizontal(void){
    if (game.play->player_direction == LEFT_DIRECTION){
        if (game.play->map_cords.x < 0 && game.play->player_rect.x == SCREEN_WIDTH / 2 - game.play->player_rect.w / 2) {
            apply_map_horizontal();
        } else if (game.play->map_cords.x > 0){
            game.play->map_cords.x = 0;
            apply_player_horizontal();
        } else {
            apply_player_horizontal();
        }
    } else {
        if (game.play->map_cords.x > -2 * SCREEN_WIDTH && game.play->player_rect.x == SCREEN_WIDTH / 2 - game.play->player_rect.w / 2){
            apply_map_horizontal();
        } else if (game.play->map_cords.x < -2 * SCREEN_WIDTH){
            game.play->map_cords.x = -2 * SCREEN_WIDTH;
            apply_player_horizontal();
        } else {
            apply_player_horizontal();
        }
    }
}

void check_map_collision(void){
    SDL_Point abs_cords = {game.play->player_rect.x + (-game.play->map_cords.x), game.play->player_rect.y + (-game.play->map_cords.y)};
    SDL_Point file_cords;
    SDL_Point file_cords2;
    switch (game.play->player_direction) {
        case UP_DIRECTION:
            file_cords.x = (abs_cords.x + game.play->player_rect.w - 10) / (TILE_GAME_SIZE / 2);
            file_cords.y = abs_cords.y / (TILE_GAME_SIZE / 2);
            file_cords2.x = (abs_cords.x + 10) / (TILE_GAME_SIZE / 2);
            file_cords2.y = abs_cords.y / (TILE_GAME_SIZE / 2);
            if (game.play->collision_map[file_cords.y][file_cords.x] == 1 || game.play->collision_map[file_cords2.y][file_cords2.x] == 1){
                if (game.play->map_cords.y < 0 && game.play->player_rect.y == SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2){
                    game.play->map_cords.y = (game.play->map_cords.y / (TILE_GAME_SIZE / 2) - 1) * (TILE_GAME_SIZE / 2) - 1;
                } else {
                    game.play->player_rect.y = (game.play->player_rect.y / 24 + 1) * 24 + 1;
                }
            }
            break;
        case DOWN_DIRECTION:
            file_cords.x = (abs_cords.x + game.play->player_rect.w - 10) / (TILE_GAME_SIZE / 2);
            file_cords.y = (abs_cords.y + game.play->player_rect.h) / (TILE_GAME_SIZE / 2);
            file_cords2.x = (abs_cords.x + 10) / (TILE_GAME_SIZE / 2);
            file_cords2.y = (abs_cords.y + game.play->player_rect.h) / (TILE_GAME_SIZE / 2);
            if (game.play->collision_map[file_cords.y][file_cords.x] == 1 || game.play->collision_map[file_cords2.y][file_cords2.x] == 1){
                if (game.play->map_cords.y > -2 * SCREEN_HEIGHT && game.play->player_rect.y == SCREEN_HEIGHT / 2 - game.play->player_rect.h / 2){
                    game.play->map_cords.y = (game.play->map_cords.y / (TILE_GAME_SIZE / 2)) * (TILE_GAME_SIZE / 2) + 1;
                } else {
                    game.play->player_rect.y = (game.play->player_rect.y / 24) * 24 - 1;
                }
            }
            break;
        case LEFT_DIRECTION:
            file_cords.x = abs_cords.x / (TILE_GAME_SIZE / 2);
            file_cords.y = (abs_cords.y + game.play->player_rect.h - 10) / (TILE_GAME_SIZE / 2);
            file_cords2.x = abs_cords.x / (TILE_GAME_SIZE / 2);
            file_cords2.y = (abs_cords.y + 10) / (TILE_GAME_SIZE / 2);
            if (game.play->collision_map[file_cords.y][file_cords.x] == 1 || game.play->collision_map[file_cords2.y][file_cords2.x] == 1){
                if (game.play->map_cords.x < 0 && game.play->player_rect.x == SCREEN_WIDTH / 2 - game.play->player_rect.w / 2){
                    game.play->map_cords.x = (game.play->map_cords.x / (TILE_GAME_SIZE / 2) - 1) * (TILE_GAME_SIZE / 2) - 1;
                } else {
                    printf("applying for player\n");
                    fflush(stdout);
                    game.play->player_rect.x = (game.play->player_rect.x / 24 + 1) * 24 + 1;
                }
            }
            break;
        case RIGHT_DIRECTION:
            file_cords.x = (abs_cords.x + game.play->player_rect.w) / (TILE_GAME_SIZE / 2);
            file_cords.y = (abs_cords.y + game.play->player_rect.h - 10) / (TILE_GAME_SIZE / 2);
            file_cords2.x = (abs_cords.x + game.play->player_rect.w) / (TILE_GAME_SIZE / 2);
            file_cords2.y = (abs_cords.y + 10) / (TILE_GAME_SIZE / 2);
            if (game.play->collision_map[file_cords.y][file_cords.x] == 1 || game.play->collision_map[file_cords2.y][file_cords2.x] == 1){
                if (game.play->map_cords.x > -2 * SCREEN_WIDTH && game.play->player_rect.x == SCREEN_WIDTH / 2 - game.play->player_rect.w / 2){
                    game.play->map_cords.x = (game.play->map_cords.x / (TILE_GAME_SIZE / 2)) * (TILE_GAME_SIZE / 2) - 1;
                } else {
                    game.play->player_rect.x = (game.play->player_rect.x / 24 - 1) * 24 - 1;
                }
            }
            break;
    }
}

void movement(void){
    if (game.play->movement_vector.x == NONE_OFFST && game.play->movement_vector.y == NONE_OFFST) {
        return;
    }
    // horizontal movement
    if (game.play->player_direction == LEFT_DIRECTION || game.play->player_direction == RIGHT_DIRECTION) {
        horizontal();
        check_map_collision();
        check_map_update();
        return;
    }
    // vertical movement
    vertical();
    check_map_collision();
    check_map_update();
}
