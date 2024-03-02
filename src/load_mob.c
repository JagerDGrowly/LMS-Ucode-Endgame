//
// Created by oleksandra on 01/03/24.
//
#include "../inc/header.h"

void create_matrix(SDL_Point init_cords, SDL_Point ind_matrix[3][3]) {
    for (int y = -1; y < 2; ++y) {
        for (int x = -1; x < 2; ++x) {
            SDL_Point crd = {init_cords.x + x, init_cords.y + y};
            ind_matrix[y + 1][x + 1] = crd;
        }
    }
}

int read_amount(char *path){
    if (access(path, F_OK) == -1){
        return -1;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        destroy_tools();
        quit_libraries();
        printf("Failed to open chunk file!\n");
        exit(EXIT_FAILURE);
    }
    char buffer[5];
    fscanf(file, "%s", buffer);
    int result = atoi(buffer);
    fclose(file); // Закрытие файла
    return result;
}

void get_mobs_from_chunk(char *path, int amount, Mob *mas){
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        destroy_tools();
        quit_libraries();
        printf("Failed to open chunk file!\n");
        exit(EXIT_FAILURE);
    }
    // Пропускаем первую строку файла
    int c;
    while ((c = fgetc(file)) != EOF && c != '\n');

    int counter = 0;
    while (counter < amount){
        if (fscanf(file, "%d %d %d", &mas[counter].typeMob, &mas[counter].rect.x, &mas[counter].rect.y) != 3) {
            continue; // Если не удалось считать 3 значения, выходим из цикла
        }
        mas[counter].rect.w = TILE_GAME_SIZE;
        mas[counter].rect.h = TILE_GAME_SIZE;
        mas[counter].is_alive = true;
        mas[counter].is_active = false;
        mas[counter].frame_counter = 0;
        mas[counter].current_frame = 0;
        mas[counter].frame_delay = MOB_FRAME_DELAY;

        if (mas[counter].typeMob < 0 || mas[counter].typeMob > 3){
            mas[counter].typeMob = 0;
        }

        if (mas[counter].typeMob == 0){
            mas[counter].texture = IMG_LoadTexture(game.gRenderer, mob_0_IMG);
            if (mas[counter].texture == NULL){
                mas[counter].typeMob = 1;
            } else {
                mas[counter].qte_texture_path = QTE_MOB_TYPE0_TEXTURE;
            }
        }
        if (mas[counter].typeMob == 1){
            mas[counter].texture = IMG_LoadTexture(game.gRenderer, mob_1_IMG);
            if (mas[counter].texture == NULL){
                mas[counter].typeMob = 2;
            } else {
                mas[counter].qte_texture_path = QTE_MOB_TYPE1_TEXTURE;
            }
        }
        if (mas[counter].typeMob == 2){
            mas[counter].texture = IMG_LoadTexture(game.gRenderer, mob_2_IMG);
            if (mas[counter].texture == NULL){
                mas[counter].typeMob = 3;
            } else {
                mas[counter].qte_texture_path = QTE_MOB_TYPE2_TEXTURE;
            }
        }
        if (mas[counter].typeMob == 3){
            mas[counter].texture = IMG_LoadTexture(game.gRenderer, mob_3_IMG);
            if (mas[counter].texture == NULL){
                quit_play();
                destroy_tools();
                quit_libraries();
                sdl_fail_exit("Failed to load mob texture!");
            } else {
                mas[counter].qte_texture_path = QTE_MOB_TYPE3_TEXTURE;
            }
        }
        counter++;
    }

}

void load_mob(void){
    printf("check 0\n");
    fflush(stdout);
    SDL_Point ind_matrix[3][3];
    create_matrix(game.play->init_chank, ind_matrix);
    game.play->mob = NULL;
    int map_mob_amount = 0;
    char path[128];
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            SDL_Point chunk = {ind_matrix[y][x].x, ind_matrix[y][x].y};
            sprintf(path, "resources/map/mob_amount/%d_%d.txt", chunk.y, chunk.x);
            int amount = read_amount(path);
            map_mob_amount += amount;
            Mob *chunk_mobs = (Mob *)malloc(sizeof(Mob) * amount);
            if (amount != 0){
                get_mobs_from_chunk(path, amount, chunk_mobs);
                for (int mob = 0; mob < amount; ++mob) {
                    chunk_mobs[mob].rect.x = (chunk.x - ind_matrix[0][0].x) * SCREEN_WIDTH + chunk_mobs[mob].rect.x;
                    chunk_mobs[mob].rect.y = (chunk.y - ind_matrix[0][0].y) * SCREEN_HEIGHT + chunk_mobs[mob].rect.y;
                }
                if (game.play->mob == NULL){
                    game.play->mob = malloc(sizeof(Mob) * map_mob_amount);
                } else {
                    game.play->mob = realloc(game.play->mob, sizeof(Mob) * map_mob_amount);
                }
                int ind = 0;
                for (int i = map_mob_amount - amount; i < map_mob_amount; i++) {
                    game.play->mob[i] = chunk_mobs[ind];
                    ind++;
                }

            }
            free(chunk_mobs);
        }
    }
    printf("check 1\n");
    fflush(stdout);
    game.play->mobs_amount = map_mob_amount;

}
