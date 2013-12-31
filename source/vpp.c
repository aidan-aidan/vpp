#include <..\include\vpp.h>
#include <..\include\tools.h>
#include <..\include\palettes.h>
#include <..\include\tilesets.h>
#include <..\include\tilemaps.h>
#include <..\include\text.h>
#include <..\include\sprites.h>

/*
All points stored in sprite structures are assumed to be the center fo the sprite, and of the format 24.8
*/

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
	
	loadBGpalette   (titleScreenPalette);
	loadBGtiles     (blank8bppTile, CBB1_U32_LOC);
	loadBGtiles     (titleScreenTiles, CBB1_U32_LOC);
	loadBGmap       (titleScreenMap, SBB30_U32_LOC, 0);
	resetBGtilesLoad();
	loadBGtiles     (dosFontTiles, CBB0_U32_LOC);
	
	drawDOS(pressStart, SBB31_U16_LOC, PRESSSTARTLENGTH, pressStartPos, PALETTE15);
	
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
				DISPCNT = 0;
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
		vBlankBool_A	= 0,
		vBlankBool_B	= 0,
		shipTurnSpeed	= 15;
	
	s32	shipMaxSpeed = 32768;
	
	point starOffset       = {0, 0},
		  shipAcceleration = {0, 0};
		  
	affSprite playerShip = {&OAMLOC[0], &OAMLOC[1], &OAMLOC[2], &OAMLOC[3], &OAMLOC[7], &OAMLOC[11], &OAMLOC[15], 256, 0, 0, 256, 0, {{120 << 8, 80 << 8}, 6}, 1};
						 
	*playerShip.attribute0			= (shipTiles[ATTRIBUTE0] | ((playerShip.definition.center.y >> 8) - spriteCenterY(shipTiles)));
	*playerShip.attribute1			= (shipTiles[ATTRIBUTE1] | ((playerShip.definition.center.x >> 8) - spriteCenterX(shipTiles)));
	*playerShip.attribute2			= (shipTiles[ATTRIBUTE2]);
	*playerShip.pa = *playerShip.pd	= playerShip.paD;
	*playerShip.pb = *playerShip.pc	= playerShip.pbD;
		
	DISPCNT = (MODE0 | OBJ1D | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE | BG3_ENABLE | OBJ_ENABLE);
	
	BG0CNT  = (CBB0	| SBB31	| BGCOLOR16	| BG_REG_32X32);
	BG1CNT  = (CBB1	| SBB27	| BGCOLOR16	| BG_REG_64X64);
	BG2CNT  = (CBB1	| SBB23	| BGCOLOR16	| BG_REG_64X64);
	BG3CNT  = (CBB1	| SBB19	| BGCOLOR16	| BG_REG_64X64);
	
	loadBGpalette   (gameScreenBGpalette);
	loadBGtiles     (blank4bppTile, CBB1_U32_LOC);
	loadBGtiles     (starTiles, CBB1_U32_LOC);
	resetBGtilesLoad();
	loadBGtiles     (dosFontTiles, CBB0_U32_LOC);
	loadOBJpalette  (gameScreenOBJpalette);
	loadOBJtiles    (blank8bppSprite);
	loadOBJtiles    (shipTiles);
	
	for(i = 0; i < BG64X64U32_LENGTH * 3; i++)
	{
		if((r() >> 25) < 20)SBB19_U32_LOC[i] = (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) | (((r() >> 27) | PALETTE14 | ((r() >> 30) << 10)) << 16));
		else SBB19_U32_LOC[i] = 0;
	}
	
	while(1)
	{
		vBlankBool_A = (DISPSTAT & VBLANKFLAG);
		
		if(vBlankBool_A & ~vBlankBool_B)
		{
			keyPoll();
			
			if(keyDown(BUTTON_B))
			{
				shipAcceleration.x += sine[playerShip.angle];
				shipAcceleration.y += -cosine[playerShip.angle];
			}
			if(keyDown(BUTTON_A))
			{
				shipAcceleration.x >>= 1;
				shipAcceleration.y >>= 1;
			}
			
			if(keyDown(BUTTON_L))playerShip.angle -= shipTurnSpeed;
			if(keyDown(BUTTON_R))playerShip.angle += shipTurnSpeed;
			
			if(playerShip.angle >= CIRCLE_DIVISION)	playerShip.angle = 0;
			if(playerShip.angle < 0)				playerShip.angle = CIRCLE_DIVISION - 1;
			
			if(shipAcceleration.x > shipMaxSpeed)shipAcceleration.x = shipMaxSpeed;
			if(shipAcceleration.y > shipMaxSpeed)shipAcceleration.y = shipMaxSpeed;
			if(shipAcceleration.x < -shipMaxSpeed)shipAcceleration.x = -shipMaxSpeed;
			if(shipAcceleration.y < -shipMaxSpeed)shipAcceleration.y = -shipMaxSpeed;
			
			playerShip.definition.center.x = starOffset.x >> 8;
			playerShip.definition.center.y = starOffset.y >> 8;
			
			starOffset.x += shipAcceleration.x;
			starOffset.y += shipAcceleration.y;
			
			*playerShip.pa	= *playerShip.pd =	cosine[playerShip.angle];
			*playerShip.pc	=					sine[playerShip.angle];
			*playerShip.pd	=					-sine[playerShip.angle];
			
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
		gunDamage				= 5,
		starXoffset				= 0;
		
	circle 		offscreen	= {{255 << 8, 255 << 8}, 0};
		
	affSprite  	gun    		= {&OAMLOC[80], &OAMLOC[81], &OAMLOC[82], &OAMLOC[3], &OAMLOC[7], &OAMLOC[11], &OAMLOC[15], 256, 0, 0, 256, 512, {offscreen.center, gunTiles[SPRITEWIDTH] >> 1}, 1, 0, gunTiles, 100};
	
	sprite		target		= {&OAMLOC[84], &OAMLOC[85], &OAMLOC[86], {{32 << 8, 32 << 8}, 16}, 1, 0, circleTiles, 50};
	
	affBG      	earth		= {&BG2PA, &BG2PB, &BG2PC, &BG2PD, &BG2X, &BG2Y, &BG2CNT, 256, 0, 0, 256, 0, {120, 256}, {256, 256}};
	
	//circle	earthBound 	= {earth.screenLocation, 128};
	
	projectile	playerProjectiles[maxPlayerShots];
	
	*gun.attribute0   		= gunTiles[ATTRIBUTE0];
	*gun.attribute1   		= gunTiles[ATTRIBUTE1] | AFFPARAM0;
	*gun.attribute2  		= gunTiles[ATTRIBUTE2];
	*gun.pa = *gun.pd 		= gun.paD;
	*gun.pb = *gun.pc 		= gun.pbD;
	
	*target.attribute0		= circleTiles[ATTRIBUTE0] | ((target.definition.center.y >> 8) - spriteCenterY(circleTiles));
	*target.attribute1		= circleTiles[ATTRIBUTE1] | ((target.definition.center.x >> 8) - spriteCenterX(circleTiles));
	*target.attribute2		= circleTiles[ATTRIBUTE2];
	
	*earth.pa = *earth.pd 	= earth.paD;
	*earth.pb = *earth.pc 	= earth.pbD;
	*earth.dx				= earth.screenLocation.x;
	*earth.dy				= earth.screenLocation.y;
	
	for(i = 0; i < maxPlayerShots; i++)
	{
		playerProjectiles[i].attribute0 			= &OAMLOC[i * 4];
		playerProjectiles[i].attribute1 			= &OAMLOC[i * 4 + 1];
		playerProjectiles[i].attribute2 			= &OAMLOC[i * 4 + 2];
		
		playerProjectiles[i].definition.center		= offscreen.center;
		
		*playerProjectiles[i].attribute0			= projectileTiles[ATTRIBUTE0] | ((playerProjectiles[i].definition.center.y >> 8) - spriteCenterY(projectileTiles));
		*playerProjectiles[i].attribute1			= projectileTiles[ATTRIBUTE1] | ((playerProjectiles[i].definition.center.x >> 8) - spriteCenterX(projectileTiles));
		*playerProjectiles[i].attribute2			= projectileTiles[ATTRIBUTE2];
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
		if(r() >> 24 < 32)
		{
			SBB29_U32_LOC[i] = ((r() >> 26) | ((r() >> 30) << 10) | PALETTE1) | (((r() >> 26) | ((r() >> 30) << 10) | PALETTE1) << 16);
		}
	}
	
	BG0CNT  	= 	(CBB2  | SBB31 		| BG_REG_32X32 | BGCOLOR16  | BGPRIORITY0);
	BG1CNT  	= 	(CBB1  | SBB29 		| BG_REG_64X32 | BGCOLOR16  | BGPRIORITY2);
	*earth.cnt	= 	(CBB0  | SBB27 		| BG_AFF_64X64 | BGCOLOR256 | BGPRIORITY1);
	DISPCNT		= 	(MODE1 | BG0_ENABLE	| BG1_ENABLE   | BG2_ENABLE | OBJ_ENABLE | OBJ1D);
		
	while(1)
	{
		vBlankBool_A = (DISPSTAT & VBLANKFLAG);
		
		if(vBlankBool_A & ~vBlankBool_B)
		{
			keyPoll();
			
			if(target.hit)
			{
				spriteNormal(&target);
			}
			
			if(keyDown(BUTTON_A) && (vBlankCount & 2) && (vBlankCount & 1))
			{
				playerProjectiles[projectileIndex].angle 				= gun.angle + ((r() >> 27) - 16);
				playerProjectiles[projectileIndex].enabled 				= TRUE;
				playerProjectiles[projectileIndex].definition.center.x 	= (cosine[playerProjectiles[projectileIndex].angle] * gunAltitude) + ((earth.screenLocation.x) << 8);
				playerProjectiles[projectileIndex].definition.center.y 	= (-sine[playerProjectiles[projectileIndex].angle] * gunAltitude) + (earth.screenLocation.y << 8);
				
				*playerProjectiles[projectileIndex].attribute0			= projectileTiles[ATTRIBUTE0] | ((playerProjectiles[projectileIndex].definition.center.y >> 8) - spriteCenterY(&projectileTiles[0]));
				*playerProjectiles[projectileIndex].attribute1			= projectileTiles[ATTRIBUTE1] | ((playerProjectiles[projectileIndex].definition.center.x >> 8) - spriteCenterX(&projectileTiles[0]));
				
				projectileIndex++;
				if(projectileIndex >= maxPlayerShots)projectileIndex = 0;
			}
			
			if(keyDown(BUTTON_L))		gun.angle += 	gunSpeed;
			if(keyDown(BUTTON_R))		gun.angle -= 	gunSpeed;
			if(gun.angle > MAXGUNANGLE)	gun.angle = 	MAXGUNANGLE;
			if(gun.angle < MINGUNANGLE)	gun.angle = 	MINGUNANGLE;
			
			earth.angle++;
			if(earth.angle >= CIRCLE_DIVISION)earth.angle = 0;
			
			for(i = 0; i < maxPlayerShots; i++)
			{
				if(playerProjectiles[i].enabled)
				{
					playerProjectiles[i].definition.center.y -= sine  [playerProjectiles[i].angle] * playerProjectileSpeed;
					playerProjectiles[i].definition.center.x += cosine[playerProjectiles[i].angle] * playerProjectileSpeed;
					
					if(playerProjectiles[i].definition.center.x - (spriteCenterX(projectileTiles) << 8) < 0)
					playerProjectiles[i].definition.center.x = (MAXSPRITEX << 8) + playerProjectiles[i].definition.center.x;
					
					if(playerProjectiles[i].definition.center.y - (spriteCenterY(projectileTiles) << 8) < 0)
					playerProjectiles[i].definition.center.y = (MAXSPRITEY << 8) + playerProjectiles[i].definition.center.y;
					
					if(playerProjectiles[i].definition.center.y > (SCREENHEIGHT << 8) && playerProjectiles[i].definition.center.y < ((MAXSPRITEY - projectileTiles[SPRITEHEIGHT]) << 8))
					{
						playerProjectiles[i].enabled = FALSE;
						
						playerProjectiles[i].definition = offscreen;
					}
					
					if(circle_circle(playerProjectiles[i].definition, target.definition))
					{
						playerProjectiles[i].enabled = FALSE;
						playerProjectiles[i].definition = offscreen;
						
						spriteFlash(&target);
						
						target.health -= gunDamage;
					}
					
					*playerProjectiles[i].attribute0 = projectileTiles[ATTRIBUTE0] | ((playerProjectiles[i].definition.center.y >> 8) - spriteCenterY(projectileTiles));
					*playerProjectiles[i].attribute1 = projectileTiles[ATTRIBUTE1] | ((playerProjectiles[i].definition.center.x >> 8) - spriteCenterX(projectileTiles));
				}
			}
			
			BG1HOFS	= starXoffset++ >> 2;
			
			*gun.pa					= *gun.pd = sine[gun.angle];
			*gun.pb					= cosine[gun.angle];
			*gun.pc					= -cosine[gun.angle];
			gun.definition.center.y	= (-sine[gun.angle] * gunAltitude)		+ (earth.screenLocation.y << 8);
			gun.definition.center.x	= (cosine[gun.angle] * gunAltitude)	+ (earth.screenLocation.x << 8);
			*gun.attribute0			= gunTiles[ATTRIBUTE0] | ((gun.definition.center.y >> 8) - spriteCenterY(gunTiles));
			*gun.attribute1			= gunTiles[ATTRIBUTE1] | ((gun.definition.center.x >> 8) - spriteCenterX(gunTiles));
			
			earth.paD = cosine[earth.angle];
			earth.pbD = -sine[earth.angle];
			earth.pcD = sine[earth.angle];
			earth.pdD = earth.paD;
			*earth.dx = (earth.locationTex.x << 8) - (earth.paD * earth.screenLocation.x + earth.pbD * earth.screenLocation.y);
			*earth.dy = (earth.locationTex.y << 8) - (earth.pcD * earth.screenLocation.x + earth.pdD * earth.screenLocation.y);
			*earth.pa = earth.paD;
			*earth.pb = earth.pbD;
			*earth.pc = earth.pcD;
			*earth.pd = earth.pdD;
			
			vBlankCount++;
		}
		
		vBlankBool_B = vBlankBool_A;
	}
}

void spriteFlash(sprite* sprite)
{
	*sprite->attribute2 ^= (*sprite->attribute2 & PALETTE15);
	*sprite->attribute2 |= PALETTE15;
	sprite->hit = 1;
}

void spriteNormal(sprite* sprite)
{
	sprite->hit = 0;
	*sprite->attribute2 ^= PALETTE15;
	*sprite->attribute2 |= sprite->tileData[ATTRIBUTE2];
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