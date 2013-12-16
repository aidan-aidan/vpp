#ifndef SPRITES
#define SPRITES



#include <..\include\tools.h>


#define SHIPTILESLENGTH 128
#define SHIPATTRIBUTE0 0xA300
#define SHIPATTRIBUTE1 0x8000
#define SHIPATTRIBUTE2 0x0002
extern const u32 shipTiles[SHIPTILESLENGTH];

#define GUNTILESLENGTH 128
#define GUNATTRIBUTE0 0x0100
#define GUNATTRIBUTE1 0x8000
#define GUNATTRIBUTE2 0x0001
extern const u32 gunTiles[GUNTILESLENGTH];

#define PROJECTILETILESLENGTH 32
#define PROJECTILEATTRIBUTE0 0x0000
#define PROJECTILEATTRIBUTE1 0x0000
#define PROJECTILEATTRIBUTE2 0x1011
extern const u32 projectileTiles[PROJECTILETILESLENGTH];



#endif