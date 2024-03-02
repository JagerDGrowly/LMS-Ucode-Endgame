//
// Created by oleksandra on 25/02/24.
//

#include "../inc/header.h"

SDL_Point get_init_chunk_cords(void){
    FILE *file = fopen(INIT_CHUNK_CORDS_PATH, "r"); // Открытие файла для чтения
    if (file == NULL) {
        destroy_tools();
        quit_libraries();
        printf("Failed to open init chunk file!\n");
        exit(EXIT_FAILURE);
    }

    SDL_Point result;

    if (fscanf(file, "%d %d", &result.x, &result.y) != 2) {
        destroy_tools();
        quit_libraries();
        printf("Failed to read cords from init chunk file!\n");
        exit(EXIT_FAILURE);
    }

    fclose(file); // Закрытие файла
    return result;
}

void get_chunk_file_name(SDL_Point cords, char *str, int flag){
    if (flag == 0){
        sprintf(str, "resources/map/visible_chunks/%d_%d.txt", cords.y, cords.x);
    } else {
        sprintf(str, "resources/map/collision_chunks/%d_%d.txt", cords.y, cords.x);
    }
}

void create_index_matrix(SDL_Point init_cords, SDL_Point ind_matrix[3][3]) {
    for (int y = -1; y < 2; ++y) {
        for (int x = -1; x < 2; ++x) {
            SDL_Point crd = {init_cords.x + x, init_cords.y + y};
            ind_matrix[y + 1][x + 1] = crd;
        }
    }
}

void parser(FILE *file, short int mas[CHUNK_ROWS][CHUNK_COLS]){
    char buffer[5]; // Предполагаем, что максимальная длина числа - 5 символов
    SDL_Point point = {0, 0};
    // Считываем числа из файла, пока не достигнем конца файла
    while (fscanf(file, "%s", buffer) != EOF) {
        // Преобразуем считанную строку в число
        int number = atoi(buffer);
        mas[point.y][point.x++] = number;
        if (point.x == CHUNK_COLS){
            point.y++;
            point.x = 0;
        }
        if (point.y == CHUNK_ROWS){
            break;
        }
    }
}

void parser_collision(FILE *file, short int mas[CHUNK_ROWS * 2][CHUNK_COLS * 2]){
    char buffer[5]; // Предполагаем, что максимальная длина числа - 5 символов
    SDL_Point point = {0, 0};
    // Считываем числа из файла, пока не достигнем конца файла
    while (fscanf(file, "%s", buffer) != EOF) {
        // Преобразуем считанную строку в число
        int number = atoi(buffer);
        mas[point.y][point.x++] = number;
        if (point.x == CHUNK_COLS * 2){
            point.y++;
            point.x = 0;
        }
        if (point.y == CHUNK_ROWS * 2){
            break;
        }
    }
}


int get_chunk(SDL_Point cords, short int mas[CHUNK_ROWS][CHUNK_COLS]){

    char file_name[64];
    get_chunk_file_name(cords, file_name, 0);

    if (access(file_name, F_OK) == -1){
        return -1;
    }

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        destroy_tools();
        quit_libraries();
        printf("Failed to open chunk file!\n");
        exit(EXIT_FAILURE);
    }

    parser(file, mas);
    return 0;
}

int get_collision_chunk(SDL_Point cords, short int mas[CHUNK_ROWS * 2][CHUNK_COLS * 2]){

    char file_name[64];
    get_chunk_file_name(cords, file_name, 1);

    if (access(file_name, F_OK) == -1){
        return -1;
    }

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        destroy_tools();
        quit_libraries();
        printf("Failed to open chunk file!\n");
        exit(EXIT_FAILURE);
    }
    parser_collision(file, mas);
    return 0;
}

void load_map(Chunk (*map)[3][3]){
    // get indexes matrix
    SDL_Point ind_matrix[3][3];
    create_index_matrix(game.play->init_chank, ind_matrix);

    // get chunks matrix
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            short int indexes[CHUNK_ROWS][CHUNK_COLS];
            int result = get_chunk(ind_matrix[y][x], indexes);

            if (result == -1) {
                return;
            }
            for (int row = 0; row < CHUNK_ROWS; ++row) {
                for (int col = 0; col < CHUNK_COLS; ++col) {
                    (*map)[y][x].indexes[row][col] = indexes[row][col];
                }
            }
        }
    }
}

void load_collision(short int (*map)[CHUNK_ROWS * 6][CHUNK_COLS * 6]){
    SDL_Point ind_matrix[3][3];
    create_index_matrix(game.play->init_chank, ind_matrix);
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            short int indexes[CHUNK_ROWS * 2][CHUNK_COLS * 2];
            int result = get_collision_chunk(ind_matrix[y][x], indexes);
            if (result == -1) {
                return;
            }

            for (int row = 0; row < CHUNK_ROWS * 2; ++row) {
                for (int col = 0; col < CHUNK_COLS * 2; ++col) {
                    (*map)[y * CHUNK_ROWS * 2 + row][x * CHUNK_COLS * 2 + col] = indexes[row][col];
                }
            }
        }
    }
}
