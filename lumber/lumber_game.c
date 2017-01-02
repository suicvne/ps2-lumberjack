#include "lumber_game.h"

#include "../input.h"
#include "log.h"
#include "branch.h"

/**
Globals
*/

sprite_t* branch_left;
sprite_t* branch_right;
sprite_t* log;

#define LOG_COUNT 2
log_t p1_log[LOG_COUNT];

#define MAX_BRANCHES 6
branch_t p1_branches[MAX_BRANCHES];

float p1_log_y = 0;



/**
End Globals
*/

/**
Private Functions
*/

void lumber_draw_p1(); //draw p1 and his/her tree
void lumber_draw_p2(); //draw p2 and his/her tree

void init_branches();

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
	//input_player_mode = INPUT_TWO_PLAYER;
	input_player_mode = INPUT_SINGLE_PLAYER;
	input_initialize();
	//end init input

	//set log positions
	
	p1_log[0].y = (0 - log->texture.Height);
	p1_log[1].y = 0;
	//p1_log[2].y = 0 + log->texture.Height;

	p1_log[0].x = (120 - log->texture.Width);
	p1_log[1].x = (120 - log->texture.Width);
	//p1_log[2].x = (120 - log->texture.Width);
	
	//end set log positions

	init_branches();

	return game;
}

void init_branches()
{
	int i;
	for(i = 0; i < MAX_BRANCHES; i++)
	{
		//TODO: set various positions 
		p1_branches[i].side = RIGHT;
		p1_branches[i].player = P1;
	}
}

void lumber_draw_p1()
{
	int i = 0;
	for(i = 0; i < LOG_COUNT; i++)
	{
		sprite_draw(log, p1_log[i].x, p1_log[i].y);
	}

	for(i = 0; i < MAX_BRANCHES; i++)
	{
		sprite_t* sprite = (p1_branches[i].side == LEFT) ? branch_left : branch_right;
		branch_draw(&p1_branches[i], sprite);
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
	for(i = 0; i < LOG_COUNT; i++)
	{
		log_update(&(p1_log[i]));
	}

	for(i = 0; i < MAX_BRANCHES; i++)
	{
		branch_update(&(p1_branches[i]));
	}
}