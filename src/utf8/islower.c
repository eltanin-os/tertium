#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

static ctype_rune rangetab[] = {
	0x00061, 0x0007B,
	0x000DF, 0x000F7,
	0x000F8, 0x00100,
	0x00137, 0x00139,
	0x00148, 0x0014A,
	0x0017E, 0x00181,
	0x0018C, 0x0018E,
	0x00199, 0x0019C,
	0x001AA, 0x001AC,
	0x001B9, 0x001BB,
	0x001BD, 0x001C0,
	0x001DC, 0x001DE,
	0x001EF, 0x001F1,
	0x00233, 0x0023A,
	0x0023F, 0x00241,
	0x0024F, 0x00294,
	0x00295, 0x002B0,
	0x0037B, 0x0037E,
	0x003AC, 0x003CF,
	0x003D0, 0x003D2,
	0x003D5, 0x003D8,
	0x003EF, 0x003F4,
	0x003FB, 0x003FD,
	0x00430, 0x00460,
	0x004CE, 0x004D0,
	0x00560, 0x00589,
	0x010D0, 0x010FB,
	0x010FD, 0x01100,
	0x013F8, 0x013FE,
	0x01C80, 0x01C89,
	0x01D00, 0x01D2C,
	0x01D6B, 0x01D78,
	0x01D79, 0x01D9B,
	0x01E95, 0x01E9E,
	0x01EFF, 0x01F08,
	0x01F10, 0x01F16,
	0x01F20, 0x01F28,
	0x01F30, 0x01F38,
	0x01F40, 0x01F46,
	0x01F50, 0x01F58,
	0x01F60, 0x01F68,
	0x01F70, 0x01F7E,
	0x01F80, 0x01F88,
	0x01F90, 0x01F98,
	0x01FA0, 0x01FA8,
	0x01FB0, 0x01FB5,
	0x01FB6, 0x01FB8,
	0x01FC2, 0x01FC5,
	0x01FC6, 0x01FC8,
	0x01FD0, 0x01FD4,
	0x01FD6, 0x01FD8,
	0x01FE0, 0x01FE8,
	0x01FF2, 0x01FF5,
	0x01FF6, 0x01FF8,
	0x0210E, 0x02110,
	0x0213C, 0x0213E,
	0x02146, 0x0214A,
	0x02C30, 0x02C5F,
	0x02C65, 0x02C67,
	0x02C73, 0x02C75,
	0x02C76, 0x02C7C,
	0x02CE3, 0x02CE5,
	0x02D00, 0x02D26,
	0x0A72F, 0x0A732,
	0x0A771, 0x0A779,
	0x0A793, 0x0A796,
	0x0AB30, 0x0AB5B,
	0x0AB60, 0x0AB68,
	0x0AB70, 0x0ABC0,
	0x0FB00, 0x0FB07,
	0x0FB13, 0x0FB18,
	0x0FF41, 0x0FF5B,
	0x10428, 0x10450,
	0x104D8, 0x104FC,
	0x10CC0, 0x10CF3,
	0x118C0, 0x118E0,
	0x16E60, 0x16E80,
	0x1D41A, 0x1D434,
	0x1D44E, 0x1D455,
	0x1D456, 0x1D468,
	0x1D482, 0x1D49C,
	0x1D4B6, 0x1D4BA,
	0x1D4BD, 0x1D4C4,
	0x1D4C5, 0x1D4D0,
	0x1D4EA, 0x1D504,
	0x1D51E, 0x1D538,
	0x1D552, 0x1D56C,
	0x1D586, 0x1D5A0,
	0x1D5BA, 0x1D5D4,
	0x1D5EE, 0x1D608,
	0x1D622, 0x1D63C,
	0x1D656, 0x1D670,
	0x1D68A, 0x1D6A6,
	0x1D6C2, 0x1D6DB,
	0x1D6DC, 0x1D6E2,
	0x1D6FC, 0x1D715,
	0x1D716, 0x1D71C,
	0x1D736, 0x1D74F,
	0x1D750, 0x1D756,
	0x1D770, 0x1D789,
	0x1D78A, 0x1D790,
	0x1D7AA, 0x1D7C3,
	0x1D7C4, 0x1D7CA,
	0x1E922, 0x1E944,
};

