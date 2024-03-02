//
// Created by oleksandra on 23/02/24.
//

#include "../inc/header.h"

void draw_main_menu(void){
    for (int i = 0; i <= QUIT_BTN; ++i) {
        if (game.menu->buttons[i].is_focused == 1){
            SDL_RenderCopy(game.gRenderer, game.menu->buttons[i].active, NULL, &game.menu->buttons[i].rect);
        } else {
            SDL_RenderCopy(game.gRenderer, game.menu->buttons[i].unactive, NULL, &game.menu->buttons[i].rect);
        }
    }
    if (game.menu->buttons[CREDITS_BTN].is_focused == 1){
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[CREDITS_BTN].active, NULL, &game.menu->buttons[CREDITS_BTN].rect);
    } else {
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[CREDITS_BTN].unactive, NULL, &game.menu->buttons[CREDITS_BTN].rect);
    }
}

void draw_settings(void){
    if (game.menu->buttons[BACK_BTN].is_focused == 1){
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].active, NULL, &game.menu->buttons[BACK_BTN].rect);
    } else {
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].unactive, NULL, &game.menu->buttons[BACK_BTN].rect);
    }
    if (game.menu->buttons[MUSIC_BTN].is_focused == 1){
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[MUSIC_BTN].active, NULL, &game.menu->buttons[MUSIC_BTN].rect);
    } else {
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[MUSIC_BTN].unactive, NULL, &game.menu->buttons[MUSIC_BTN].rect);
    }
    if (game.menu->buttons[SOUND_BTN].is_focused == 1){
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[SOUND_BTN].active, NULL, &game.menu->buttons[SOUND_BTN].rect);
    } else {
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[SOUND_BTN].unactive, NULL, &game.menu->buttons[SOUND_BTN].rect);
    }
}

void draw_credits(void) {
    if (game.menu->buttons[BACK_BTN].is_focused == 1){
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].active, NULL, &game.menu->buttons[BACK_BTN].rect);
    } else {
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].unactive, NULL, &game.menu->buttons[BACK_BTN].rect);
    }

    // Отображение текстуры на экране
    SDL_Rect transparentRect = {60, 55, 1045, 515};
    SDL_RenderCopy(game.gRenderer, game.menu->second_background, NULL, &transparentRect);

    SDL_Color textColor = {255, 255, 255, 255}; // Белый цвет текста

    // Создаем массив строк текста для кредитов
    char* lines[] = {
        "Music used in the game:",
        "Funny Beat By: Fesliyan Studios"
    };

    int lineCount = sizeof(lines) / sizeof(lines[0]); // Определяем количество строк текста

    int posY = SCREEN_HEIGHT / 7.5; // Начальная позиция Y для первой строки

    for (int i = 0; i < lineCount; ++i) {
        SDL_Surface* lineSurface = TTF_RenderText_Solid(game.menu->font, lines[i], textColor);
        SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(game.gRenderer, lineSurface);

        int posX = (SCREEN_WIDTH - lineSurface->w) / 2; // Позиция X для центрирования текста

        SDL_Rect lineRect = {posX, posY, lineSurface->w, lineSurface->h};
        SDL_RenderCopy(game.gRenderer, lineTexture, NULL, &lineRect);

        // Увеличиваем posY для следующей строки текста
        posY += SCREEN_HEIGHT / 11;

        // Освобождаем ресурсы поверхности и текстуры текста
        SDL_FreeSurface(lineSurface);
        SDL_DestroyTexture(lineTexture);
    }
}

void draw_developers(void) {
    if (game.menu->buttons[BACK_BTN].is_focused == 1){
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].active, NULL, &game.menu->buttons[BACK_BTN].rect);
    } else {
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].unactive, NULL, &game.menu->buttons[BACK_BTN].rect);
    }

    SDL_Rect transparentRect = {60, 55, 1045, 515}; // Позиция и размеры серого прямоугольника
    SDL_RenderCopy(game.gRenderer, game.menu->second_background, NULL, &transparentRect);

    SDL_Color textColor = {255, 255, 255, 255}; // Белый цвет текста

    // Создаем массив строк текста
    char* lines[] = {
        "Developers of this game:",
        "Volodymyr Pedenko - composer, developer",
        "Oleksandra Adamenko - graphic designer, developer and troubleshooting",
        "Yevhen Petukhov - graphic designer, developer",
        "Danylo Bazylevych - mob system developer",
        "Maksym Chaban - combat mechanics developer",
        "Maksym Menshov - interface developer"
    };

    int lineCount = sizeof(lines) / sizeof(lines[0]); // Определяем количество строк текста

    int posY = SCREEN_HEIGHT / 7.5; // Начальная позиция Y для первой строки

    for (int i = 0; i < lineCount; ++i) {
        SDL_Surface* lineSurface = TTF_RenderText_Solid(game.menu->font, lines[i], textColor);
        SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(game.gRenderer, lineSurface);

        int posX = (SCREEN_WIDTH - lineSurface->w) / 2; // Позиция X для центрирования текста

        SDL_Rect lineRect = {posX, posY, lineSurface->w, lineSurface->h};
        SDL_RenderCopy(game.gRenderer, lineTexture, NULL, &lineRect);

        // Увеличиваем posY для следующей строки текста
        posY += SCREEN_HEIGHT / 11;

        // Освобождаем ресурсы поверхности и текстуры текста
        SDL_FreeSurface(lineSurface);
        SDL_DestroyTexture(lineTexture);
    }
}

