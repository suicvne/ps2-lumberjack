#ifndef _BRANCH_H_
#define _BRANCH_H_

#include "log.h" //for LOG_SPEED
#include "lumber_game.h" //for the sprites
#include "../sprite.h"

#define P1_BRANCH_LEFT 0
#define P1_BRANCH_RIGHT 120

#define P2_BRANCH_LEFT 0
#define P2_BRANCH_RIGHT 0

typedef enum branch_side {

	LEFT,
	RIGHT

} branch_side;

typedef enum branch_player {
	P1,
	P2
} branch_player;

typedef struct branch_t {

	float x;
	float y; //should move in conjunction with LOG_SPEED
	branch_side side;
	branch_player player;

} branch_t;

void branch_update(branch_t* branch);
void branch_draw(branch_t* branch, sprite_t* sprite);

#endif //_BRANCH_H_