// Drawing a pseudo "pixel" in text mode using ASCII characters

#include <kernel/tty.h>

/* THESE VALUES ARE ALREADY DEFINED AT tty.h, but with diferentes names to
 gave abstraction */
#define BLACK_PIXEL        0x00
#define BLUE_PIXEL         0x01
#define GREEN_PIXEL        0x02
#define CYAN_PIXEL         0x03
#define RED_PIXEL          0x04
#define MAGENTA_PIXEL      0x05
#define BROWN_PIXEL        0x06
#define LIGHT_GREY_PIXEL   0x07
#define DARK_GREY_PIXEL    0x08
#define LIGHT_BLUE_PIXEL   0x09
#define LIGHT_GREEN_PIXEL  0x0A
#define LIGHT_CYAN_PIXEL   0x0B
#define LIGHT_RED_PIXEL    0x0C
#define LIGHT_MAGENTA_PIXEL 0x0D
#define YELLOW_PIXEL       0x0E
#define WHITE_PIXEL        0x0F

#define SCREEN_WIDTH 75
#define SCREEN_HEIGHT 25

#include <types.h>
#include <limits.h>

#include <stdio.h>
#include <time.h>

/* Draw a pixel in the VGA TextMode interface */
static void draw(u16 x, u16 y, u8 color) {
    if (x > 80 || y > 25) return;       //  outside vga text-mode
    drawPixel(x, y, (char)219, color);  //  (char)219 = █ 
}

static void drawSquare(u8 x, u8 y, u8 size, u8 color){
    for (u16 i = 0; i < size; i++){
        for (u16 j = 0; j < size; j++){
            draw(i + x, j + y, color);
        }
    }
}

typedef struct {
    u8 x;
    u8 y;
} Pos;

typedef struct Player_t {
    Pos pos;
    u8 color;
    u8 size;
    void (*draw)(struct Player_t *);  
    void (*delete)(struct Player_t *);
    void (*update)(struct Player_t *, u8, u8);
} Player_t;


static void drawPlayer(Player_t *p) {
    drawSquare(p->pos.x, p->pos.y, p->size, p->color);
}

static void deletePlayer(Player_t *p) {
    u8 originalColor = p->color;
    p->color = getTerminalBgColor();
    drawPlayer(p);
    p->color = originalColor;    
}

static void updatePlayer(Player_t *p, u8 newX, u8 newY){
    // update = delete + draw
    deletePlayer(p);
    p->pos.x = newX;
    p->pos.y = newY;
    drawPlayer(p);
}

static Player_t *newPlayer(u8 x, u8 y, u8 color, u8 size) {
    Player_t * player = (Player_t*)kMalloc(sizeof(Player_t));
        player->pos.x = x;
        player->pos.y = y;
        player->color = color;
        player->size = size;
        player->draw = &drawPlayer;  
        player->delete = &deletePlayer;
        player->update = &updatePlayer;
    
    return player;
}

static bool checkCollision(Player_t *a, Player_t *b){
    if (a->pos.x == b->pos.x && a->pos.y == b->pos.y){
        return true;
    }

    return false;
}
