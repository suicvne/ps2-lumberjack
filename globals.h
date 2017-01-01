#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>


extern GSGLOBAL* gsGlobal;
extern u64 TextureColor;
extern u64 White;

extern float ScreenWidth;
extern float ScreenHeight;

void initialize_gskit();
void flip_screen();

#endif //_GLOBAL_H_
