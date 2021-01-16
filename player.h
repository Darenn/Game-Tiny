#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "ssd1306.h"

#define START_POS_X 64
#define START_POS_Y 55

typedef struct Player {
  uint_fast8_t speed = 1; // in pixel per frame COULD BE OPTIMIZED IF NOT CHANGED DURING GAME
  SPRITE sprite;
} Player;

Player* playerCreate() {
  Player* player = malloc(sizeof(Player));
  player->sprite = ssd1306_createSprite(START_POS_X, START_POS_Y, sizeof(playerBMP),  playerBMP);
  player->speed = 1;
  return player;
}

void playerDraw(Player *const p) {
  if (p->sprite.x != p->sprite.lx || p->sprite.y != p->sprite.ly) {
    p->sprite.eraseTrace();
    p->sprite.draw();
  }
}

void playerForceDraw(Player *const p) {
  p->sprite.eraseTrace();
  p->sprite.draw();
}

static void playerMove(Player *const p) {
  if (getPadRightPressed()) {
    p->sprite.x += p->speed;
    note(1, 3);
  } else if (getPadDownPressed()) {
    p->sprite.x -= p->speed;
    note(2, 3);
  } else if (getPadLeftPressed()) {
    p->sprite.x -= p->speed;
    note(3, 3);
  } else if (getPadUpPressed()) {
    p->sprite.x += p->speed;
    note(4, 3);
  }
}

static void playerShoot(Player *const p) {
  p->speed = 1;
  if (getButtonAPressed()) {
    //bulletCreate(p->sprite.x + 3, p->sprite.y - 5);
  }
  if (getButtonBPressed()) {
    p->sprite.x = START_POS_X;
    p->sprite.y = START_POS_Y;
  }
}

void playerUpdate(Player *const player) {
  playerMove(player);
  playerShoot(player);
}

#endif
