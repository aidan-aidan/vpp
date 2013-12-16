#include <..\include\vpp.h>
#include <..\include\tools.h>
#include <..\include\palettes.h>
#include <..\include\tilesets.h>
#include <..\include\tilemaps.h>
#include <..\include\text.h>
#include <..\include\sprites.h>

int main(void)
{
	titleScreen();
	//gameScreen();
	railGame();
	
	while(1){}
}

void titleScreen(void)
{
	u32 vBlankBool_A = 0,
		vBlankBool_B = 0,
		vBlankCount = 0,
		time = 0;
	
	DISPCNT = (MODE0 | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE);
	BG0CNT  = (CBB0  | SBB31      | BGCOLOR16  | BG_REG_32X32);
	BG1CNT  = (CBB1  | SBB30      | BGCOLOR256 | BG_REG_32X32);
	BG2CNT  = (CBB0  | SBB29      | BGCOLOR16  | BG_REG_32X32);
	BG3CNT  = (CBB0  | SBB28      | BGCOLOR16  | BG_REG_32X32);
	
	loadBGpalette   (&titleScreenPalette[0]);
	loadBGtiles     (&blank8bppTile[0], TILELENGTH8BPP, CBB1_U32_LOC);
	loadBGtiles     (&titleScreenTiles[0], TITLESCREENTILESLENGTH, CBB1_U32_LOC);
	loadBGmap       (&titleScreenMap[0], BG32X32U32_LENGTH, SBB30_U32_LOC, 0);
	resetBGtilesLoad();
	loadBGtiles     (&dosFontTiles[0], DOSFONTTILESLENGTH, CBB0_U32_LOC);
	
	drawDOS(&pressStart[0], SBB31_U16_LOC, PRESSSTARTLENGTH, pressStartPos, PALETTE15);
	
	while(1)
	{
		vBlankBool_A = (DISPSTAT & VBLANKFLAG);
		
		if(vBlankBool_A & ~vBlankBool_B)
		{
			keyPoll();
			
			vBlankCount++;
			
			if(keyPress(BUTTON_START))
			{
				setSeed(time);
				resetBGtilesLoad();
				resetBGmap(SBB31_U32_LOC, BG32X32U32_LENGTH);
				return;
			}
			
			if(vBlankCount == 30)
			{
				setBGswatch(1, 15, PRESSSTARTRED);
			}
			if(vBlankCount > 59)
			{
				vBlankCount = 0;
				setBGswatch(1, 15, FONTCOLOR);
			}
		}
		
		time++;
		vBlankBool_B = vBlankBool_A;
	}
}

