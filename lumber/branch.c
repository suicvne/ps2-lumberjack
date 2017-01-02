#include "branch.h"

void branch_update(branch_t* branch)
{
	branch->y += LOG_SPEED;
	if(branch->y > ScreenHeight)
	{
		//TODO: move to top, select new side
	}
}

void branch_draw(branch_t* branch, sprite_t* sprite)
{
	if(branch->player == P1)
	{
		float x = (branch->side == LEFT) ? P1_BRANCH_LEFT : P1_BRANCH_RIGHT;
		sprite_draw(sprite, x, branch->y);
	}
	if(branch->player == P2)
	{
		float x = (branch->side == LEFT) ? P2_BRANCH_LEFT : P2_BRANCH_RIGHT;
		sprite_draw(sprite, x, branch->y);
	}
}