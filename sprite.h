#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <gsKit.h>
#include <gsToolkit.h>

typedef struct sprite_t {

	GSTEXTURE texture;

} sprite_t;

sprite_t* sprite_create(const char* path);
void sprite_destroy(sprite_t* sprite);

void sprite_draw(sprite_t* sprite, float x, float y);

#endif //_SPRITE_H_