void gameScreen(void)
{
	u32 i,
		vBlankBool_A = 0,
		vBlankBool_B = 0;
	s32	shipAngle    = 0;
	
	point starOffset       = {0, 0},
	      playerPos        = {104, 48},
		  shipAcceleration = {0, 0};
		  
	sprite playerShip = {&OAMLOC[0],
						 &OAMLOC[1],
						 &OAMLOC[2]};
						 
	*playerShip.attribute0 = (SHIPATTRIBUTE0 | playerPos.y);
	*playerShip.attribute1 = (SHIPATTRIBUTE1 | playerPos.x);
	*playerShip.attribute2 = (SHIPATTRIBUTE2);
	
	OAMLOC[3] = OAMLOC[15] = 256;
	OAMLOC[7] = OAMLOC[11] = 0;
		
	DISPCNT = (MODE0 | OBJ1D | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE | BG3_ENABLE | OBJ_ENABLE);
	
	BG0CNT  = (CBB0  | SBB31      | BGCOLOR16  | BG_REG_32X32);
	BG1CNT  = (CBB1  | SBB27      | BGCOLOR16  | BG_REG_64X64);
	BG2CNT  = (CBB1  | SBB23      | BGCOLOR16  | BG_REG_64X64);
	BG3CNT  = (CBB1  | SBB19      | BGCOLOR16  | BG_REG_64X64);
	
	loadBGpalette   (&gameScreenBGpalette[0]);
	loadBGtiles     (&blank4bppTile[0], TILELENGTH4BPP, CBB1_U32_LOC);
	loadBGtiles     (&starTiles[0], STARTILESLENGTH, CBB1_U32_LOC);
	resetBGtilesLoad();
	loadBGtiles     (&dosFontTiles[0], DOSFONTTILESLENGTH, CBB0_U32_LOC);
	loadOBJpalette  (&gameScreenOBJpalette[0]);
	loadOBJtiles    (&blank8bppTile[0], TILELENGTH8BPP);
	loadOBJtiles    (&shipTiles[0], SHIPTILESLENGTH);
	
	for(i = 0; i < BG64X64U32_LENGTH; i++)
	{
		if((r() >> 25) < 20)
		{
			SBB19_U32_LOC[i] = (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) | (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) << 16));
		}
		else
		{
			SBB19_U32_LOC[i] = 0;
		}
		if((r() >> 25) < 20)
		{
			SBB23_U32_LOC[i] = (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) | (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) << 16));
		}
		else
		{
			SBB23_U32_LOC[i] = 0;
		}
		if((r() >> 25) < 20)
		{
			SBB27_U32_LOC[i] = (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) | (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) << 16));
		}
		else
		{
			SBB27_U32_LOC[i] = 0;
		}
	}
	
	while(1)
	{
		vBlankBool_A = (DISPSTAT & VBLANKFLAG);
		
		if(vBlankBool_A & ~vBlankBool_B)
		{
			keyPoll();
			
			if(keyDown(BUTTON_B))
			{
				shipAcceleration.x += sine[shipAngle];
				shipAcceleration.y += -cosine[shipAngle];
			}
			if(keyDown(BUTTON_A))
			{
				shipAcceleration.x >>= 1;
				shipAcceleration.y >>= 1;
			}
			if(keyDown(BUTTON_L))
			{
				shipAngle -= 15;
			}
			if(keyDown(BUTTON_R))
			{
				shipAngle += 15;
			}
			
			if(shipAngle > CIRCLE_DIVISION - 1)
			{
				shipAngle = 0;
			}
			if(shipAngle < 0)
			{
				shipAngle = CIRCLE_DIVISION - 1;
			}
			
			if(shipAcceleration.x > 32768)
			{
				shipAcceleration.x = 32768;
			}
			if(shipAcceleration.y > 32768)
			{
				shipAcceleration.y = 32768;
			}
			if(shipAcceleration.x < -32768)
			{
				shipAcceleration.x = -32768;
			}
			if(shipAcceleration.y < -32768)
			{
				shipAcceleration.y = -32768;
			}
			
			playerPos.x = starOffset.x >> 8;
			playerPos.y = starOffset.y >> 8;
			
			starOffset.x += shipAcceleration.x;
			starOffset.y += shipAcceleration.y;
			
			OAMLOC[3]  = OAMLOC[15] = cosine[shipAngle];
			OAMLOC[7]  = sine[shipAngle];
			OAMLOC[11] = -sine[shipAngle];
			
			BG1HOFS = starOffset.x >> 13;
			BG2HOFS = starOffset.x >> 14;
			BG3HOFS = starOffset.x >> 15;
			BG1VOFS = starOffset.y >> 13;
			BG2VOFS = starOffset.y >> 14;
			BG3VOFS = starOffset.y >> 15;
		}
		
		vBlankBool_B = vBlankBool_A;
	}
}

