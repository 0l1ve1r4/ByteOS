//========================================================================
//    This file is part of ByteOS.
//    Copyright (C) 2024 Guilherme Oliveira Santos
//    This is free software: you can redistribute it and/or modify it 
//    under the terms of the GNU GPL3 or (at your option) any later version. 
//	
//	* File: gaming.h 
//	* Sources: 
//	* Description: Basic VGA Pixel manipulation to do games  
//========================================================================

//========================================================================
 	                            #ifndef GAMING_H
                                #define GAMING_H
//========================================================================

//========================================================================
// 	                                INCLUDES
//========================================================================

#include <kernel/tty.h>     // DrawPixel, getBgColor
#include <kernel/heap.h>    // kmalloc

#include <types.h>          // u8, u16, etc.
#include <limits.h>         // MAX_U8
#include <stdio.h>          // getch
#include <time.h>           // sleep

//========================================================================
// 	                                DEFINES
//========================================================================

// They are defined at tty.h, but with diferent names to gave abstraction 
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

//========================================================================
// 	                                ENUMS
//========================================================================

//========================================================================
// 	                                STRUCTS
//========================================================================

typedef struct Pos {
    u8 x;
    u8 y;
} Pos;

typedef struct Size {
    u8 width; 
    u8 height;
} Size;

// Player is a rectangle :)
typedef struct Player_t {
    Pos pos;
    u8 color;
    Size size;
    void (*draw)(struct Player_t *);  
    void (*delete)(struct Player_t *);
    void (*update)(struct Player_t *, u8, u8);
} Player_t;


//========================================================================
// 	                                FUNCIONS
//========================================================================

/* Draw a pixel in the VGA TextMode interface */
static void draw(Pos pos, u8 color) {
    if (pos.x >= SCREEN_WIDTH || pos.y >= SCREEN_HEIGHT) return;       
    drawPixel(pos.x, pos.y, (char)219, color);  //  (char)219 = █ 
}

static void drawSquare(Pos pos, Size size, u8 color){
    for (u16 i = 0; i < size.width; i++){
        for (u16 j = 0; j < size.height; j++){
            draw((Pos){i + pos.x, j + pos.y}, color);
        }
    }
}

static void drawPlayer(Player_t *p) {
    drawSquare(p->pos, p->size, p->color);
}

static void deletePlayer(Player_t *p) {
    u8 originalColor = p->color;
    p->color = getTerminalBgColor(); 
    drawPlayer(p);
    p->color = originalColor;    
}

static void updatePlayer(Player_t *p, u8 x, u8 y) {
    Pos newPos = {x, y};
    deletePlayer(p);
    p->pos = newPos;
    drawPlayer(p);
}

static Player_t *newPlayer(u8 x, u8 y, u8 color, u8 width, u8 height) {
    Player_t * player = (Player_t*)kMalloc(sizeof(Player_t));
    player->pos.x = x;
    player->pos.y = y;
    player->color = color;
    player->size.width = width;
    player->size.height = height;
    player->draw = &drawPlayer;  
    player->delete = &deletePlayer;
    player->update = &updatePlayer;
    
    return player;
}

static bool checkCollision(Player_t *a, Player_t *b) {
    u8 a_left = a->pos.x;
    u8 a_right = a->pos.x + a->size.width;
    u8 a_top = a->pos.y;
    u8 a_bottom = a->pos.y + a->size.height;

    u8 b_left = b->pos.x;
    u8 b_right = b->pos.x + b->size.width;
    u8 b_top = b->pos.y;
    u8 b_bottom = b->pos.y + b->size.height;

    if (a_left < b_right && a_right > b_left && a_top < b_bottom && 
        a_bottom > b_top) {
        return true; 
    }

    return false;
}


//========================================================================
// 	                                GAMESSSSSS
//========================================================================

#pragma GCC diagnostic ignored "-Wunused-function"

// returns true when win, 0 otherwise
static int pong() {
    terminalClearAll();
    
    u8 ballX = 80/2, ballY = 25/2, playerY = 25/2;
    
    bool isRight  = true;
    bool isDown   =  true;

    Player_t *ball = newPlayer(ballX, ballY, RED_PIXEL, 1, 1);
    Player_t *bot = newPlayer(SCREEN_WIDTH - 1, 25/2, WHITE_PIXEL, 1, 4);
    Player_t *player = newPlayer(1, 25/2, WHITE_PIXEL, 1, 4);

    Player_t *middleArena = newPlayer(SCREEN_WIDTH/2, 0, CYAN_PIXEL, 1, SCREEN_HEIGHT);

    bool isPlayerDown = false;
    bool isPlayerUp = false;
    while (1) { 
        if (ballX >= 70) {
            if (checkCollision(ball, bot)) isRight = false;
        }

        else if (ballX <= 10) 
            if (checkCollision(ball, player)) isRight = true;
        
        if (ballY >= 25) isDown = false;
        else if (ballY <= 0) isDown = true;

        if (isRight) ballX++;
        else ballX--;
        
        if (isDown) ballY++;
        else ballY--;

        u8 c = getchar();
        if (c == 'w'){ 
            isPlayerUp = true;
            isPlayerDown = false;
        }

        else if (c == 's'){
            isPlayerDown = true;
            isPlayerUp =   false;
        }

        if (isPlayerDown && player->pos.y < 25) playerY++;
        else if (isPlayerUp && player->pos.y > 0) playerY--;

        
        ball->update(ball, ballX, ballY);    
        middleArena->draw(middleArena);
        bot->update(bot, bot->pos.x, ballY*0.7);
        player->update(player, player->pos.x, playerY);

        if (ball->pos.x > SCREEN_WIDTH){
            return true;
            
        } else if (ball->pos.x <= 0){
            return false;
        }

        sleep(20000000); 
    }
}
#pragma GCC diagnostic pop

//========================================================================
 	                                #endif
//========================================================================