#include "lumber_game.h"

#include "../input.h"
#include "log.h"

/**
Globals
*/

sprite_t* branch_left;
sprite_t* branch_right;
sprite_t* log;

log_t p1_log[2];

float p1_log_y = 0;

/**
End Globals
*/

/**
Private Functions
*/

void lumber_draw_p1(); //draw p1 and his/her tree
void lumber_draw_p2(); //draw p2 and his/her tree

/**
End Private Functions
*/

lumber_game_t lumber_game_create()
{
	lumber_game_t game;

	game.p1_score = 0;
	game.p2_score = 0;

	if(branch_left == NULL)
	{
		branch_left = sprite_create("branch_left.png");
	}
	if(branch_right == NULL)
	{
		branch_right = sprite_create("branch_right.png");
	}
	if(log == NULL)
	{
		log = sprite_create("log.png");
	}

	//init input
	input_player_mode = 1;
	input_initialize(INPUT_TWO_PLAYER);
	//end init input

	//set log positions
	p1_log[0].y = (0 - log->texture.Height);
	p1_log[1].y = 0;

	p1_log[0].x = (120 - log->texture.Width);
	p1_log[1].x = (120 - log->texture.Width);
	//end set log positions

	return game;
}

void lumber_draw_p1()
{
	int i = 0;
	for(i = 0; i < 2; i++)
	{
		sprite_draw(log, p1_log[i].x, p1_log[i].y);
	}
}

void lumber_draw(lumber_game_t* game)
{
	gsKit_clear(gsGlobal, GS_SETREG_RGBAQ(0x87,0xCE,0xEB,0x00,0x00)); //sky blue

	lumber_draw_p1();

	flip_screen();
}

void lumber_update(lumber_game_t* game)
{
	input_update(0); //player one
	input_update(1); //player two

	int i = 0;
	for(i = 0; i < 2; i++)
	{
		log_update(&(p1_log[i]));
	}
}