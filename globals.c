#include "globals.h"

GSGLOBAL* gsGlobal;

u64 TextureColor = GS_SETREG_RGBAQ(0x80,0x80,0x80,0x80,0x00);
u64 White = GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x00,0x00);

float ScreenWidth = 0.0f;
float ScreenHeight = 0.0f;

void initialize_gskit()
{
	gsGlobal = gsKit_init_global();
	gsKit_init_screen(gsGlobal);

	gsGlobal->PSM = GS_PSM_CT32;
	gsGlobal->PSMZ = GS_PSMZ_16S;
	gsGlobal->ZBuffering = GS_SETTING_ON;

	dmaKit_init(D_CTRL_RELE_OFF,D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
		    D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);

	// Initialize the DMAC
	dmaKit_chan_init(DMA_CHANNEL_GIF);

	gsGlobal->PrimAlphaEnable = GS_SETTING_ON;

	ScreenWidth = gsGlobal->Width;
	ScreenHeight = gsGlobal->Height;
}

void flip_screen()
{
	gsKit_sync_flip(gsGlobal);
	gsKit_queue_exec(gsGlobal);
	gsKit_queue_reset(gsGlobal->Per_Queue);
}