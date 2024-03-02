#ifndef THEGAME_HEADER_H
#define THEGAME_HEADER_H


// інклюди
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

// константи
#define SCREEN_WIDTH 1152
#define SCREEN_HEIGHT 720
#define FRAME_DELAY (1000 / 60)

// player
#define DEFAULT_PLAYER_SPEED 6
#define PLAYER_ANIMATION_FRAMES 6
#define PLAYER_ANIMATION_SPEED 6

//mob
#define MOB_ANIMATION_FRAMES 4
#define MOB_FRAME_DELAY 10

// константи для видимої мапи
#define CHUNK_ROWS 15
#define CHUNK_COLS 24
#define TILE_FILE_SIZE 16
#define TILE_FILE_COLS 32
#define TILE_GAME_SIZE  (SCREEN_WIDTH / CHUNK_COLS)

// константи qte
#define FONT_PATH "resources/fonts/EnterCommand.ttf"
#define FIGHT_OPTIONS 3
#define HINT_OPTIONS 5
#define OPTION_BTN_WIDTH 192
#define OPTION_BTN_HEIGHT 36
#define QTE_END 675
#define HEALTHBAR_WIDTH 300
#define HEALTHBAR_HEIGHT 15
#define HEALTHBAR_PADDING 5

// inventory constants
#define CELL_SIZE 50
#define INVENTORY_SIZE 5

// шляхи
#define IMG_PATH "resources/img/"
#define FONT_MENU_PATH "resources/fonts/LiberationSans-Bold.ttf"
#define FONT_QTE_PATH "resources/fonts/EnterCommand.ttf"
#define BTN_PATH "resources/img/button"
#define BACKGROUND_MUSIC "resources/music/background_music.mp3"

#define BACKGROUND_MENU_PATH "resources/img/menu.png"
#define BACKGROUND_MENU_SECOND_PATH "resources/img/menu_surface.png"
#define BACKGROUND_QTE_PATH "resources/img/background.png"
#define BACKGROUND_INVENTORY_PATH "resources/img/inv_wp.png"
#define ESSENCE_PATH "resources/img/essence.png"
#define INDICATOR_PATH "resources/img/indicator.png"
#define PLAYER_HEALTH_PATH "resources/player/player_health.txt"

#define TILESET_PATH "resources/img/visible_tileset.png"
#define INIT_CHUNK_CORDS_PATH "resources/map/init_chunk.txt"
#define CHUNKS_PATH "resources/map/visible_chunks/"
#define PLAYER_IMG "resources/img/player.png"
#define ACTIVE_RADIUS_MOB 300
#define TOTAL_FRAMES 3
// new !!!!!!!!!!!!!!!!!!
#define mob_0_IMG "resources/img/mob/cloud_0.png"
#define mob_1_IMG "resources/img/mob/cloud_1.png"
#define mob_2_IMG "resources/img/mob/cloud_2.png"
#define mob_3_IMG "resources/img/mob/cloud_3.png"

#define mob0_IMG "resources/img/mob/cloud_0_qte.png"
#define mob1_IMG "resources/img/mob/cloud_1_qte.png"
#define mob2_IMG "resources/img/mob/cloud_2_qte.png"
#define mob3_IMG "resources/img/mob/cloud_3_qte.png"

#define QTE_PLAYER_TEXTURE_PATH "resources/img/player_fight.png"
// замінити
#define QTE_MOB_TEXTURE_PATH "resources/img/mob/fly.png" // test замінити на моба

#define QTE_MOB_TYPE0_TEXTURE "resources/img/mob/cloud_0.png"
#define QTE_MOB_TYPE1_TEXTURE "resources/img/mob/cloud_1.png"
#define QTE_MOB_TYPE2_TEXTURE "resources/img/mob/cloud_2.png"
#define QTE_MOB_TYPE3_TEXTURE "resources/img/mob/cloud_3.png"

// enum
// ігрові сцени
enum Activity {
    MAIN_MENU,
    PLAY,
    QTE,
    FIGHT,
    INVENTORY,
    SETTINGS,
    DEVELOPERS,
    HELP,
    CREDITS,
    QUIT
};

// BTN_AMOUNTS ОБОВ'ЯЗКОВО залишається на останній позиції
enum Button_ind {
    PLAY_BTN,
    SETTINGS_BTN,
    HELP_BTN,
    DEVELOPERS_BTN,
    QUIT_BTN,
    MUSIC_BTN,
    SOUND_BTN,
    CREDITS_BTN,
    BACK_BTN,
    BTN_AMOUNTS
};

enum Options_qte{
    // було без визначень
    ATTACK,
    DEFENSE,
    HEAL
};

enum Qte_modes {
    QTE_MENU,
    QTE_MY_TURN,
    QTE_MOB_TURN
};

// зміщення мапи або гравця при русі
enum Movement_offsets {
    NONE_OFFST = 0,
    UP_OFFST = 1,
    DOWN_OFFST = -1,
    LEFT_OFFST = 1,
    RIGHT_OFFST = -1
};

