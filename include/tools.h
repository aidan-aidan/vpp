#ifndef TOOLS
#define TOOLS



#define INLINE static inline

typedef void (*fnptr)(void);

typedef unsigned  int    u32;
typedef signed    int    s32;
typedef unsigned  short  u16;
typedef signed    short  s16;
typedef unsigned  char   u8;
typedef signed    char   s8;

typedef struct point{
	s32 x;
	s32 y;
}point;
typedef struct sprite{
	u16*  attribute0;
	u16*  attribute1;
	u16*  attribute2;
	point location;
	u32   enabled;
}sprite;
typedef struct affSprite{
	u16*  attribute0;
	u16*  attribute1;
	u16*  attribute2;
	u16*  pa;
	u16*  pb;
	u16*  pc;
	u16*  pd;
	s32   paD;
	s32   pbD;
	s32   pcD;
	s32   pdD;
	u32   angle;
	point location;
	u32   enabled;
}affSprite;
typedef struct affBG{
	u16*  			attribute0;
	u16*  			attribute1;
	u16*  			attribute2;
	volatile u16* 	pa;
	volatile u16* 	pb;
	volatile u16* 	pc;
	volatile u16* 	pd;
	volatile u32*	dx;
	volatile u32*   dy;
	volatile u16*   cnt;
	s32   			paD;
	s32   			pbD;
	s32   			pcD;
	s32   			pdD;
	u32   			angle;
	point 			screenLocation;
	point 			locationTex;
}affBG;
typedef struct rectangle{
	point location;
	u32 width;
	u32 height;
}rectangle;
typedef struct circle{
	point location;
	u32 radius;
}circle;

extern u32	r                	(void);
extern u32	getSeed           	(void);
extern void	setSeed           	(u32);

extern void	loadBGpalette      	(const u32*);
extern void	loadBGsubPalette  	(const u32*);

extern void	loadBGtiles       	(const u32*, u32*);
extern void	resetBGtilesLoad   	(void);

extern void	loadBGmap        	(const u32*, u32*, u32);
extern void	loadAFFmap        	(const u32*, u32*);
extern void	resetBGmap       	(u32*, u32);

extern void	loadOBJpalette   	(const u32*);
extern void	loadOBJsubPalette 	(const u32*);
extern void	loadOBJtiles      	(const u32*);
extern void	resetOBJtilesLoad  	(void);

extern void	resetOAM         	(void);

extern void	OBJneutralTransform	(void);

extern void	drawString      	(const char*, u16*, u32, point, u32);
extern void	drawChar          	(char, u16*, u32, u32);

extern s32	power				(s32 base, u32 exponent);
extern u32	squareRoot			(u32 number);

extern u16        keyCurrent,
                  keyPrevious;

#define SCREENWIDTH          240
#define SCREENHEIGHT         160
#define SCREENWIDTHTILE      30
#define SCREENHEIGHTTILE     20
#define TILEWIDTH            8
#define TILEHEIGHT           8
#define CIRCLE_DIVISION      2048
#define SPRITEWIDTH			 4
#define SPRITEHEIGHT		 5
#define ATTRIBUTE0			 1
#define ATTRIBUTE1			 2
#define ATTRIBUTE2			 3

#define MODE0                0x0000
#define MODE1                0x0001
#define MODE2                0x0002
#define MODE3                0x0003
#define MODE4                0x0004
#define MODE5                0x0005
#define OBJ1D                0x0040
#define BG0_ENABLE           0x0100
#define BG1_ENABLE           0x0200
#define BG2_ENABLE           0x0400
#define BG3_ENABLE           0x0800
#define OBJ_ENABLE           0x1000

#define VBLANKFLAG           0x0001
#define VCOUNTFLAG           0x0004
#define VCOUNTSETTING160     0xA000
#define VBLANKIRQ            0x0008

#define BG_REG_32X32         0x0000
#define BG_REG_64X32         0x4000
#define BG_REG_32X64         0x8000
#define BG_REG_64X64         0xC000
#define BG_AFF_16X16         0x0000
#define BG_AFF_32X32         0x4000
#define BG_AFF_64X64         0x8000
#define BG_AFF_128X128       0xC000