static ctype_rune tab[] = {
	0x000B5,
	0x00101,
	0x00103,
	0x00105,
	0x00107,
	0x00109,
	0x0010B,
	0x0010D,
	0x0010F,
	0x00111,
	0x00113,
	0x00115,
	0x00117,
	0x00119,
	0x0011B,
	0x0011D,
	0x0011F,
	0x00121,
	0x00123,
	0x00125,
	0x00127,
	0x00129,
	0x0012B,
	0x0012D,
	0x0012F,
	0x00131,
	0x00133,
	0x00135,
	0x0013A,
	0x0013C,
	0x0013E,
	0x00140,
	0x00142,
	0x00144,
	0x00146,
	0x0014B,
	0x0014D,
	0x0014F,
	0x00151,
	0x00153,
	0x00155,
	0x00157,
	0x00159,
	0x0015B,
	0x0015D,
	0x0015F,
	0x00161,
	0x00163,
	0x00165,
	0x00167,
	0x00169,
	0x0016B,
	0x0016D,
	0x0016F,
	0x00171,
	0x00173,
	0x00175,
	0x00177,
	0x0017A,
	0x0017C,
	0x00183,
	0x00185,
	0x00188,
	0x00192,
	0x00195,
	0x0019E,
	0x001A1,
	0x001A3,
	0x001A5,
	0x001A8,
	0x001AD,
	0x001B0,
	0x001B4,
	0x001B6,
	0x001C6,
	0x001C9,
	0x001CC,
	0x001CE,
	0x001D0,
	0x001D2,
	0x001D4,
	0x001D6,
	0x001D8,
	0x001DA,
	0x001DF,
	0x001E1,
	0x001E3,
	0x001E5,
	0x001E7,
	0x001E9,
	0x001EB,
	0x001ED,
	0x001F3,
	0x001F5,
	0x001F9,
	0x001FB,
	0x001FD,
	0x001FF,
	0x00201,
	0x00203,
	0x00205,
	0x00207,
	0x00209,
	0x0020B,
	0x0020D,
	0x0020F,
	0x00211,
	0x00213,
	0x00215,
	0x00217,
	0x00219,
	0x0021B,
	0x0021D,
	0x0021F,
	0x00221,
	0x00223,
	0x00225,
	0x00227,
	0x00229,
	0x0022B,
	0x0022D,
	0x0022F,
	0x00231,
	0x0023C,
	0x00242,
	0x00247,
	0x00249,
	0x0024B,
	0x0024D,
	0x00371,
	0x00373,
	0x00377,
	0x00390,
	0x003D9,
	0x003DB,
	0x003DD,
	0x003DF,
	0x003E1,
	0x003E3,
	0x003E5,
	0x003E7,
	0x003E9,
	0x003EB,
	0x003ED,
	0x003F5,
	0x003F8,
	0x00461,
	0x00463,
	0x00465,
	0x00467,
	0x00469,
	0x0046B,
	0x0046D,
	0x0046F,
	0x00471,
	0x00473,
	0x00475,
	0x00477,
	0x00479,
	0x0047B,
	0x0047D,
	0x0047F,
	0x00481,
	0x0048B,
	0x0048D,
	0x0048F,
	0x00491,
	0x00493,
	0x00495,
	0x00497,
	0x00499,
	0x0049B,
	0x0049D,
	0x0049F,
	0x004A1,
	0x004A3,
	0x004A5,
	0x004A7,
	0x004A9,
	0x004AB,
	0x004AD,
	0x004AF,
	0x004B1,
	0x004B3,
	0x004B5,
	0x004B7,
	0x004B9,
	0x004BB,
	0x004BD,
	0x004BF,
	0x004C2,
	0x004C4,
	0x004C6,
	0x004C8,
	0x004CA,
	0x004CC,
	0x004D1,
	0x004D3,
	0x004D5,
	0x004D7,
	0x004D9,
	0x004DB,
	0x004DD,
	0x004DF,
	0x004E1,
	0x004E3,
	0x004E5,
	0x004E7,
	0x004E9,
	0x004EB,
	0x004ED,
	0x004EF,
	0x004F1,
	0x004F3,
	0x004F5,
	0x004F7,
	0x004F9,
	0x004FB,
	0x004FD,
	0x004FF,
	0x00501,
	0x00503,
	0x00505,
	0x00507,
	0x00509,
	0x0050B,
	0x0050D,
	0x0050F,
	0x00511,
	0x00513,
	0x00515,
	0x00517,
	0x00519,
	0x0051B,
	0x0051D,
	0x0051F,
	0x00521,
	0x00523,
	0x00525,
	0x00527,
	0x00529,
	0x0052B,
	0x0052D,
	0x0052F,
	0x01E01,
	0x01E03,
	0x01E05,
	0x01E07,
	0x01E09,
	0x01E0B,
	0x01E0D,
	0x01E0F,
	0x01E11,
	0x01E13,
	0x01E15,
	0x01E17,
	0x01E19,
	0x01E1B,
	0x01E1D,
	0x01E1F,
	0x01E21,
	0x01E23,
	0x01E25,
	0x01E27,
	0x01E29,
	0x01E2B,
	0x01E2D,
	0x01E2F,
	0x01E31,
	0x01E33,
	0x01E35,
	0x01E37,
	0x01E39,
	0x01E3B,
	0x01E3D,
	0x01E3F,
	0x01E41,
	0x01E43,
	0x01E45,
	0x01E47,
	0x01E49,
	0x01E4B,
	0x01E4D,
	0x01E4F,
	0x01E51,
	0x01E53,
	0x01E55,
	0x01E57,
	0x01E59,
	0x01E5B,
	0x01E5D,
	0x01E5F,
	0x01E61,
	0x01E63,
	0x01E65,
	0x01E67,
	0x01E69,
	0x01E6B,
	0x01E6D,
	0x01E6F,
	0x01E71,
	0x01E73,
	0x01E75,
	0x01E77,
	0x01E79,
	0x01E7B,
	0x01E7D,
	0x01E7F,
	0x01E81,
	0x01E83,
	0x01E85,
	0x01E87,
	0x01E89,
	0x01E8B,
	0x01E8D,
	0x01E8F,
	0x01E91,
	0x01E93,
	0x01E9F,
	0x01EA1,
	0x01EA3,
	0x01EA5,
	0x01EA7,
	0x01EA9,
	0x01EAB,
	0x01EAD,
	0x01EAF,
	0x01EB1,
	0x01EB3,
	0x01EB5,
	0x01EB7,
	0x01EB9,
	0x01EBB,
	0x01EBD,
	0x01EBF,
	0x01EC1,
	0x01EC3,
	0x01EC5,
	0x01EC7,
	0x01EC9,
	0x01ECB,
	0x01ECD,
	0x01ECF,
	0x01ED1,
	0x01ED3,
	0x01ED5,
	0x01ED7,
	0x01ED9,
	0x01EDB,
	0x01EDD,
	0x01EDF,
	0x01EE1,
	0x01EE3,
	0x01EE5,
	0x01EE7,
	0x01EE9,
	0x01EEB,
	0x01EED,
	0x01EEF,
	0x01EF1,
	0x01EF3,
	0x01EF5,
	0x01EF7,
	0x01EF9,
	0x01EFB,
	0x01EFD,
	0x01FBE,
	0x0210A,
	0x02113,
	0x0212F,
	0x02134,
	0x02139,
	0x0214E,
	0x02184,
	0x02C61,
	0x02C68,
	0x02C6A,
	0x02C6C,
	0x02C71,
	0x02C81,
	0x02C83,
	0x02C85,
	0x02C87,
	0x02C89,
	0x02C8B,
	0x02C8D,
	0x02C8F,
	0x02C91,
	0x02C93,
	0x02C95,
	0x02C97,
	0x02C99,
	0x02C9B,
	0x02C9D,
	0x02C9F,
	0x02CA1,
	0x02CA3,
	0x02CA5,
	0x02CA7,
	0x02CA9,
	0x02CAB,
	0x02CAD,
	0x02CAF,
	0x02CB1,
	0x02CB3,
	0x02CB5,
	0x02CB7,
	0x02CB9,
	0x02CBB,
	0x02CBD,
	0x02CBF,
	0x02CC1,
	0x02CC3,
	0x02CC5,
	0x02CC7,
	0x02CC9,
	0x02CCB,
	0x02CCD,
	0x02CCF,
	0x02CD1,
	0x02CD3,
	0x02CD5,
	0x02CD7,
	0x02CD9,
	0x02CDB,
	0x02CDD,
	0x02CDF,
	0x02CE1,
	0x02CEC,
	0x02CEE,
	0x02CF3,
	0x02D27,
	0x02D2D,
	0x0A641,
	0x0A643,
	0x0A645,
	0x0A647,
	0x0A649,
	0x0A64B,
	0x0A64D,
	0x0A64F,
	0x0A651,
	0x0A653,
	0x0A655,
	0x0A657,
	0x0A659,
	0x0A65B,
	0x0A65D,
	0x0A65F,
	0x0A661,
	0x0A663,
	0x0A665,
	0x0A667,
	0x0A669,
	0x0A66B,
	0x0A66D,
	0x0A681,
	0x0A683,
	0x0A685,
	0x0A687,
	0x0A689,
	0x0A68B,
	0x0A68D,
	0x0A68F,
	0x0A691,
	0x0A693,
	0x0A695,
	0x0A697,
	0x0A699,
	0x0A69B,
	0x0A723,
	0x0A725,
	0x0A727,
	0x0A729,
	0x0A72B,
	0x0A72D,
	0x0A733,
	0x0A735,
	0x0A737,
	0x0A739,
	0x0A73B,
	0x0A73D,
	0x0A73F,
	0x0A741,
	0x0A743,
	0x0A745,
	0x0A747,
	0x0A749,
	0x0A74B,
	0x0A74D,
	0x0A74F,
	0x0A751,
	0x0A753,
	0x0A755,
	0x0A757,
	0x0A759,
	0x0A75B,
	0x0A75D,
	0x0A75F,
	0x0A761,
	0x0A763,
	0x0A765,
	0x0A767,
	0x0A769,
	0x0A76B,
	0x0A76D,
	0x0A76F,
	0x0A77A,
	0x0A77C,
	0x0A77F,
	0x0A781,
	0x0A783,
	0x0A785,
	0x0A787,
	0x0A78C,
	0x0A78E,
	0x0A791,
	0x0A797,
	0x0A799,
	0x0A79B,
	0x0A79D,
	0x0A79F,
	0x0A7A1,
	0x0A7A3,
	0x0A7A5,
	0x0A7A7,
	0x0A7A9,
	0x0A7AF,
	0x0A7B5,
	0x0A7B7,
	0x0A7B9,
	0x0A7BB,
	0x0A7BD,
	0x0A7BF,
	0x0A7C3,
	0x0A7FA,
	0x1D4BB,
	0x1D7CB,
};

/* Ll */
int
c_utf8_islower(ctype_rune r)
{
	if (UTF8_RANGESEARCH(&r, rangetab))
		return 1;
	if (UTF8_SEARCH(&r, tab))
		return 1;
	return 0;
}
