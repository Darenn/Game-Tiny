#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "ssd1306.h"
#include "bullet.h"
#include "invader.h"


#define PLAYER_WIDTH 7
#define PLAYER_HEIGHT 3
#define START_POS_X 64 - PLAYER_WIDTH/2
#define START_POS_Y 56
#define PLAYER_SHOOT_COOLDOWN 600 //in ms
#define PLAYER_SPEED 2 // pixel per frame

typedef struct Player {
  SPRITE sprite;
  Bullet bullet;
  uint_fast8_t hp = 3;
} Player;

static Player p;

void displayPlayerLife() {
  ssd1306_printFixed_oldStyle(127-6*6, 0, "LIFE:", STYLE_NORMAL);
  char tempStr[6] = {0};
  utoa(p.hp, tempStr, 10);
  ssd1306_printFixed_oldStyle(127-1*6, 0, tempStr, STYLE_NORMAL);
}

void init_player() {
   p.sprite = ssd1306_createSprite(START_POS_X, START_POS_Y, sizeof(playerBMP),  playerBMP); 
   p.sprite.draw();
   displayPlayerLife();
}

void playerDraw() {
  if (p.sprite.x != p.sprite.lx || p.sprite.y != p.sprite.ly) {
    p.sprite.eraseTrace();
    p.sprite.draw();
  }
}

static void playerMove() {
  if (IS_RIGHT_PAD_PRESSED || IS_DOWN_PAD_PRESSED) {
    p.sprite.x += PLAYER_SPEED;
  } else if (IS_LEFT_PAD_PRESSED || IS_UP_PAD_PRESSED) {
    p.sprite.x -= PLAYER_SPEED;
  }
}

static void playerShoot() {
  static unsigned long lastShootTime = 0;
  //static bool cooldownOver = true;
  /*if(!cooldownOver && millis() - lastShootTime >= PLAYER_SHOOT_COOLDOWN) {
    p.sprite = ssd1306_createSprite(p.sprite.x, p.sprite.y, sizeof(playerBMP),  playerBMP);
    p.sprite.draw();
    cooldownOver = true;
  }*/
  if ( IS_A_BUTTON_PRESSED && ((millis() - lastShootTime) >= PLAYER_SHOOT_COOLDOWN) ) {
      lastShootTime = millis();
      p.sprite = ssd1306_createSprite(p.sprite.x, p.sprite.y, sizeof(playerBMP),  playerBMP);
      shoot(&p.bullet, p.sprite.x + 4, p.sprite.y - 4);
      // TODO note(7,4);
      //cooldownOver = false;
    }
  if (IS_B_BUTTON_PRESSED) {
    p.sprite.x = START_POS_X;
    p.sprite.y = START_POS_Y;
  }
}


static bool processCollisionWithInvaders(Bullet *theBullet) {
  for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) { 
      uint_fast8_t x = getPosX(i);
      uint_fast8_t y = getPosY(i);   
      if (!invaders[i].isDead && isColliding(getBulletRect(theBullet), getInvaderRect(x, y))) {
        killInvader(&invaders[i], i);
        compensateDead(); // compensate the loss before redrawing
        drawInvaders(); // draw the invaders before the bullet explosion
        theBullet->sprite.x = x; // To draw the explosion on the invader position
        theBullet->sprite.y = y;
        kill(theBullet);
        return true;
      }
    }
   return false;
}

void playPlayerExplosionSound() {
  /*note(4,1);
  delay(100);
  note(3,1);
  delay(100);
  note(4,1);
  delay(100);
  note(3,1);
  delay(100);
  note(2,1);
  delay(100);
  note(3,1);
  delay(200);
  note(2,1);
  delay(300);
  note(1,1);
  delay(400);
  note(1,1);
  delay(500);
  note(0,0);*/
  //myMelody(snd_PlayerExplosion, 10);
  // TODO melody(snd_PlayerExplosion);
}



void playerLoosesHP() {
  --p.hp;
  playPlayerExplosionSound();
  delay(800);
  if(p.hp == 0) {
   // display game over
   // save score
   // back to start
  } else {
    displayPlayerLife();
    init_player();
  }
}

static bool processCollisionWithPlayer(Bullet *theBullet) {
  Rect playerRect = Rect{p.sprite.x, p.sprite.y, p.sprite.x + 8, p.sprite.y + 8};
  if (isColliding(getBulletRect(theBullet), playerRect)) {
    theBullet->sprite.x = p.sprite.x; // To draw the explosion on the invader position
    theBullet->sprite.y = p.sprite.y;
    kill(theBullet);
    playerLoosesHP();
  }
}


void playerUpdate() {
  processCollisionWithInvaders(&p.bullet);
  if(bulletFast.enabled) {
    processCollisionWithPlayer(&bulletFast);
  }
  playerMove();
  playerShoot();
  bulletUpdate(&p.bullet);
  
}

#endif
