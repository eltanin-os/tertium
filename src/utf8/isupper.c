#include <tertium/cpu.h>
#include <tertium/std.h>

#include "private.h"

static ctype_rune rangetab[] = {
	0x00041, 0x0005B,
	0x000C0, 0x000D7,
	0x000D8, 0x000DF,
	0x00178, 0x0017A,
	0x00181, 0x00183,
	0x00186, 0x00188,
	0x00189, 0x0018C,
	0x0018E, 0x00192,
	0x00193, 0x00195,
	0x00196, 0x00199,
	0x0019C, 0x0019E,
	0x0019F, 0x001A1,
	0x001A6, 0x001A8,
	0x001AE, 0x001B0,
	0x001B1, 0x001B4,
	0x001B7, 0x001B9,
	0x001F6, 0x001F9,
	0x0023A, 0x0023C,
	0x0023D, 0x0023F,
	0x00243, 0x00247,
	0x00388, 0x0038B,
	0x0038E, 0x00390,
	0x00391, 0x003A2,
	0x003A3, 0x003AC,
	0x003D2, 0x003D5,
	0x003F9, 0x003FB,
	0x003FD, 0x00430,
	0x004C0, 0x004C2,
	0x00531, 0x00557,
	0x010A0, 0x010C6,
	0x013A0, 0x013F6,
	0x01C90, 0x01CBB,
	0x01CBD, 0x01CC0,
	0x01F08, 0x01F10,
	0x01F18, 0x01F1E,
	0x01F28, 0x01F30,
	0x01F38, 0x01F40,
	0x01F48, 0x01F4E,
	0x01F68, 0x01F70,
	0x01FB8, 0x01FBC,
	0x01FC8, 0x01FCC,
	0x01FD8, 0x01FDC,
	0x01FE8, 0x01FED,
	0x01FF8, 0x01FFC,
	0x0210B, 0x0210E,
	0x02110, 0x02113,
	0x02119, 0x0211E,
	0x0212A, 0x0212E,
	0x02130, 0x02134,
	0x0213E, 0x02140,
	0x02C00, 0x02C2F,
	0x02C62, 0x02C65,
	0x02C6D, 0x02C71,
	0x02C7E, 0x02C81,
	0x0A77D, 0x0A77F,
	0x0A7AA, 0x0A7AF,
	0x0A7B0, 0x0A7B5,
	0x0A7C4, 0x0A7C7,
	0x0FF21, 0x0FF3B,
	0x10400, 0x10428,
	0x104B0, 0x104D4,
	0x10C80, 0x10CB3,
	0x118A0, 0x118C0,
	0x16E40, 0x16E60,
	0x1D400, 0x1D41A,
	0x1D434, 0x1D44E,
	0x1D468, 0x1D482,
	0x1D49E, 0x1D4A0,
	0x1D4A5, 0x1D4A7,
	0x1D4A9, 0x1D4AD,
	0x1D4AE, 0x1D4B6,
	0x1D4D0, 0x1D4EA,
	0x1D504, 0x1D506,
	0x1D507, 0x1D50B,
	0x1D50D, 0x1D515,
	0x1D516, 0x1D51D,
	0x1D538, 0x1D53A,
	0x1D53B, 0x1D53F,
	0x1D540, 0x1D545,
	0x1D54A, 0x1D551,
	0x1D56C, 0x1D586,
	0x1D5A0, 0x1D5BA,
	0x1D5D4, 0x1D5EE,
	0x1D608, 0x1D622,
	0x1D63C, 0x1D656,
	0x1D670, 0x1D68A,
	0x1D6A8, 0x1D6C1,
	0x1D6E2, 0x1D6FB,
	0x1D71C, 0x1D735,
	0x1D756, 0x1D76F,
	0x1D790, 0x1D7A9,
	0x1E900, 0x1E922,
};