#define CHARBLOCK_LENGTH     0x4000
#define SCREENBLOCK_LENGTH   0x0800
#define AFF128X128U32_LENGTH 0x1000
#define AFF64X64U32_LENGTH   0x0400
#define BG64X64U32_LENGTH    0x0800
#define BG64X64U16_LENGTH    0x1000
#define BG64X32U32_LENGTH    0x0400
#define BG32X64U32_LENGTH    0x0400
#define BG32X32U32_LENGTH    0x0200
#define OAM_LENGTH           0x0200
#define PALETTELENGTH        128
#define SUBPALETTELENGTH     8
#define TILELENGTH4BPP       8
#define TILELENGTH8BPP       16

#define BGCOLOR16            0x0000
#define BGCOLOR256           0x0080

#define SBB0                 0x0000
#define SBB1                 0x0100
#define SBB2                 0x0200
#define SBB3                 0x0300
#define SBB4                 0x0400
#define SBB5                 0x0500
#define SBB6                 0x0600
#define SBB7                 0x0700
#define SBB8                 0x0800
#define SBB9                 0x0900
#define SBB10                0x0A00
#define SBB11                0x0B00
#define SBB12                0x0C00
#define SBB13                0x0D00
#define SBB14                0x0E00
#define SBB15                0x0F00
#define SBB16                0x1000
#define SBB17                0x1100
#define SBB18                0x1200
#define SBB19                0x1300
#define SBB20                0x1400
#define SBB21                0x1500
#define SBB22                0x1600
#define SBB23                0x1700
#define SBB24                0x1800
#define SBB25                0x1900
#define SBB26                0x1A00
#define SBB27                0x1B00
#define SBB28                0x1C00
#define SBB29                0x1D00
#define SBB30                0x1E00
#define SBB31                0x1F00

#define CBB0                 0x0000
#define CBB1                 0x0004
#define CBB2                 0x0008
#define CBB3                 0x000C

#define PALETTE0             0x0000
#define PALETTE1             0x1000
#define PALETTE2             0x2000
#define PALETTE3             0x3000
#define PALETTE4             0x4000
#define PALETTE5             0x5000
#define PALETTE6             0x6000
#define PALETTE7             0x7000
#define PALETTE8             0x8000
#define PALETTE9             0x9000
#define PALETTE10            0xA000
#define PALETTE11            0xB000
#define PALETTE12            0xC000
#define PALETTE13            0xD000
#define PALETTE14            0xE000
#define PALETTE15            0xF000

#define AFFPARAM0			 0x0000
#define AFFPARAM1			 0x0200
#define AFFPARAM2			 0x0400
#define AFFPARAM3			 0x0600
#define AFFPARAM4			 0x0800
#define AFFPARAM5			 0x0A00
#define AFFPARAM6			 0x0C00
#define AFFPARAM7			 0x0E00
#define AFFPARAM8			 0x1000
#define AFFPARAM9			 0x1200
#define AFFPARAM10			 0x1400
#define AFFPARAM11			 0x1600
#define AFFPARAM12			 0x1800
#define AFFPARAM13			 0x1A00
#define AFFPARAM14			 0x1C00
#define AFFPARAM15			 0x1E00
#define AFFPARAM16			 0x2000
#define AFFPARAM17			 0x2200
#define AFFPARAM18			 0x2400
#define AFFPARAM19			 0x2600
#define AFFPARAM20			 0x2800
#define AFFPARAM21			 0x2A00
#define AFFPARAM22			 0x2C00
#define AFFPARAM23			 0x2E00
#define AFFPARAM24			 0x3000
#define AFFPARAM25			 0x3200
#define AFFPARAM26			 0x3400
#define AFFPARAM27			 0x3600
#define AFFPARAM28			 0x3800
#define AFFPARAM29			 0x3A00
#define AFFPARAM30			 0x3C00
#define AFFPARAM31			 0x3E00

#define VFLIP                0x0800
#define HFLIP                0x0400
#define DOUBLESIZE           0x0200

