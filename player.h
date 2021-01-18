#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "ssd1306.h"
#include "bullet.h"


#define PLAYER_WIDTH 7
#define PLAYER_HEIGHT 3
#define START_POS_X 64 - PLAYER_WIDTH/2
#define START_POS_Y 56
#define PLAYER_SHOOT_COOLDOWN 700 //in ms
#define PLAYER_SPEED 1 // pixel per frame

typedef struct Player {
  SPRITE sprite = ssd1306_createSprite(START_POS_X, START_POS_Y, sizeof(playerBMP),  playerBMP);
  Bullet bullet;
} Player;

void init_player(Player *p) {
   p->bullet.sprite = ssd1306_createSprite(0, 0, sizeof(shootSprite),  shootSprite);  
   p->sprite.draw();
}

void playerDraw(Player *const p) {
  if (p->sprite.x != p->sprite.lx || p->sprite.y != p->sprite.ly) {
    p->sprite.eraseTrace();
    p->sprite.draw();
  }
}

static void playerMove(Player *const p) {
  if (IS_RIGHT_PAD_PRESSED) {
    p->sprite.x += PLAYER_SPEED;
  } else if (IS_DOWN_PAD_PRESSED) {
    p->sprite.x += PLAYER_SPEED;
  } else if (IS_LEFT_PAD_PRESSED) {
    p->sprite.x -= PLAYER_SPEED;
  } else if (IS_UP_PAD_PRESSED) {
    p->sprite.x -= PLAYER_SPEED;
  }
}

static void playerShoot(Player *const p) {
  static unsigned long lastShootTime = 0;
  if (IS_A_BUTTON_PRESSED && millis() - lastShootTime >= PLAYER_SHOOT_COOLDOWN) {
    lastShootTime = millis();
    shoot(&p->bullet, p->sprite.x + 4, p->sprite.y - 4);
    note(7,4);
  }
  if (IS_B_BUTTON_PRESSED) {
    p->sprite.x = START_POS_X;
    p->sprite.y = START_POS_Y;
  }
}

void playerUpdate(Player *const player) {
  playerMove(player);
  playerShoot(player);
  bulletUpdate(&player->bullet);
}

#endif
