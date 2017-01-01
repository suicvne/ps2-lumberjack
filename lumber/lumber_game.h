#ifndef _LUMBER_GAME_H_
#define _LUMBER_GAME_H_

#include <gsKit.h>
#include <gsToolkit.h>
#include "../sprite.h"
#include "../globals.h"

typedef struct lumber_game_t {

	int p1_score;
	int p2_score;

} lumber_game_t;

extern sprite_t* branch_left;
extern sprite_t* branch_right;
extern sprite_t* log;

lumber_game_t lumber_game_create();

void lumber_draw(lumber_game_t* game);
void lumber_update(lumber_game_t* game);

#endif //_LUMBER_GAME_H_