#define SOUND_HVOLUME100     0x0002
#define SOUND_HAVOLUME100    0x0004
#define SOUND_HBVOLUME100    0x0008
#define SOUND_HBVOLUME0      0x0000
#define SOUND_HAENABLERIGHT  0x0100
#define SOUND_HAENABLELEFT   0x0200
#define SOUND_HATIMER0       0x0000
#define SOUND_HARESETFIFO    0x0800
#define SOUND_HBENABLERIGHT  0x1000
#define SOUND_HBENABLELEFT   0x2000
#define SOUND_HBDISABLERIGHT 0x0000
#define SOUND_HBDISABLELEFT  0x0000
#define SOUND_HBTIMER0       0x0000
#define SOUND_HBRESETFIFO    0x8000

#define SOUND_XFIFOME        0x0080

#define TIMER_F1             0x0000
#define TIMER_F64            0x0001
#define TIMER_F256           0x0002
#define TIMER_F1024          0x0003
#define TIMER_COUNTUPTIMING  0x0004
#define TIMER_IRQENABLE      0x0040
#define TIMER_START          0x0080

#define DMASTARTTIMING_SPEC  0x3000
#define DMAENABLE            0x8000
#define DMAREPEAT            0x0200
#define DMATRANSFER_32       0x0400

#define BUTTON_A             0x0001
#define BUTTON_B             0x0002
#define BUTTON_SELECT        0x0004
#define BUTTON_START         0x0008
#define BUTTON_RIGHT         0x0010
#define BUTTON_LEFT          0x0020
#define BUTTON_UP            0x0040
#define BUTTON_DOWN          0x0080
#define BUTTON_R             0X0100
#define BUTTON_L             0x0200
#define BUTTON_MASK          0x03FF

#define INTERRUPT_VBL        0x0001
#define INTERRUPT_HBL        0x0002
#define INTERRUPT_VCT        0x0004
#define INTERRUPT_TM0        0x0008
#define INTERRUPT_TM1        0x0010
#define INTERRUPT_TM2        0x0020
#define INTERRUPT_TM3        0x0040
#define INTERRUPT_COM        0x0080
#define INTERRUPT_DMA0       0x0100
#define INTERRUPT_DMA1       0x0200
#define INTERRUPT_DMA2       0x0400
#define INTERRUPT_DMA3       0x0800
#define INTERRUPT_KEY        0x1000
#define INTERRUPT_PAK        0x2000

#define OAMLENGTH            384
#define OBJ_DISABLE          0x0200
#define OBJ_DISABLE32        0x02000200
#define BGDXSIGN             0x08000000

#define IME_ENABLE           0x0001

#define REG_ISR_MAIN         *(fnptr*)(0x03007FFC)
#define DISPCNT              *((volatile u16*)(0x04000000))
#define KEYINPUT             *((volatile u16*)(0x04000130))
#define SOUNDCNT_X           *((volatile u32*)(0x04000084))
#define SOUNDCNT_H           *((volatile u16*)(0x04000082))
#define DISPSTAT             *((volatile u16*)(0x04000004))
#define VCOUNT               *((volatile u16*)(0x04000006))
#define KEYCNT               *((volatile u16*)(0x04000132))

#define BG0CNT               *((volatile u16*)(0x04000008))
#define BG1CNT               *((volatile u16*)(0x0400000A))
#define BG2CNT               *((volatile u16*)(0x0400000C))
#define BG3CNT               *((volatile u16*)(0x0400000E))

#define BG0HOFS              *((volatile u16*)(0x04000010))
#define BG1HOFS              *((volatile u16*)(0x04000014))
#define BG2HOFS              *((volatile u16*)(0x04000018))
#define BG3HOFS              *((volatile u16*)(0x0400001C))
#define BG0VOFS              *((volatile u16*)(0x04000012))
#define BG1VOFS              *((volatile u16*)(0x04000016))
#define BG2VOFS              *((volatile u16*)(0x0400001A))
#define BG3VOFS              *((volatile u16*)(0x0400001E))

#define BG2X                 *((volatile u32*)(0x04000028))
#define BG2Y                 *((volatile u32*)(0x0400002C))
#define BG2PA                *((volatile u16*)(0x04000020))
#define BG2PB                *((volatile u16*)(0x04000022))
#define BG2PC                *((volatile u16*)(0x04000024))
#define BG2PD                *((volatile u16*)(0x04000026))