enum Movement_directions{
    UP_DIRECTION,
    DOWN_DIRECTION,
    LEFT_DIRECTION,
    RIGHT_DIRECTION,
    DIRECTION_AMOUNTS
};

// моди переміщення (змінюється координата мапи чи гравця?)
enum Movement_modes {
    MAP_MOVE_MODE,
    PLAYER_MOVE_MOD
};

// ------------------------------------------------------------
// секція clock
// воно працює - не чіпайте
typedef struct ClockStruct Clock;
typedef void (*Func)(Clock clock, unsigned int delay);
struct ClockStruct {
    Uint32 frame_start;
    Uint32 frame_time;
    Func delay;
};
void delay(Clock clock, unsigned int delay);
// end clock
// -------------------------------------------------------------

typedef struct {
    SDL_Rect rect;
    int is_focused;
    SDL_Texture *active;
    SDL_Texture *unactive;
    char *text;     // name
} Button;

typedef struct {
    short int indexes[CHUNK_ROWS][CHUNK_COLS];
} Chunk;

typedef struct {
    int musicOn;
    int soundOn;
} Settings;
extern Settings settings;

typedef struct {
    SDL_Texture *texture;
    char *qte_texture_path;
    SDL_Rect rect;
    int typeMob;
    bool is_alive;
    bool is_active;
    int current_frame;  // Текущий кадр анимации
    int frame_delay;    // Задержка перед сменой кадра
    int frame_counter;
} Mob;

// scene structs

typedef struct {
    // tools
    int speed;
    int result;
    int frame_counter;
    int mode;
    bool success;
    bool print_result;
    int active_option;
    Button options[FIGHT_OPTIONS];
    TTF_Font *font;

    // indicator
    SDL_Rect indicator_rect;
    SDL_Texture *indicator_texture;

    SDL_Texture *basic_background;
    SDL_Texture *qte_backgrounds[FIGHT_OPTIONS];
    SDL_Texture *hints[HINT_OPTIONS];
    SDL_Rect hint_rects[HINT_OPTIONS];
    // hz
    char result_text[128];
    double result_multiplier;
    // player
    int player_attack;
    double player_defense;
    int player_heal;
    double player_health;
    double player_max_health;
    SDL_Texture *player_texture;
    // mob
    int index_mob;
    int mob_attack;
    double mob_defense;
    int mob_heal;
    double mob_health;
    double mob_max_health;
    SDL_Texture *mob_texture;

    bool key_up_on;
    bool key_down_on;
    bool key_up_off;
    bool key_down_off;

    int type_mob;
} Qte;

typedef struct {
    TTF_Font* font;
    SDL_Texture *background_texture;
    SDL_Texture *second_background;
    Button buttons [BTN_AMOUNTS];
} Menu;

typedef struct {
    SDL_Point map_cords;
    SDL_Point init_chank;
    SDL_Rect player_rect;

    SDL_Texture *player_texture;
    SDL_Texture *tileset;
    Chunk visible_map[3][3];
    short int collision_map[CHUNK_ROWS * 6][CHUNK_COLS * 6];

    //movement
    SDL_Point movement_vector;
    short int player_direction;
    short int speed;
    SDL_Point player_current_frame;
    short int player_animation_counter;
    int movement_modes[DIRECTION_AMOUNTS];

    // mobs
    int mobs_amount;
    Mob *mob;
} Play;

typedef struct {
    TTF_Font* font;
    SDL_Texture *background_texture;
    SDL_Texture *gEssenceTexture;
} Inventory;

// основна ігрова структура
// зі змінними, які знадобляться в будь-якій сцені гри
typedef struct {
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    Clock clock;
    int prev_activity;
    int Activity;
    float essenceCount;
    Menu *menu;
    Play *play;
    Inventory *inventory;
    Qte *qte;
    Mix_Music* music;
} Game;
extern Game game;

// ------------------------------------------------------------

// прототипи функцій
// намагаємось не засмічувати цю секцію
// краще створити update, який лише викликає три функціі
// ніж ставити сюди update_map, update_enemy і update_player

void update(void);
void movement(void);

void render(void);
void draw_play(void);

void setup(void);
void init_menu(void);
void quit_menu(void);
void init_play(void);
void quit_play(void);
void init_qte(int type_mob, int index);
void quit_qte(void);
void init_inventory(void);
void quit_inventory(void);

int get_chunk(SDL_Point cords, short int mas[CHUNK_ROWS][CHUNK_COLS]);
int get_collision_chunk(SDL_Point cords, short int mas[CHUNK_ROWS * 2][CHUNK_COLS * 2]);
SDL_Texture *render_text(char *text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer);

void load_map(Chunk (*map)[3][3]);
void load_mob(void);
void load_collision(short int (*map)[CHUNK_ROWS * 6][CHUNK_COLS * 6]);
SDL_Point get_init_chunk_cords(void);

void draw_qte(void);
void draw_fight(void);

void draw_inventory(void);

void sdl_fail_exit(char *msg);
void quit_libraries(void);
void destroy_tools(void);
void playMusic(void);
void stopMusic(void);

void draw_end(void);

#endif
