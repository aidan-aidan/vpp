#ifndef VPP
#define VPP



#include <..\include\tools.h>

typedef struct projectile{
	sprite data;
	u32 angle;
}projectile;

#define PRESSSTARTRED 	0x2D7F
#define MAXGUNANGLE		716
#define MINGUNANGLE		308

void titleScreen(void);
void gameScreen(void);
void railGame(void);
void drawDOS(const char*, u16*, u32, point, u32);



#endif