#define TM0CNT               *((volatile u16*)(0x04000102))
#define TM0CNTCOUNT          *((volatile u16*)(0x04000100))
#define TM1CNT               *((volatile u16*)(0x04000106))
#define TM1CNTCOUNT          *((volatile u16*)(0x04000104))
#define TM2CNT               *((volatile u16*)(0x0400010A))
#define TM2CNTCOUNT          *((volatile u16*)(0x04000108))
#define TM3CNT               *((volatile u16*)(0x0400010E))
#define TM3CNTCOUNT          *((volatile u16*)(0x0400010C))

#define DMA0SAD              *((volatile u32*)(0x040000B0))
#define DMA1SAD              *((volatile u32*)(0x040000BC))
#define DMA2SAD              *((volatile u32*)(0x040000C8))
#define DMA3SAD              *((volatile u32*)(0x040000D4))

#define DMA0DAD              *((volatile u32*)(0x040000B4))
#define DMA1DAD              *((volatile u32*)(0x040000C0))
#define DMA2DAD              *((volatile u32*)(0x040000CC))
#define DMA3DAD              *((volatile u32*)(0x040000D8))

#define FIFOA                *((volatile u32*)(0x040000A0))

#define INTERRUPTME          *((volatile u16*)(0x04000208))
#define INTERRUPTE           *((volatile u16*)(0x04000200))
#define INTERRUPTF           *((volatile u16*)(0x04000202))

#define DMA0WCNT             *((volatile u16*)(0x040000B8))
#define DMA1WCNT             *((volatile u16*)(0x040000C4))
#define DMA2WCNT             *((volatile u16*)(0x040000D0))
#define DMA3WCNT             *((volatile u16*)(0x040000DC))

#define DMA0CNT              *((volatile u16*)(0x040000BA))
#define DMA1CNT              *((volatile u16*)(0x040000C6))
#define DMA2CNT              *((volatile u16*)(0x040000D2))
#define DMA3CNT              *((volatile u16*)(0x040000DE))

#define SBB0_U16_LOC         ((u16*)0x06000000)
#define SBB0_U32_LOC         ((u32*)0x06000000)
#define SBB1_U16_LOC         ((u16*)0x06000800)
#define SBB1_U32_LOC         ((u32*)0x06000800)
#define SBB2_U16_LOC         ((u16*)0x06001000)
#define SBB2_U32_LOC         ((u32*)0x06001000)
#define SBB3_U16_LOC         ((u16*)0x06001800)
#define SBB3_U32_LOC         ((u32*)0x06001800)
#define SBB4_U16_LOC         ((u16*)0x06002000)
#define SBB4_U32_LOC         ((u32*)0x06002000)
#define SBB5_U16_LOC         ((u16*)0x06002800)
#define SBB5_U32_LOC         ((u32*)0x06002800)
#define SBB6_U16_LOC         ((u16*)0x06003000)
#define SBB6_U32_LOC         ((u32*)0x06003000)
#define SBB7_U16_LOC         ((u16*)0x06003800)
#define SBB7_U32_LOC         ((u32*)0x06003800)
#define SBB8_U16_LOC         ((u16*)0x06004000)
#define SBB8_U32_LOC         ((u32*)0x06004000)
#define SBB9_U16_LOC         ((u16*)0x06004800)
#define SBB9_U32_LOC         ((u32*)0x06004800)
#define SBB10_U16_LOC        ((u16*)0x06005000)
#define SBB10_U32_LOC        ((u32*)0x06005000)
#define SBB11_U16_LOC        ((u16*)0x06005800)
#define SBB11_U32_LOC        ((u32*)0x06005800)
#define SBB12_U16_LOC        ((u16*)0x06006000)
#define SBB12_U32_LOC        ((u32*)0x06006000)
#define SBB13_U16_LOC        ((u16*)0x06006800)
#define SBB13_U32_LOC        ((u32*)0x06006800)
#define SBB14_U16_LOC        ((u16*)0x06007000)
#define SBB14_U32_LOC        ((u32*)0x06007000)
#define SBB15_U16_LOC        ((u16*)0x06007800)
#define SBB15_U32_LOC        ((u32*)0x06007800)
#define SBB16_U16_LOC        ((u16*)0x06008000)
#define SBB16_U32_LOC        ((u32*)0x06008000)
#define SBB17_U16_LOC        ((u16*)0x06008800)
#define SBB17_U32_LOC        ((u32*)0x06008800)
#define SBB18_U16_LOC        ((u16*)0x06009000)
#define SBB18_U32_LOC        ((u32*)0x06009000)
#define SBB19_U16_LOC        ((u16*)0x06009800)
#define SBB19_U32_LOC        ((u32*)0x06009800)
#define SBB20_U16_LOC        ((u16*)0x0600A000)
#define SBB20_U32_LOC        ((u32*)0x0600A000)
#define SBB21_U16_LOC        ((u16*)0x0600A800)
#define SBB21_U32_LOC        ((u32*)0x0600A800)
#define SBB22_U16_LOC        ((u16*)0x0600B000)
#define SBB22_U32_LOC        ((u32*)0x0600B000)
#define SBB23_U16_LOC        ((u16*)0x0600B800)
#define SBB23_U32_LOC        ((u32*)0x0600B800)
#define SBB24_U16_LOC        ((u16*)0x0600C000)
#define SBB24_U32_LOC        ((u32*)0x0600C000)
#define SBB25_U16_LOC        ((u16*)0x0600C800)
#define SBB25_U32_LOC        ((u32*)0x0600C800)
#define SBB26_U16_LOC        ((u16*)0x0600D000)
#define SBB26_U32_LOC        ((u32*)0x0600D000)
#define SBB27_U16_LOC        ((u16*)0x0600D800)
#define SBB27_U32_LOC        ((u32*)0x0600D800)
#define SBB28_U16_LOC        ((u16*)0x0600E000)
#define SBB28_U32_LOC        ((u32*)0x0600E000)
#define SBB29_U16_LOC        ((u16*)0x0600E800)
#define SBB29_U32_LOC        ((u32*)0x0600E800)
#define SBB30_U16_LOC        ((u16*)0x0600F000)
#define SBB30_U32_LOC        ((u32*)0x0600F000)
#define SBB31_U16_LOC        ((u16*)0x0600F800)
#define SBB31_U32_LOC        ((u32*)0x0600F800)

