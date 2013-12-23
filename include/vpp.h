#ifndef VPP
#define VPP



#include <..\include\tools.h>

typedef struct projectile{
	u16*	attribute0;
	u16*	attribute1;
	u16*	attribute2;
	circle	definition;
	u32		enabled;
	u32 	angle;
}projectile;

#define PRESSSTARTRED 	0x2D7F
#define MAXGUNANGLE		716
#define MINGUNANGLE		308

void titleScreen	(void);
void gameScreen		(void);
void railGame		(void);
void spriteFlash	(sprite*);
void spriteNormal	(sprite*);
void drawDOS		(const char*, u16*, u32, point, u32);



#endif