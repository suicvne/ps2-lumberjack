#ifndef _INPUT_H_
#define _INPUT_H_

#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include "libpad.h"

typedef struct input_t {

	u32 pad_data;
	u32 old_pad;
	u32 new_pad;
	struct padButtonStatus sce_buttons;

} input_t;

#define INPUT_SINGLE_PLAYER 0
#define INPUT_TWO_PLAYER 1

input_t input_player_one;
input_t input_player_two;

extern char padBuf1[256] __attribute__((aligned(64)));
extern char padBuf2[256] __attribute__((aligned(64)));

extern char actAlign[6];
extern int actuators;

extern int input_player_mode; //0 = 1 player, 1 = 2 player

extern struct padButtonStatus buttons_player_one;
extern struct padButtonStatus buttons_player_two;

extern u32 paddata1;
extern u32 newpad1;
extern u32 oldpad1;

extern u32 paddata2;
extern u32 newpad2;
extern u32 oldpad2;

void input_initialize();

void input_update(int port); //0 = player 1, 1 = player 2

int input_is_button_down(int port, u16 button);

#endif //_INPUT_H_