#define CBB0_U16_LOC         ((u16*)0x06000000)
#define CBB0_U32_LOC         ((u32*)0x06000000)
#define CBB1_U16_LOC         ((u16*)0x06004000)
#define CBB1_U32_LOC         ((u32*)0x06004000)
#define CBB2_U16_LOC         ((u16*)0x06008000)
#define CBB2_U32_LOC         ((u32*)0x06008000)
#define CBB3_U16_LOC         ((u16*)0x0600C000)
#define CBB3_U32_LOC         ((u32*)0x0600C000)

#define BGPAL                ((u32*)0x05000000)
#define OBJPAL               ((u32*)0x05000200)
#define BGPALU16             ((u16*)0x05000000)
#define OBJPALU16            ((u16*)0x05000200)
#define OBJTILELOC           ((u32*)0x06010000)
#define OAMLOC               ((u16*)0x07000000)
#define VRAM                 ((u32*)0x06000000)

#define BG2P                 ((u16*)0x04000020)

extern const s32 sine[CIRCLE_DIVISION];
extern const s32 cosine[CIRCLE_DIVISION];

INLINE void keyPoll(){
	keyPrevious = keyCurrent;
    keyCurrent = ~KEYINPUT;
}

INLINE void setBGswatch 	(u32 x, u32 y, u32 value)	{BGPALU16[y * 16 + x] = (u16)value;}
INLINE void setOBJswatch	(u32 x, u32 y, u32 value)	{OBJPALU16[y * 16 + x] = (u16)value;}
INLINE u32  keyPress    	(u32 key)                	{return((keyCurrent & ~keyPrevious) & key);}
INLINE u32  keyDown     	(u32 key)                	{return(keyCurrent & key);}
INLINE u32	square			(u32 base)					{return(base * base);}
INLINE s32  spriteCenterX	(const u32* sprite)			{return((sprite[SPRITEWIDTH]  >> 1) + (((sprite[ATTRIBUTE0] & DOUBLESIZE) >> 9) * (sprite[SPRITEWIDTH]  >> 1)));}
INLINE s32	spriteCenterY	(const u32* sprite)			{return((sprite[SPRITEHEIGHT] >> 1) + (((sprite[ATTRIBUTE0] & DOUBLESIZE) >> 9) * (sprite[SPRITEHEIGHT] >> 1)));}



#endif