void draw_help(void) {
    if (game.menu->buttons[BACK_BTN].is_focused == 1){
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].active, NULL, &game.menu->buttons[BACK_BTN].rect);
    } else {
        SDL_RenderCopy(game.gRenderer, game.menu->buttons[BACK_BTN].unactive, NULL, &game.menu->buttons[BACK_BTN].rect);
    }

    SDL_Rect transparentRect = {60, 55, 1045, 515};
    SDL_RenderCopy(game.gRenderer, game.menu->second_background, NULL, &transparentRect);

    SDL_Color textColor = {255, 255, 255, 255}; // Белый цвет текста

    // Создаем массив строк текста
    char* lines[] = {
            "Read PDF",
            "Just kidding, here is a guide for you.",
            "Control the arrows, continue self-study, contact other students and you will succeed!",
            "Okay, the inventory opens at E, that's all."
    };

    int lineCount = sizeof(lines) / sizeof(lines[0]); // Определяем количество строк текста

    int posY = SCREEN_HEIGHT / 7.5; // Начальная позиция Y для первой строки

    for (int i = 0; i < lineCount; ++i) {
        SDL_Surface* lineSurface = TTF_RenderText_Solid(game.menu->font, lines[i], textColor);
        SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(game.gRenderer, lineSurface);

        int posX = (SCREEN_WIDTH - lineSurface->w) / 2; // Позиция X для центрирования текста

        SDL_Rect lineRect = {posX, posY, lineSurface->w, lineSurface->h};
        SDL_RenderCopy(game.gRenderer, lineTexture, NULL, &lineRect);

        // Увеличиваем posY для следующей строки текста
        posY += SCREEN_HEIGHT / 11;

        // Освобождаем ресурсы поверхности и текстуры текста
        SDL_FreeSurface(lineSurface);
        SDL_DestroyTexture(lineTexture);
    }
}

