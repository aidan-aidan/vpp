#ifndef VPP
#define VPP



#include <..\include\tools.h>

typedef struct projectile{
	sprite data;
	s32 x;
	s32 y;
	u32 animation;
	u32 enabled;
	u32 angle;
}projectile;

#define PRESSSTARTRED 0x2D7F

void titleScreen(void);
void gameScreen(void);
void railGame(void);
void drawDOS(const char*, u16*, u32, point, u32);



#endif