#include "input.h"

/**
Globals
*/

char padBuf1[256] __attribute__((aligned(64)));
char padBuf2[256] __attribute__((aligned(64)));

char actAlign[6];
int actuators;

int input_player_mode = 0; //0 = 1 player, 1 = 2 player

struct padButtonStatus buttons_player_one;
struct padButtonStatus buttons_player_two;

u32 paddata1;
u32 newpad1;
u32 oldpad1;

u32 paddata2;
u32 newpad2;
u32 oldpad2;

/**
End Globals
*/

/*
 * loadModules()
 */
static void
loadModules(void)
{
    int ret;


    ret = SifLoadModule("rom0:SIO2MAN", 0, NULL);
    if (ret < 0) {
        printf("sifLoadModule sio failed: %d\n", ret);
        SleepThread();
    }

    ret = SifLoadModule("rom0:PADMAN", 0, NULL);
    if (ret < 0) {
        printf("sifLoadModule pad failed: %d\n", ret);
        SleepThread();
    }
}

/*
 * waitPadReady()
 */
static int waitPadReady(int port, int slot)
{
    int state;
    int lastState;
    char stateString[16];

    state = padGetState(port, slot);
    lastState = -1;
    while((state != PAD_STATE_STABLE) && (state != PAD_STATE_FINDCTP1)) {
        if (state != lastState) {
            padStateInt2String(state, stateString);
            printf("Please wait, pad(%d,%d) is in state %s\n",
                       port, slot, stateString);
        }
        lastState = state;
        state=padGetState(port, slot);
    }
    // Were the pad ever 'out of sync'?
    if (lastState != -1) {
        printf("Pad OK!\n");
    }
    return 0;
}


/*
 * initializePad()
 */
static int
initializePad(int port, int slot)
{

    int ret;
    int modes;
    int i;

    waitPadReady(port, slot);

    // How many different modes can this device operate in?
    // i.e. get # entrys in the modetable
    modes = padInfoMode(port, slot, PAD_MODETABLE, -1);
    printf("The device has %d modes\n", modes);

    if (modes > 0) {
        printf("( ");
        for (i = 0; i < modes; i++) {
            printf("%d ", padInfoMode(port, slot, PAD_MODETABLE, i));
        }
        printf(")");
    }

    printf("It is currently using mode %d\n",
               padInfoMode(port, slot, PAD_MODECURID, 0));

    // If modes == 0, this is not a Dual shock controller
    // (it has no actuator engines)
    if (modes == 0) {
        printf("This is a digital controller?\n");
        return 1;
    }

    // Verify that the controller has a DUAL SHOCK mode
    i = 0;
    do {
        if (padInfoMode(port, slot, PAD_MODETABLE, i) == PAD_TYPE_DUALSHOCK)
            break;
        i++;
    } while (i < modes);
    if (i >= modes) {
        printf("This is no Dual Shock controller\n");
        return 1;
    }

    // If ExId != 0x0 => This controller has actuator engines
    // This check should always pass if the Dual Shock test above passed
    ret = padInfoMode(port, slot, PAD_MODECUREXID, 0);
    if (ret == 0) {
        printf("This is no Dual Shock controller??\n");
        return 1;
    }

    printf("Enabling dual shock functions\n");

    // When using MMODE_LOCK, user cant change mode with Select button
    padSetMainMode(port, slot, PAD_MMODE_DUALSHOCK, PAD_MMODE_LOCK);

    waitPadReady(port, slot);
    printf("infoPressMode: %d\n", padInfoPressMode(port, slot));

    waitPadReady(port, slot);
    printf("enterPressMode: %d\n", padEnterPressMode(port, slot));

    waitPadReady(port, slot);
    actuators = padInfoAct(port, slot, -1, 0);
    printf("# of actuators: %d\n",actuators);

    if (actuators != 0) {
        actAlign[0] = 0;   // Enable small engine
        actAlign[1] = 1;   // Enable big engine
        actAlign[2] = 0xff;
        actAlign[3] = 0xff;
        actAlign[4] = 0xff;
        actAlign[5] = 0xff;

        waitPadReady(port, slot);
        printf("padSetActAlign: %d\n",
                   padSetActAlign(port, slot, actAlign));
    }
    else {
        printf("Did not find any actuators.\n");
    }

    waitPadReady(port, slot);

    return 1;
}

void input_initialize()
{
	int ret;

	SifInitRpc(0); //init the rpc

	loadModules(); //load the modules for input

	padInit(0); //init the pad modules
	if(input_player_mode == 1)
	{
		printf("2 player mode\n");
		padInit(1);
	}

	/*
	Player 1
	*/
	if((ret = padPortOpen(0, 0, padBuf1)) == 0) 
	{
        printf("p1 padOpenPort failed: %d\n", ret);
        SleepThread();
    }

    if(!initializePad(0, 0)) 
    {
        printf("p1 pad initalization failed!\n");
        SleepThread();
    }
    /*
	End Player 1
	*/

	/*
	Player 2
	*/
    if(input_player_mode == 1) //only if 2 player supported
    {
    	printf("2 player mode\n");
    	if((ret = padPortOpen(1, 0, padBuf2)) == 0)
    	{
    		printf("p2 padOpenPort failed: %d\n", ret);
    		SleepThread();
    	}
    	else
    		printf("p2 opened fine\n");

    	if(!initializePad(1, 0))
    	{
    		printf("p2 pad initalization failed!\n");
    		SleepThread();
    	}
    	else
    		printf("p2 initialized fine\n");
    }
	/*
	End Player 2
	*/
}

void input_update(int port)
{
	int i = 0;
	int slot = 0;
	int ret = padGetState(port, 0);

	while((ret != PAD_STATE_STABLE) && (ret != PAD_STATE_FINDCTP1)) 
	{
        if(ret==PAD_STATE_DISCONN) 
        {
            printf("Pad(%d, %d) is disconnected\n", port, slot);
        }
        ret = padGetState(port, slot);
    }
    if(i==1) 
    {
    	printf("Pad: OK!\n");
    }

    if(port == 0)
    	ret = padRead(port, slot, &(buttons_player_one));
    else
    	ret = padRead(port, slot, &(buttons_player_two));
    if(ret != 0)
    {//TODO ?
    }
}

int input_is_button_down(int port, u16 button)
{
	if(port == 0) //p1
	{
		paddata1 = 0xffff ^ (buttons_player_one.btns);
		newpad1 = paddata1 & ~oldpad1;
		oldpad1 = paddata1;

		if(newpad1 & button)
		{
			printf("p1 pressed\n");
			return 1;
		}
	}
	else if(port == 1) //p2 
	{
		paddata2 = 0xffff ^ (buttons_player_two.btns);
		newpad2 = paddata2 & ~oldpad2;
		oldpad2 = paddata2;

		if(newpad2 & button)
		{
			printf("p2 pressed");
			return 1;
		}
	}

	return 0;
}
