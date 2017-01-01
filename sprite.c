#include "sprite.h"
#include "globals.h"
#include <stdio.h>

sprite_t* sprite_create(const char* path)
{
	sprite_t* sprite = malloc(sizeof(sprite_t));

	gsKit_texture_png(gsGlobal, &(sprite->texture), path);

	return sprite;	
}

void sprite_destroy(sprite_t* sprite)
{
	free(sprite); //TODO: this
}

void sprite_draw(sprite_t* sprite, float x, float y)
{
	GSTEXTURE* text = &(sprite->texture);
	gsKit_prim_sprite_texture(gsGlobal, text,	x,  // X1
							y,  // Y2
							0.0f,  // U1
							0.0f,  // V1
							x + sprite->texture.Width, // X2
							y + sprite->texture.Height, // Y2
							sprite->texture.Width, // U2
							sprite->texture.Height, // V2
							2,
							TextureColor);
}