void railGame(void)
{
	u32 i,
		vBlankBool_A = 0,
		vBlankBool_B = 0,
		earthAngle = 0,
		gunAngle = 512;
	
	s32 earthPA = 0,
		earthPB = 0,
		earthPC = 0,
		earthPD = 0;
	
	point earthRotationTex = {256, 256},
		  earthRotationScr = {120, 256};
		  
	affSprite gun = {&OAMLOC[120], &OAMLOC[121], &OAMLOC[122], &OAMLOC[3], &OAMLOC[7], &OAMLOC[11], &OAMLOC[15]};
	*gun.attribute0   	= GUNATTRIBUTE0;
	*gun.attribute1   	= GUNATTRIBUTE1;
	*gun.attribute2  	= GUNATTRIBUTE2;
	*gun.pa = *gun.pd 	= 256;
	*gun.pb = *gun.pc	= 0;
	
	projectile projectiles[30];
	for(i = 0; i < 30; i++)
	{
		projectiles[i].data.attribute0 = &OAMLOC[i * 4];
		projectiles[i].data.attribute1 = &OAMLOC[i * 4 + 1];
		projectiles[i].data.attribute2 = &OAMLOC[i * 4 + 2];
		
		*projectiles[i].data.attribute0 = PROJECTILEATTRIBUTE0;
		*projectiles[i].data.attribute1 = PROJECTILEATTRIBUTE1;
		*projectiles[i].data.attribute2 = PROJECTILEATTRIBUTE2;
	}
	
	BG2PA = BG2PD = 255;
	BG2PB = BG2PC = 0;
	
	BG2X = 0;
	BG2Y = 0;
	
	loadBGpalette(&railGameBGpalette[0]);
	loadOBJpalette(&railGameOBJpalette[0]);
	loadBGtiles(&earthTiles[0], EARTHTILESLENGTH, CBB0_U32_LOC);
	loadOBJtiles(&blank4bppTile[0], TILELENGTH4BPP);
	loadOBJtiles(&gunTiles[0], GUNTILESLENGTH);
	loadOBJtiles(&projectileTiles[0], PROJECTILETILESLENGTH);
	loadBGmap(&earthMap[0], AFF64X64U32_LENGTH, SBB27_U32_LOC, PALETTE0);
	
	DISPCNT = (MODE1 | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE | OBJ_ENABLE | OBJ1D);
	BG0CNT  = (CBB2 | SBB31 | BG_REG_32X32 | BGCOLOR16);
	BG1CNT  = (CBB1 | SBB29 | BG_REG_64X32 | BGCOLOR16);
	BG2CNT  = (CBB0 | SBB27 | BG_AFF_64X64 | BGCOLOR256);
		
	while(1)
	{
		vBlankBool_A = (DISPSTAT & VBLANKFLAG);
		
		if(vBlankBool_A & ~vBlankBool_B)
		{
			keyPoll();
			
			earthAngle++;
			if(earthAngle > CIRCLE_DIVISION - 1)
			{
				earthAngle = 0;
			}
			
			if(keyDown(BUTTON_L))
			{
				gunAngle += 3;
			}
			if(keyDown(BUTTON_R))
			{
				gunAngle -= 3;
			}
			if(gunAngle > 716)
			{
				gunAngle = 716;
			}
			if(gunAngle < 308)
			{
				gunAngle = 308;
			}
			
			*gun.pa = *gun.pd = sine[gunAngle];
			*gun.pb = cosine[gunAngle];
			*gun.pc = -cosine[gunAngle];
			
			*gun.attribute0 = GUNATTRIBUTE0 | (((-sine[gunAngle] * 142) >> 8) + 240);
			*gun.attribute1 = GUNATTRIBUTE1 | (((cosine[gunAngle] * 142) >> 8) + 104);
			
			earthPA = earthPD = cosine[earthAngle];
			earthPB = -sine[earthAngle];
			earthPC = sine[earthAngle];
			
			BG2X = (earthRotationTex.x << 8) - (earthPA * earthRotationScr.x + earthPB * earthRotationScr.y);
			BG2Y = (earthRotationTex.y << 8) - (earthPC * earthRotationScr.x + earthPD * earthRotationScr.y);
			
			BG2PA = earthPA;
			BG2PB = earthPB;
			BG2PC = earthPC;
			BG2PD = earthPD;
		}
		
		vBlankBool_B = vBlankBool_A;
	}
}

void drawDOS(const char* string, u16* SBB, u32 length, point location, u32 palette)
{
	u32 i;
	
	for(i = 0; i < length; i++)
	{
		SBB[location.y * 32 + location.x + i] = (string[i] - 32) | palette;
		SBB[location.y * 32 + location.x + i + 32] = (string[i] - 32 + 95) | palette;
	}
}