void draw_quit(void){
    printf("Quit button clicked!\n");
    // Показать вопрос об выходе
    const SDL_MessageBoxButtonData buttons[] = {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" }, // Yes справа
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "No" },  // No слева
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    { 255, 0, 0 },
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    { 0, 255, 0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    { 255, 255, 0 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    { 0, 0, 255 },
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    { 255, 0, 255 }
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            game.gWindow, /* .window */
            "Exit", /* .title */
            "Are you sure you want to close the game?", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
    if (buttonid == -1 || buttonid == 0) {
        printf("Quit operation canceled!\n");
        game.Activity = game.prev_activity;
    } else {
        printf("Quit operation confirmed!\n");
        FILE *file = fopen(PLAYER_HEALTH_PATH, "w");
        if (file == NULL) {
            printf("Помилка відкриття файлу.\n");
            exit(-1);
        }
        fprintf(file, "%d\n", 100);
        fclose(file);
        if (game.prev_activity == PLAY) {
            quit_play();
        }
        game.Activity = QUIT;
    }
}

void draw_inventory(void) {
    SDL_RenderCopy(game.gRenderer, game.inventory->background_texture, NULL, NULL);

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(game.inventory->font, "Inventory", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game.gRenderer, textSurface);
    SDL_Rect textRect = {SCREEN_WIDTH / 2 - textSurface->w / 2, 10, textSurface->w, textSurface->h};
    SDL_RenderCopy(game.gRenderer, textTexture, NULL, &textRect);

    // Освобождаем память, используемую для текстуры и поверхности
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    // Текст для вывода значения essenceCount
    char essenceText[20];
    snprintf(essenceText, sizeof(essenceText), "your progress: %.1f", game.essenceCount);

    SDL_Surface* essenceSurface = TTF_RenderText_Solid(game.inventory->font, essenceText, textColor);
    SDL_Texture* essenceTexture = SDL_CreateTextureFromSurface(game.gRenderer, essenceSurface);
    SDL_Rect essenceRect = {SCREEN_WIDTH / 2 - essenceSurface->w / 2, 40, essenceSurface->w, essenceSurface->h};
    SDL_RenderCopy(game.gRenderer, essenceTexture, NULL, &essenceRect);

    // Освобождаем память, используемую для текстуры и поверхности
    SDL_DestroyTexture(essenceTexture);
    SDL_FreeSurface(essenceSurface);

    int totalWidth = INVENTORY_SIZE * CELL_SIZE;
    int startX = SCREEN_WIDTH / 2 - totalWidth / 2;

    // Проверка на значение essenceCount
    if (game.essenceCount >= 0 && game.essenceCount <= 5) {
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            int x = startX + i * CELL_SIZE;
            int y = SCREEN_HEIGHT / 2 - CELL_SIZE / 2;

            SDL_Rect cellRect = {x, y, CELL_SIZE, CELL_SIZE};

            // Округление вниз
            int roundedEssenceCount = (int)floor(game.essenceCount);

            if (i < roundedEssenceCount) {
                // Отрисовываем текстуру эссенции поверх ячейки
                SDL_RenderCopy(game.gRenderer, game.inventory->gEssenceTexture, NULL, &cellRect);
            } else {
                // Отрисовываем обычную ячейку
                SDL_SetRenderDrawColor(game.gRenderer, 169, 169, 169, 255);
                SDL_RenderFillRect(game.gRenderer, &cellRect);
                SDL_SetRenderDrawColor(game.gRenderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(game.gRenderer, &cellRect);
            }
        }

        // Проверка, чтобы отображать текст только при essenceCount >= 5
        if (game.essenceCount >= 5) {
            SDL_Surface* endTextSurface = TTF_RenderText_Solid(game.inventory->font, "You can end the game, press enter/return", textColor);
            SDL_Texture* endTextTexture = SDL_CreateTextureFromSurface(game.gRenderer, endTextSurface);
            SDL_Rect endTextRect = {SCREEN_WIDTH / 2 - endTextSurface->w / 2, SCREEN_HEIGHT - 50, endTextSurface->w, endTextSurface->h};
            SDL_RenderCopy(game.gRenderer, endTextTexture, NULL, &endTextRect);

            // Освобождаем память, используемую для текстуры и поверхности
            SDL_DestroyTexture(endTextTexture);
            SDL_FreeSurface(endTextSurface);
        }
    } else {
        // Просто ограничиваем essenceCount до 5
        game.essenceCount = 5;

        // Отрисовываем только пять ячеек с текстурами эссенций
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            int x = startX + i * CELL_SIZE;
            int y = SCREEN_HEIGHT / 2 - CELL_SIZE / 2;

            SDL_Rect cellRect = {x, y, CELL_SIZE, CELL_SIZE};

            if (i < game.essenceCount) {
                // Отрисовываем текстуру эссенции поверх ячейки
                SDL_RenderCopy(game.gRenderer, game.inventory->gEssenceTexture, NULL, &cellRect);
            } else {
                // Отрисовываем обычную ячейку
                SDL_SetRenderDrawColor(game.gRenderer, 169, 169, 169, 255);
                SDL_RenderFillRect(game.gRenderer, &cellRect);
                SDL_SetRenderDrawColor(game.gRenderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(game.gRenderer, &cellRect);
            }
        }
    }
}

void draw_end(void) {
    printf("The End");
}

void playMusic(void) {
    if (Mix_PlayingMusic() == 0) {

        game.music = Mix_LoadMUS(BACKGROUND_MUSIC);
        if (game.music == NULL) {
            printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        } else {
            Mix_PlayMusic(game.music, -1);
        }
    }
}

void stopMusic(void) {
    if (Mix_PlayingMusic() != 0) {
        Mix_HaltMusic();
        if (game.music != NULL) {
            Mix_FreeMusic(game.music);
            game.music = NULL;
        }
    }
}


void render(void){
    SDL_SetRenderDrawColor(game.gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(game.gRenderer);

    switch (game.Activity) {
        case MAIN_MENU:
            SDL_RenderCopy(game.gRenderer, game.menu->background_texture, NULL, NULL);
            // Рисуем элементы главного меню
            draw_main_menu();
            break;
        case PLAY:
            draw_play();
            break;
        case QTE:
            draw_qte();
            break;
        case FIGHT:
            draw_fight();
            break;
        case SETTINGS:
            SDL_RenderCopy(game.gRenderer, game.menu->background_texture, NULL, NULL);
            draw_settings();
            break;
        case DEVELOPERS:
            SDL_RenderCopy(game.gRenderer, game.menu->background_texture, NULL, NULL);
            draw_developers();
            break;
        case CREDITS:
            SDL_RenderCopy(game.gRenderer, game.menu->background_texture, NULL, NULL);
            draw_credits();
            break;
        case HELP:
            SDL_RenderCopy(game.gRenderer, game.menu->background_texture, NULL, NULL);
            draw_help();
            break;
        case QUIT:
            draw_quit();
            break;
        case INVENTORY:
            draw_inventory();
            break;
    }
    SDL_RenderPresent(game.gRenderer);
}
