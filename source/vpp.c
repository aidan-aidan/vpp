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
	
	DISPCNT = (MODE0 | BG0_ENABLE | BG1_ENABLE);
	BG0CNT  = (CBB0  | SBB31      | BGCOLOR16  | BG_REG_32X32);
	BG1CNT  = (CBB1  | SBB30      | BGCOLOR256 | BG_REG_32X32);
	
	loadBGpalette   (&titleScreenPalette[0]);
	loadBGtiles     (&blank8bppTile[0], CBB1_U32_LOC);
	loadBGtiles     (&titleScreenTiles[0], CBB1_U32_LOC);
	loadBGmap       (&titleScreenMap[0], SBB30_U32_LOC, 0);
	resetBGtilesLoad();
	loadBGtiles     (&dosFontTiles[0], CBB0_U32_LOC);
	
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
				resetBGmap(SBB30_U32_LOC, BG64X32U32_LENGTH);
				return;
			}
			
			if(vBlankCount == 29)
			{
				setBGswatch(1, 15, PRESSSTARTRED);
			}
			if(vBlankCount > 59)
			{
				vBlankCount = 0;
				setBGswatch(1, 15, DOSFONTCOLOR);
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
						 
	*playerShip.attribute0 = (shipTiles[1] | playerPos.y);
	*playerShip.attribute1 = (shipTiles[2] | playerPos.x);
	*playerShip.attribute2 = (shipTiles[3]);
	
	OAMLOC[3] = OAMLOC[15] = 256;
	OAMLOC[7] = OAMLOC[11] = 0;
		
	DISPCNT = (MODE0 | OBJ1D | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE | BG3_ENABLE | OBJ_ENABLE);
	
	BG0CNT  = (CBB0  | SBB31      | BGCOLOR16  | BG_REG_32X32);
	BG1CNT  = (CBB1  | SBB27      | BGCOLOR16  | BG_REG_64X64);
	BG2CNT  = (CBB1  | SBB23      | BGCOLOR16  | BG_REG_64X64);
	BG3CNT  = (CBB1  | SBB19      | BGCOLOR16  | BG_REG_64X64);
	
	loadBGpalette   (&gameScreenBGpalette[0]);
	loadBGtiles     (&blank4bppTile[0], CBB1_U32_LOC);
	loadBGtiles     (&starTiles[0], CBB1_U32_LOC);
	resetBGtilesLoad();
	loadBGtiles     (&dosFontTiles[0], CBB0_U32_LOC);
	loadOBJpalette  (&gameScreenOBJpalette[0]);
	loadOBJtiles    (&blank8bppSprite[0]);
	loadOBJtiles    (&shipTiles[0]);
	
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
		vBlankBool_A 			= 0,
		vBlankBool_B 			= 0,
		vBlankCount 			= 0,
		projectileIndex 		= 0,
		playerProjectileSpeed	= 2,
		maxPlayerShots  		= 20,
		gunAltitude				= 135,
		gunSpeed 				= 4,
		starXoffset				= 0;
		
	point 		offscreen	= {255 << 8, 255 << 8};
		
	affSprite  	gun    		= {&OAMLOC[80], &OAMLOC[81], &OAMLOC[82], &OAMLOC[3], &OAMLOC[7], &OAMLOC[11], &OAMLOC[15], 256, 0, 0, 256, 512, {{(255 << 8), (255 << 8)}, gunTiles[SPRITEWIDTH] >> 1}, 1};
	
	sprite		target		= {&OAMLOC[84], &OAMLOC[85], &OAMLOC[86], {{32 << 8, 32 << 8}, 16}, 1};
	
	affBG      	earth		= {&BG2PA, &BG2PB, &BG2PC, &BG2PD, &BG2X, &BG2Y, &BG2CNT, 256, 0, 0, 256, 0, {120, 256}, {256, 256}};
	
	circle     	earthBound 	= {earth.screenLocation, 128};
	
	projectile	playerProjectiles[maxPlayerShots];
	
	*gun.attribute0   		= gunTiles[ATTRIBUTE0];
	*gun.attribute1   		= gunTiles[ATTRIBUTE1] | AFFPARAM0;
	*gun.attribute2  		= gunTiles[ATTRIBUTE2];
	*gun.pa = *gun.pd 		= gun.paD;
	*gun.pb = *gun.pc 		= gun.pbD;
	
	*target.attribute0		= circleTiles[ATTRIBUTE0] | ((target.definition.location.y >> 8) - spriteCenterY(&circleTiles[0]));
	*target.attribute1		= circleTiles[ATTRIBUTE1] | ((target.definition.location.x >> 8) - spriteCenterX(&circleTiles[0]));
	*target.attribute2		= circleTiles[ATTRIBUTE2];
	
	*earth.pa = *earth.pd 	= earth.paD;
	*earth.pb = *earth.pc 	= earth.pbD;
	*earth.dx = *earth.dy 	= 255 << 8;
	
	for(i = 0; i < maxPlayerShots; i++)
	{
		playerProjectiles[i].data.attribute0 				= &OAMLOC[i * 4];
		playerProjectiles[i].data.attribute1 				= &OAMLOC[i * 4 + 1];
		playerProjectiles[i].data.attribute2 				= &OAMLOC[i * 4 + 2];
		
		playerProjectiles[i].data.definition.location.x	= 255 << 8;
		playerProjectiles[i].data.definition.location.y 	= 255 << 8;
		
		*playerProjectiles[i].data.attribute0				= projectileTiles[ATTRIBUTE0] | ((playerProjectiles[i].data.definition.location.y >> 8) - spriteCenterY(&projectileTiles[0]));
		*playerProjectiles[i].data.attribute1				= projectileTiles[ATTRIBUTE1] | ((playerProjectiles[i].data.definition.location.x >> 8) - spriteCenterX(&projectileTiles[0]));
		*playerProjectiles[i].data.attribute2				= projectileTiles[ATTRIBUTE2];
	}
	
	loadBGpalette	(railGameBGpalette);
	loadBGtiles		(earthTiles, 	CBB0_U32_LOC);
	resetBGtilesLoad();
	loadBGtiles     (blank4bppTile,	CBB1_U32_LOC);
	loadBGtiles     (starTiles, 	CBB1_U32_LOC);
	loadBGmap		(earthMap, SBB27_U32_LOC, PALETTE0);
	
	loadOBJpalette	(railGameOBJpalette	);
	loadOBJtiles	(blank4bppSprite	);
	loadOBJtiles	(gunTiles			);
	loadOBJtiles	(projectileTiles	);
	loadOBJtiles	(circleTiles		);
	
	for(i = 0; i < BG64X32U32_LENGTH; i++)
	{
		if(r() >> 25 < 32)
		{
			SBB29_U32_LOC[i] = ((r() >> 27) | ((r() >> 30) << 10) | PALETTE1) | (((r() >> 27) | ((r() >> 30) << 10) | PALETTE1) << 16);
		}
	}
	
	DISPCNT		= 	(MODE1 | BG0_ENABLE	| BG1_ENABLE   | BG2_ENABLE | OBJ_ENABLE | OBJ1D);
	BG0CNT  	= 	(CBB2  | SBB31 		| BG_REG_32X32 | BGCOLOR16  | BGPRIORITY0);
	BG1CNT  	= 	(CBB1  | SBB29 		| BG_REG_64X32 | BGCOLOR16  | BGPRIORITY2);
	*earth.cnt	= 	(CBB0  | SBB27 		| BG_AFF_64X64 | BGCOLOR256 | BGPRIORITY1);
		
	while(1)
	{
		vBlankBool_A = (DISPSTAT & VBLANKFLAG);
		
		if(vBlankBool_A & ~vBlankBool_B)
		{
			keyPoll();
			
			if(keyDown(BUTTON_A) && (vBlankCount & 2) && (vBlankCount & 1))
			{
				playerProjectiles[projectileIndex].angle 						= gun.angle + ((r() >> 27) - 16);
				playerProjectiles[projectileIndex].data.enabled 				= 1;
				playerProjectiles[projectileIndex].data.definition.location.x 	= (cosine[playerProjectiles[projectileIndex].angle] * gunAltitude) + ((earth.screenLocation.x) << 8);
				playerProjectiles[projectileIndex].data.definition.location.y 	= (-sine[playerProjectiles[projectileIndex].angle] * gunAltitude) + (earth.screenLocation.y << 8);
				
				*playerProjectiles[projectileIndex].data.attribute0				= projectileTiles[ATTRIBUTE0] | ((playerProjectiles[projectileIndex].data.definition.location.y >> 8) - spriteCenterY(&projectileTiles[0]));
				*playerProjectiles[projectileIndex].data.attribute1				= projectileTiles[ATTRIBUTE1] | ((playerProjectiles[projectileIndex].data.definition.location.x >> 8) - spriteCenterX(&projectileTiles[0]));
				
				projectileIndex++;
				if(projectileIndex >= maxPlayerShots)
				{
					projectileIndex = 0;
				}
			}
			
			if(keyDown(BUTTON_L))		gun.angle += 	gunSpeed;
			if(keyDown(BUTTON_R))		gun.angle -= 	gunSpeed;
			if(gun.angle > MAXGUNANGLE)	gun.angle = 	MAXGUNANGLE;
			if(gun.angle < MINGUNANGLE)	gun.angle = 	MINGUNANGLE;
			
			earth.angle++;
			if(earth.angle >= CIRCLE_DIVISION)earth.angle = 0;
			
			vBlankCount++;
			
			for(i = 0; i < maxPlayerShots; i++)
			{
				if(playerProjectiles[i].data.enabled)
				{
					playerProjectiles[i].data.definition.location.y -= sine  [playerProjectiles[i].angle] * playerProjectileSpeed;
					playerProjectiles[i].data.definition.location.x += cosine[playerProjectiles[i].angle] * playerProjectileSpeed;
					
					if(playerProjectiles[i].data.definition.location.x - (spriteCenterX(&projectileTiles[0]) << 8) < 0)
					playerProjectiles[i].data.definition.location.x = (MAXSPRITEX << 8) + playerProjectiles[i].data.definition.location.x;
					
					if(playerProjectiles[i].data.definition.location.y - (spriteCenterY(&projectileTiles[0]) << 8) < 0)
					playerProjectiles[i].data.definition.location.y = (MAXSPRITEY << 8) + playerProjectiles[i].data.definition.location.y;
					
					if(playerProjectiles[i].data.definition.location.y > (SCREENHEIGHT << 8) && playerProjectiles[i].data.definition.location.y < (240 << 8))
					{
						playerProjectiles[i].data.enabled = 0;
						
						playerProjectiles[i].data.definition.location = offscreen;
					}
					
					if(circle_circle(playerProjectiles[i].data.definition, target.definition))
					{
						playerProjectiles[i].data.enabled = 0;
						
						playerProjectiles[i].data.definition.location = offscreen;
					}
					
					*playerProjectiles[i].data.attribute0 = projectileTiles[ATTRIBUTE0] | ((playerProjectiles[i].data.definition.location.y >> 8) - spriteCenterY(&projectileTiles[0]));
					*playerProjectiles[i].data.attribute1 = projectileTiles[ATTRIBUTE1] | ((playerProjectiles[i].data.definition.location.x >> 8) - spriteCenterX(&projectileTiles[0]));
				}
			}
			
			BG1HOFS	= starXoffset++ >> 2;
			
			*gun.pa	= *gun.pd = sine[gun.angle];
			*gun.pb	= cosine[gun.angle];
			*gun.pc	= -cosine[gun.angle];
			
			gun.definition.location.y = (-sine[gun.angle] * gunAltitude) 	+ (earth.screenLocation.y << 8);
			gun.definition.location.x = (cosine[gun.angle] * gunAltitude) 	+ (earth.screenLocation.x << 8);
			
			*gun.attribute0 = gunTiles[1] | ((gun.definition.location.y >> 8) - spriteCenterY(&gunTiles[0]));
			*gun.attribute1 = gunTiles[2] | ((gun.definition.location.x >> 8) - spriteCenterX(&gunTiles[0]));
			
			earth.paD = earth.pdD =	cosine[earth.angle];
			earth.pbD = 			-sine[earth.angle];
			earth.pcD = 			sine[earth.angle];
			
			*earth.dx = (earth.locationTex.x << 8) - (earth.paD * earth.screenLocation.x + earth.pbD * earth.screenLocation.y);
			*earth.dy = (earth.locationTex.y << 8) - (earth.pcD * earth.screenLocation.x + earth.pdD * earth.screenLocation.y);
			
			*earth.pa = earth.paD;
			*earth.pb = earth.pbD;
			*earth.pc = earth.pcD;
			*earth.pd = earth.pdD;
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