static ctype_rune tab[] = {
	0x00100,
	0x00102,
	0x00104,
	0x00106,
	0x00108,
	0x0010A,
	0x0010C,
	0x0010E,
	0x00110,
	0x00112,
	0x00114,
	0x00116,
	0x00118,
	0x0011A,
	0x0011C,
	0x0011E,
	0x00120,
	0x00122,
	0x00124,
	0x00126,
	0x00128,
	0x0012A,
	0x0012C,
	0x0012E,
	0x00130,
	0x00132,
	0x00134,
	0x00136,
	0x00139,
	0x0013B,
	0x0013D,
	0x0013F,
	0x00141,
	0x00143,
	0x00145,
	0x00147,
	0x0014A,
	0x0014C,
	0x0014E,
	0x00150,
	0x00152,
	0x00154,
	0x00156,
	0x00158,
	0x0015A,
	0x0015C,
	0x0015E,
	0x00160,
	0x00162,
	0x00164,
	0x00166,
	0x00168,
	0x0016A,
	0x0016C,
	0x0016E,
	0x00170,
	0x00172,
	0x00174,
	0x00176,
	0x0017B,
	0x0017D,
	0x00184,
	0x001A2,
	0x001A4,
	0x001A9,
	0x001AC,
	0x001B5,
	0x001BC,
	0x001C4,
	0x001C7,
	0x001CA,
	0x001CD,
	0x001CF,
	0x001D1,
	0x001D3,
	0x001D5,
	0x001D7,
	0x001D9,
	0x001DB,
	0x001DE,
	0x001E0,
	0x001E2,
	0x001E4,
	0x001E6,
	0x001E8,
	0x001EA,
	0x001EC,
	0x001EE,
	0x001F1,
	0x001F4,
	0x001FA,
	0x001FC,
	0x001FE,
	0x00200,
	0x00202,
	0x00204,
	0x00206,
	0x00208,
	0x0020A,
	0x0020C,
	0x0020E,
	0x00210,
	0x00212,
	0x00214,
	0x00216,
	0x00218,
	0x0021A,
	0x0021C,
	0x0021E,
	0x00220,
	0x00222,
	0x00224,
	0x00226,
	0x00228,
	0x0022A,
	0x0022C,
	0x0022E,
	0x00230,
	0x00232,
	0x00241,
	0x00248,
	0x0024A,
	0x0024C,
	0x0024E,
	0x00370,
	0x00372,
	0x00376,
	0x0037F,
	0x00386,
	0x0038C,
	0x003CF,
	0x003D8,
	0x003DA,
	0x003DC,
	0x003DE,
	0x003E0,
	0x003E2,
	0x003E4,
	0x003E6,
	0x003E8,
	0x003EA,
	0x003EC,
	0x003EE,
	0x003F4,
	0x003F7,
	0x00460,
	0x00462,
	0x00464,
	0x00466,
	0x00468,
	0x0046A,
	0x0046C,
	0x0046E,
	0x00470,
	0x00472,
	0x00474,
	0x00476,
	0x00478,
	0x0047A,
	0x0047C,
	0x0047E,
	0x00480,
	0x0048A,
	0x0048C,
	0x0048E,
	0x00490,
	0x00492,
	0x00494,
	0x00496,
	0x00498,
	0x0049A,
	0x0049C,
	0x0049E,
	0x004A0,
	0x004A2,
	0x004A4,
	0x004A6,
	0x004A8,
	0x004AA,
	0x004AC,
	0x004AE,
	0x004B0,
	0x004B2,
	0x004B4,
	0x004B6,
	0x004B8,
	0x004BA,
	0x004BC,
	0x004BE,
	0x004C3,
	0x004C5,
	0x004C7,
	0x004C9,
	0x004CB,
	0x004CD,
	0x004D0,
	0x004D2,
	0x004D4,
	0x004D6,
	0x004D8,
	0x004DA,
	0x004DC,
	0x004DE,
	0x004E0,
	0x004E2,
	0x004E4,
	0x004E6,
	0x004E8,
	0x004EA,
	0x004EC,
	0x004EE,
	0x004F0,
	0x004F2,
	0x004F4,
	0x004F6,
	0x004F8,
	0x004FA,
	0x004FC,
	0x004FE,
	0x00500,
	0x00502,
	0x00504,
	0x00506,
	0x00508,
	0x0050A,
	0x0050C,
	0x0050E,
	0x00510,
	0x00512,
	0x00514,
	0x00516,
	0x00518,
	0x0051A,
	0x0051C,
	0x0051E,
	0x00520,
	0x00522,
	0x00524,
	0x00526,
	0x00528,
	0x0052A,
	0x0052C,
	0x0052E,
	0x010C7,
	0x010CD,
	0x01E00,
	0x01E02,
	0x01E04,
	0x01E06,
	0x01E08,
	0x01E0A,
	0x01E0C,
	0x01E0E,
	0x01E10,
	0x01E12,
	0x01E14,
	0x01E16,
	0x01E18,
	0x01E1A,
	0x01E1C,
	0x01E1E,
	0x01E20,
	0x01E22,
	0x01E24,
	0x01E26,
	0x01E28,
	0x01E2A,
	0x01E2C,
	0x01E2E,
	0x01E30,
	0x01E32,
	0x01E34,
	0x01E36,
	0x01E38,
	0x01E3A,
	0x01E3C,
	0x01E3E,
	0x01E40,
	0x01E42,
	0x01E44,
	0x01E46,
	0x01E48,
	0x01E4A,
	0x01E4C,
	0x01E4E,
	0x01E50,
	0x01E52,
	0x01E54,
	0x01E56,
	0x01E58,
	0x01E5A,
	0x01E5C,
	0x01E5E,
	0x01E60,
	0x01E62,
	0x01E64,
	0x01E66,
	0x01E68,
	0x01E6A,
	0x01E6C,
	0x01E6E,
	0x01E70,
	0x01E72,
	0x01E74,
	0x01E76,
	0x01E78,
	0x01E7A,
	0x01E7C,
	0x01E7E,
	0x01E80,
	0x01E82,
	0x01E84,
	0x01E86,
	0x01E88,
	0x01E8A,
	0x01E8C,
	0x01E8E,
	0x01E90,
	0x01E92,
	0x01E94,
	0x01E9E,
	0x01EA0,
	0x01EA2,
	0x01EA4,
	0x01EA6,
	0x01EA8,
	0x01EAA,
	0x01EAC,
	0x01EAE,
	0x01EB0,
	0x01EB2,
	0x01EB4,
	0x01EB6,
	0x01EB8,
	0x01EBA,
	0x01EBC,
	0x01EBE,
	0x01EC0,
	0x01EC2,
	0x01EC4,
	0x01EC6,
	0x01EC8,
	0x01ECA,
	0x01ECC,
	0x01ECE,
	0x01ED0,
	0x01ED2,
	0x01ED4,
	0x01ED6,
	0x01ED8,
	0x01EDA,
	0x01EDC,
	0x01EDE,
	0x01EE0,
	0x01EE2,
	0x01EE4,
	0x01EE6,
	0x01EE8,
	0x01EEA,
	0x01EEC,
	0x01EEE,
	0x01EF0,
	0x01EF2,
	0x01EF4,
	0x01EF6,
	0x01EF8,
	0x01EFA,
	0x01EFC,
	0x01EFE,
	0x01F59,
	0x01F5B,
	0x01F5D,
	0x01F5F,
	0x02102,
	0x02107,
	0x02115,
	0x02124,
	0x02126,
	0x02128,
	0x02145,
	0x02183,
	0x02C60,
	0x02C67,
	0x02C69,
	0x02C6B,
	0x02C72,
	0x02C75,
	0x02C82,
	0x02C84,
	0x02C86,
	0x02C88,
	0x02C8A,
	0x02C8C,
	0x02C8E,
	0x02C90,
	0x02C92,
	0x02C94,
	0x02C96,
	0x02C98,
	0x02C9A,
	0x02C9C,
	0x02C9E,
	0x02CA0,
	0x02CA2,
	0x02CA4,
	0x02CA6,
	0x02CA8,
	0x02CAA,
	0x02CAC,
	0x02CAE,
	0x02CB0,
	0x02CB2,
	0x02CB4,
	0x02CB6,
	0x02CB8,
	0x02CBA,
	0x02CBC,
	0x02CBE,
	0x02CC0,
	0x02CC2,
	0x02CC4,
	0x02CC6,
	0x02CC8,
	0x02CCA,
	0x02CCC,
	0x02CCE,
	0x02CD0,
	0x02CD2,
	0x02CD4,
	0x02CD6,
	0x02CD8,
	0x02CDA,
	0x02CDC,
	0x02CDE,
	0x02CE0,
	0x02CE2,
	0x02CEB,
	0x02CED,
	0x02CF2,
	0x0A640,
	0x0A642,
	0x0A644,
	0x0A646,
	0x0A648,
	0x0A64A,
	0x0A64C,
	0x0A64E,
	0x0A650,
	0x0A652,
	0x0A654,
	0x0A656,
	0x0A658,
	0x0A65A,
	0x0A65C,
	0x0A65E,
	0x0A660,
	0x0A662,
	0x0A664,
	0x0A666,
	0x0A668,
	0x0A66A,
	0x0A66C,
	0x0A680,
	0x0A682,
	0x0A684,
	0x0A686,
	0x0A688,
	0x0A68A,
	0x0A68C,
	0x0A68E,
	0x0A690,
	0x0A692,
	0x0A694,
	0x0A696,
	0x0A698,
	0x0A69A,
	0x0A722,
	0x0A724,
	0x0A726,
	0x0A728,
	0x0A72A,
	0x0A72C,
	0x0A72E,
	0x0A732,
	0x0A734,
	0x0A736,
	0x0A738,
	0x0A73A,
	0x0A73C,
	0x0A73E,
	0x0A740,
	0x0A742,
	0x0A744,
	0x0A746,
	0x0A748,
	0x0A74A,
	0x0A74C,
	0x0A74E,
	0x0A750,
	0x0A752,
	0x0A754,
	0x0A756,
	0x0A758,
	0x0A75A,
	0x0A75C,
	0x0A75E,
	0x0A760,
	0x0A762,
	0x0A764,
	0x0A766,
	0x0A768,
	0x0A76A,
	0x0A76C,
	0x0A76E,
	0x0A779,
	0x0A77B,
	0x0A780,
	0x0A782,
	0x0A784,
	0x0A786,
	0x0A78B,
	0x0A78D,
	0x0A790,
	0x0A792,
	0x0A796,
	0x0A798,
	0x0A79A,
	0x0A79C,
	0x0A79E,
	0x0A7A0,
	0x0A7A2,
	0x0A7A4,
	0x0A7A6,
	0x0A7A8,
	0x0A7B6,
	0x0A7B8,
	0x0A7BA,
	0x0A7BC,
	0x0A7BE,
	0x0A7C2,
	0x1D49C,
	0x1D4A2,
	0x1D546,
	0x1D7CA,
};

/* Lu */
int
c_utf8_isupper(ctype_rune r)
{
	if (UTF8_RANGESEARCH(&r, rangetab))
		return 1;
	if (UTF8_SEARCH(&r, tab))
		return 1;
	return 0;
}
