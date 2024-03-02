
//
// Created by oleksandra on 25/02/24.
//

#include "../inc/header.h"
void draw_chunk(Chunk chunk, SDL_Point chunk_cords){
    SDL_Rect file_tile = {0, 0, TILE_FILE_SIZE, TILE_FILE_SIZE};
    SDL_Rect game_tile = {chunk_cords.x, chunk_cords.y, TILE_GAME_SIZE, TILE_GAME_SIZE};
    SDL_Point cords;
    for (int y = 0; y < CHUNK_ROWS; ++y) {
        for (int x = 0; x < CHUNK_COLS; ++x) {
            int index = chunk.indexes[y][x];
            cords.y = index / TILE_FILE_COLS;
            cords.x = index % TILE_FILE_COLS;
            file_tile.x = cords.x * TILE_FILE_SIZE;
            file_tile.y = cords.y * TILE_FILE_SIZE;
            game_tile.x = chunk_cords.x + x * TILE_GAME_SIZE;
            game_tile.y = chunk_cords.y + y * TILE_GAME_SIZE;
            SDL_RenderCopy(game.gRenderer, game.play->tileset, &file_tile, &game_tile);
        }
    }
}

void draw_map(void){
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            SDL_Point chunk_cords = {game.play->map_cords.x + x * SCREEN_WIDTH, game.play->map_cords.y + y * SCREEN_HEIGHT};
            draw_chunk(game.play->visible_map[y][x], chunk_cords);
        }
    }
}

void draw_player(void){
    SDL_Rect drawing_rect = game.play->player_rect;
    drawing_rect.y -= game.play->player_rect.h;
    drawing_rect.h += game.play->player_rect.h;
    SDL_Rect texture_rect = {game.play->player_current_frame.x * 16, game.play->player_current_frame.y * 32, 16, 32};
    SDL_RenderCopy(game.gRenderer, game.play->player_texture, &texture_rect, &drawing_rect);
}

void draw_mob(void){
    SDL_Rect drawing_rect = {0, 0, TILE_GAME_SIZE, TILE_GAME_SIZE};
    SDL_Rect texture_rect = {0, 0, 16, 16};
    for (int i = 0; i < game.play->mobs_amount; ++i) {
        if (game.play->mob[i].is_alive){
            drawing_rect.x = game.play->mob[i].rect.x + game.play->map_cords.x;
            drawing_rect.y = game.play->mob[i].rect.y + game.play->map_cords.y;
            texture_rect.x = game.play->mob[i].current_frame * 16;
            SDL_RenderCopy(game.gRenderer, game.play->mob[i].texture, &texture_rect, &drawing_rect);
        }
    }
}

void draw_play(void){
    draw_map();
    draw_player();
    draw_mob();
}
