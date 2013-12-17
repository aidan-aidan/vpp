#include <..\include\tools.h>
#include <..\include\palettes.h>


const u32 titleScreenPalette[PALETTELENGTH] __attribute__((aligned(4)))={
	0x000B0000,0x02202C0B,0x34004631,0x4E600231,0x4C096018,0x00176B5A,0x6000035A,0x00806C0D,
	0x019A77A0,0x44110360,0x01DD00CD,0x2D6B35A0,0x100003BD,0x00847BDE,0x001D5C0B,0x56B5781E,
	0x4C007400,0x02E05EE0,0x0011016B,0x5C1735AD,0x01603406,0x21080004,0x4E732000,0x6F7B5EF7,
	0x780F02F7,0x7FFF6C1B,0x3DEF0111,0x2D601084,0x2C04600C,0x3C0703C0,0x001A3C0F,0x10046318,
	0x4C1377BD,0x7C1F000D,0x01002003,0x0008001F,0x01A05400,0x010801AD,0x034002B5,0x001503FF,
	0x340D001B,0x7C0F6B40,0x008B1080,0x7C004400,0x540A6800,0x000F7FE0,0x740E4408,0x02602C00,
	0x01E001FF,0x031803E0,0x741D037B,0x02730018,0x00130068,0x680C6C00,0x1001001E,0x681A0133,
	0x030003A0,0x03DE02A0,0x78005C00,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,

	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x56B50000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
};

const u32 gameScreenBGpalette[PALETTELENGTH] __attribute__((aligned(4)))={
	0x00330000,0x01002A13,0x0CEA154E,0x00041B3F,0x022000FB,0x059C12BE,0x00C04BFF,0x0AC10E3D,
	0x005A08A9,0x21D101A0,0x00220037,0x1B220140,0x06801F9F,0x01E0112C,0x01601D8F,0x13010260,
	0x4C007400,0x02E05EE0,0x0011016B,0x5C1735AD,0x01603406,0x21080004,0x4E732000,0x6F7B5EF7,
	0x780F02F7,0x7FFF6C1B,0x3DEF0111,0x2D601084,0x2C04600C,0x3C0703C0,0x001A3C0F,0x10046318,
	0x4C1377BD,0x7C1F000D,0x01002003,0x0008001F,0x01A05400,0x010801AD,0x034002B5,0x001503FF,
	0x340D001B,0x7C0F6B40,0x008B1080,0x7C004400,0x540A6800,0x000F7FE0,0x740E4408,0x02602C00,
	0x01E001FF,0x031803E0,0x741D037B,0x02730018,0x00130068,0x680C6C00,0x1001001E,0x681A0133,
	0x030003A0,0x03DE02A0,0x78005C00,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,

	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x001F0000,0x03FF021F,0x7FFF5FFF,0x00007FF4,0x00000000,0x00000000,0x00000000,0x00000000,
	0x56B50000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
};

const u32 gameScreenOBJpalette[PALETTELENGTH] __attribute__((aligned(4)))={
	0x00330000,0x01002A13,0x0CEA154E,0x00041B3F,0x022000FB,0x059C12BE,0x00C04BFF,0x0AC10E3D,
	0x005A08A9,0x21D101A0,0x00220037,0x1B220140,0x06801F9F,0x01E0112C,0x01601D8F,0x13010260,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
};

const u32 railGameBGpalette[PALETTELENGTH] __attribute__((aligned(4)))={
	0x5D220000,0x000003E0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x001F0000,0x03FF021F,0x7FFF5FFF,0x00007FF4,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,

	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
};

const u32 railGameOBJpalette[PALETTELENGTH] __attribute__((aligned(4)))={
	0x21080000,0x0C633DEF,0x529410AF,0x294A5EF7,0x14A52D6B,0x463135FA,0x18C66739,0x042135AD,
	0x027F0000,0x000003FF,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,

	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
};