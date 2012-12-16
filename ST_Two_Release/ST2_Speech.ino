/****************************************************************************\
*                                                                            *
* Solder Time II speech support                                              *
*                                                                            *
* by GoingDigital 2012                                                       *
*                                                                            *
* This is a hacked around version of the Talkie Speech Synthesis library,    *
* which is a software emulation of the 80's Texas Instruments speech chips,  *
* as used in Speak'n'Spell, TI99/4A, Acorn BBC Micro speech addon and others.*
*                                                                            *
* For more vocabulary, or an easy to use Arduino library version, check out  *
* http://github.com/GoingDigital                                             *
*                                                                            *
* Speech sounds here are extracts from the Acorn Computers BBC Microcomputer *
* Speech Synthesiser upgrade. This was famous at the time as the first ever  *
* computer voice with an english accent. It was voiced by Kenneth Kendall,   *
* a BBC newsreader of the era.                                               *
*                                                                            *
* Thanks to the MAME team for reverse engineering and documenting the        *
* Texas Instruments TMS5220 series devices.                                  *
*                                                                            *
* Talkie is designed for a 16MHz clocked device. Unfortunately SolderTime is *
* running at 8MHz, so the core synthesis code needs extra speed tweaks to    *
* achieve real-time synthesis.                                               *
\****************************************************************************/

// Speech vocabulary
// This data is in TMS5220 compressed format. Must be in PROGMEM.
//
// More speech segments with different voices are available from the Talkie library above.
//
uint8_t spONE[]       PROGMEM = {0xA6,0x90,0x76,0xCC,0x43,0x6B,0xB9,0x42,0xD8,0x35,0x77,0xA9,0x19,0x72,0xE5,0x46,0xD2,0x62,0x56,0xCB,0xAC,0x9F,0x68,0xE1,0x4E,0x23,0x09,0x71,0x23,0x55,0x3A,0x9E,0xB8,0xC4,0x4B,0x77,0x6D,0x74,0xE3,0x93,0x54,0x7B,0xE5,0x6E,0x2D,0x4F,0xD6,0xEC,0x56,0x84,0xB5,0x3A,0x45,0x0D,0x5D,0xA1,0xD6,0xA8,0xF4,0xC5,0x58,0x84,0x78,0xEC,0x34,0x64,0x6D,0x16,0xEA,0x8D,0xC2,0x90,0x95,0x66,0xB1,0x25,0x0E,0x43,0x92,0x1A,0x43,0x9E,0x26,0x0C,0x49,0x49,0xB4,0x78,0xEA,0x34,0x16,0x1B,0xA6,0xEA,0xB1,0xC9,0x24,0x82,0xBB,0x88,0xC8,0x06,0x00,0xF8,0x26};
uint8_t spTWO[]       PROGMEM = {0x0E,0x58,0x56,0xCB,0x00,0xD7,0xAB,0x19,0xE0,0x38,0xCB,0xE6,0x0C,0x65,0x8A,0x61,0xAD,0x86,0x9D,0xA5,0x79,0xA4,0x2D,0x1E,0x6E,0x61,0x69,0x9A,0xF6,0x79,0x04,0x85,0xA4,0x6B,0xC8,0xEF,0x16,0x17,0x94,0xA1,0xC1,0xBB,0x5B,0x5E,0x61,0x86,0x05,0x7E,0x0A,0xA5,0x0A,0x25,0xA6,0x75,0x3A,0x34,0x8E,0x5F,0xA8,0xEB,0x4B,0xD7,0x49,0xBB,0xE6,0x12,0x8F,0xDD,0xE0,0xC5,0x78,0xB2,0xBC,0x36,0x83,0x15,0xEB,0x2E,0xF2,0x48,0x0D,0x46,0x9E,0x89,0xE9,0x2B,0x31,0xC8,0x32,0x2C,0x9E,0xAB,0xFF,0x5A,0x26};
uint8_t spTHREE[]     PROGMEM = {0x08,0xA8,0xC2,0x8C,0x02,0x04,0x68,0x2A,0xDC,0xF9,0x51,0x5B,0x96,0x79,0x8D,0x10,0xE5,0xCA,0x2E,0x9A,0x76,0x72,0xD0,0xC2,0x5C,0x25,0x21,0x23,0xCD,0x0C,0x4F,0xD4,0x22,0x7A,0x46,0x34,0x3E,0xF1,0x48,0x86,0xD2,0xB1,0xEA,0x24,0x33,0x16,0x62,0xE7,0xAA,0x55,0xAC,0xD4,0x04,0xD5,0x8D,0x47,0xB3,0x53,0x33,0xE4,0x2C,0x69,0xED,0x4E,0x81,0x30,0x53,0xA7,0xF5,0xBB,0x14,0x43,0xF4,0x92,0x36,0xEC,0x92,0x04,0xD5,0x4B,0xD2,0xB8,0xAB,0x23,0xF4,0x34,0xCE,0x63,0x19,0x57,0x73,0x84,0xAE,0x26,0x69,0x9C,0x8D,0xC0,0xAB,0x6B,0x87,0xB1,0x7B,0x94,0x99,0x8A,0xF2,0x5A,0x66};
uint8_t spFOUR[]      PROGMEM = {0x08,0xA8,0xCA,0x94,0x00,0x5D,0x84,0x31,0x20,0xA9,0x0A,0x05,0x54,0x1D,0x16,0xBC,0xAA,0xDC,0xC3,0xC4,0xCE,0x0A,0x92,0xDA,0x94,0xA0,0x4D,0xC7,0x4F,0x7C,0xDA,0x0B,0x73,0x9F,0x20,0xAA,0x2D,0x73,0xCE,0x75,0x92,0x28,0xB7,0x23,0xD9,0xF7,0xCA,0x82,0xB9,0x16,0xD3,0x5C,0xA3,0x88,0x7A,0x2A,0x83,0x72,0x8D,0x2E,0xEA,0xED,0x08,0xCC,0xD3,0x86,0x68,0xB6,0xCD,0x29,0x77,0x19,0xA3,0xDE,0xD6,0xA0,0xDE,0x65,0x0C,0x66,0x5B,0x82,0x73,0x97,0x31,0xD8,0x2D,0x0B,0xEA,0x53,0xC6,0x10,0xB6,0x24,0xB8,0x77,0x99,0x42,0x98,0x4C,0xE5,0xDC,0x6E,0x0A,0xA3,0x4C,0xC3,0x17,0xFE,0x5A,0x16};
uint8_t spFIVE[]      PROGMEM = {0x08,0xE8,0xD2,0x15,0x03,0x02,0xA8,0x3A,0x5D,0x01,0x55,0x96,0x0E,0x3F,0xA5,0x70,0xE7,0x98,0xBD,0x82,0xDC,0xDB,0x5D,0xAD,0xD6,0x0A,0x4A,0xF8,0x70,0xF5,0x86,0x27,0x2E,0xFE,0xD3,0xC5,0x6B,0x9D,0xB4,0xE9,0xAB,0x94,0x68,0x78,0xAA,0xEA,0x2F,0xC3,0xA3,0xF1,0xE9,0x6A,0xD8,0x88,0xF0,0xD9,0xA7,0x6F,0x61,0xA2,0xDC,0x66,0xAF,0xBE,0x85,0xB6,0x34,0x9B,0xB5,0xFA,0xEE,0x5D,0xD2,0x73,0xCE,0xEA,0xBB,0x33,0x8A,0xAC,0x3A,0x63,0xE8,0x56,0x29,0xAB,0xAB,0x94,0xBE,0x67,0x45,0xCB,0x9E,0x5D,0xFA,0xE6,0x04,0xB3,0x72,0x76,0xEA,0x8A,0x26,0x6F,0xCF,0x29,0xA9,0x4D,0xCA,0x34,0x3D,0x6A,0xC7,0xC1,0x0F,0xFF,0x5A,0x56};
uint8_t spSIX[]       PROGMEM = {0x04,0xF8,0x82,0x8D,0x03,0x0A,0xF8,0xCA,0xDC,0x01,0x5F,0x79,0x28,0xE0,0xEB,0x30,0x05,0x7C,0xED,0xBE,0xBC,0xAD,0x8A,0x34,0x62,0xD5,0x0D,0x4E,0xB4,0xDC,0x12,0x87,0x77,0x1A,0xD5,0x28,0x09,0x1E,0xBE,0x24,0x36,0xA8,0x15,0xCA,0xDD,0x45,0x64,0x03,0x80,0x01,0xF2,0x54,0x31,0xC0,0x57,0x15,0x02,0xF8,0xCA,0x8C,0x01,0xDF,0x58,0x12,0xE0,0x1B,0x0B,0x04,0x7C,0x2F,0x86,0x80,0xEF,0xD4,0xFE,0x5A,0x36};
uint8_t spSEVEN[]     PROGMEM = {0x08,0xF8,0x5C,0x9D,0x01,0x5F,0x78,0x08,0xE0,0x8B,0x74,0x05,0x7C,0x15,0xAE,0x81,0x61,0x57,0x6B,0x9A,0xDC,0x75,0x8E,0xD7,0x6D,0x48,0x89,0x2F,0x3E,0x41,0x0B,0xED,0x29,0x3A,0xFB,0x44,0xD5,0xA7,0x87,0xDA,0xA2,0x96,0xC4,0x50,0x11,0xCA,0xB5,0x54,0xAD,0x65,0x6A,0x88,0xB8,0x6A,0x6D,0x0E,0x63,0xC6,0xD6,0xB8,0x8D,0xB9,0x46,0x38,0xD9,0xEC,0x34,0xE5,0xAC,0x45,0xBE,0x75,0xC2,0x94,0x84,0x78,0xBB,0x37,0xB6,0x93,0x9E,0xC8,0x24,0x82,0xBB,0x88,0xC8,0x06,0x00,0x80,0xFF,0x5A,0x76};
uint8_t spEIGHT[]     PROGMEM = {0x23,0x1E,0xC5,0x58,0x33,0xA7,0x9E,0xA0,0x6A,0xF1,0xAD,0x9E,0xB2,0xE2,0xEE,0x49,0xAB,0x3A,0xCA,0x2A,0x66,0x72,0x94,0xE9,0xDA,0xBB,0x0A,0xC3,0x30,0x8C,0xB5,0x1D,0x5B,0x4C,0x42,0xB9,0xBB,0x88,0x6C,0x00,0x00,0x01,0x5C,0x91,0x26,0x01,0x04,0x14,0x9F,0xFA,0x5A,0x0E};
uint8_t spNINE[]      PROGMEM = {0xA1,0x4A,0x4C,0xF4,0x31,0xDD,0x85,0x32,0x71,0xB6,0xC7,0x74,0x97,0x8A,0xCC,0x54,0x1F,0xCB,0x5D,0xC9,0x33,0x35,0x7D,0xCC,0xE4,0x2D,0x6B,0x20,0xF9,0x58,0xEB,0x9F,0xA4,0xCB,0x56,0x13,0x6F,0x74,0xE2,0xAE,0x37,0x5C,0x3D,0xD1,0x89,0x9B,0xBD,0x74,0xF1,0x44,0x27,0x69,0xE6,0xDA,0xD5,0x13,0x9D,0xB4,0xAB,0x9B,0x10,0x4F,0x74,0xF2,0x29,0x67,0xC2,0x3C,0xE5,0x29,0xA7,0xE9,0xAA,0x90,0x54,0xA7,0x9A,0xBE,0x3D,0x52,0x5A,0x9D,0x66,0xC5,0x51,0x49,0x6B,0x74,0xDA,0x95,0x46,0x30,0xA2,0xD1,0xE8,0x66,0x2E,0xE4,0xCA,0xCA,0x6D,0x58,0x21,0x89,0x3A,0x23,0x87,0x21,0x73,0xB5,0x71,0x4D,0x6A,0x86,0x20,0x2C,0xCE,0xCD,0x89,0x1A,0x82,0xB0,0x5C,0xB5,0x24,0x6A,0x08,0x22,0x2A,0x2D,0x3D,0xAB,0x3E,0x4A,0xAD,0x34,0xF3,0xF5,0x5A,0x4E};
uint8_t spTWEN_[]     PROGMEM = {0x01,0x98,0xC1,0xC2,0x00,0xCD,0x4E,0x28,0xA0,0xCC,0x8A,0xE2,0xC7,0xA2,0x6E,0x16,0x8D,0x8E,0x57,0xBC,0x4B,0xBA,0xAF,0x3E,0x7E,0x0F,0x45,0xE1,0xDA,0xF9,0x04,0xD3,0x35,0x85,0x7A,0xAB,0x13,0x75,0xE5,0xD4,0x16,0x89,0x46,0xDC,0x94,0xD0,0x51,0xD9,0x4D,0x69,0x56,0x1C,0xC5,0xA9,0x8C,0xD4,0x42,0xB9,0xBB,0x88,0x6C,0x80,0xFF,0x66};
uint8_t spTHIR_[]     PROGMEM = {0x08,0xC8,0x22,0x19,0x01,0x4D,0x05,0x0B,0xA0,0x73,0x17,0x03,0x74,0xE1,0x96,0x9C,0x69,0x92,0x4B,0xCC,0xF1,0x08,0xA3,0x77,0x1E,0xAF,0xB2,0xC7,0x2F,0xD6,0xB4,0x2C,0x2F,0x1F,0xBF,0x9B,0xE0,0x0C,0x79,0x7C,0x82,0x6E,0x92,0x3D,0x64,0xF5,0x09,0x7B,0x70,0x09,0xD3,0x39,0x27,0xAA,0x8E,0x23,0xBD,0xAA,0xA6,0xB4,0x39,0x56,0xD3,0xAC,0x85,0x40,0xA1,0xDC,0x5D,0x44,0x36,0xFC,0x16};
uint8_t spFOUR_[]     PROGMEM = {0x08,0xA8,0xCA,0x94,0x00,0x5D,0x84,0x31,0x20,0xA9,0x0A,0x05,0x54,0x1D,0x16,0xBC,0xAA,0xDC,0xC3,0xC4,0xCE,0x0A,0x92,0xDA,0x94,0xA0,0x4D,0xC7,0x4F,0x7C,0xDA,0x0B,0x73,0x9F,0x20,0xAA,0x2D,0x73,0xCE,0xB5,0x92,0x60,0xAE,0xC5,0x34,0xD7,0xC8,0xA2,0x9E,0xCA,0xA0,0x5C,0x2D,0x8B,0x66,0xDB,0x9C,0x72,0xA7,0x22,0x98,0x6D,0x09,0xCE,0x6D,0x8A,0x30,0xCA,0x34,0x7C,0xE1,0xFF,0x56};
uint8_t spFIF_[]      PROGMEM = {0x08,0x28,0xD4,0x14,0x03,0x06,0x68,0x2A,0x74,0x79,0xCD,0x30,0x75,0xFB,0xE4,0x13,0x4C,0x1D,0xC8,0x13,0xAB,0x4E,0xD0,0x9D,0x62,0x94,0x4F,0x29,0x51,0x53,0x4A,0x9E,0x3E,0x59,0x00,0x4D,0x98,0x28,0x60,0x99,0x54,0x0D,0x20,0x50,0x28,0x77,0x17,0x91,0x0D,0xF0,0x36};
uint8_t spSIX_[]      PROGMEM = {0x04,0xF8,0x82,0x8D,0x03,0x0A,0xF8,0xCA,0xDC,0x01,0x5F,0x79,0x28,0xE0,0x6B,0xF7,0xE5,0x6D,0x55,0xA4,0x11,0xAB,0x4E,0xB4,0xDC,0x12,0x87,0x77,0x0A,0xCD,0x28,0x09,0x1E,0xBE,0x04,0xB5,0x42,0xB9,0xBB,0x88,0x6C,0x00,0x06,0xE4,0xA9,0x22,0x80,0xAF,0xCC,0x08,0xF0,0x8D,0x25,0x06,0xFE,0x76};
uint8_t spSEVEN_[]    PROGMEM = {0x08,0xF8,0x5C,0x9D,0x01,0x5F,0x78,0x08,0xE0,0x8B,0x74,0x05,0x7C,0x15,0xAE,0x81,0x61,0x57,0x6B,0x9A,0xDC,0x75,0x4E,0xD0,0x42,0x7B,0x8A,0xCE,0xBE,0x41,0x4B,0x62,0xA8,0x08,0xE5,0x5A,0xAA,0xD6,0x32,0x35,0x44,0x5C,0xB5,0x36,0x87,0x31,0x63,0x6B,0xDC,0xDB,0x34,0xE6,0x1A,0xE1,0x64,0xB3,0xC3,0x94,0xB3,0x16,0xF9,0xD6,0x71,0x53,0x12,0xE2,0xED,0xDE,0xF8,0xFF,0x0E};
uint8_t spEIGH_[]     PROGMEM = {0x23,0x1E,0xC5,0x58,0x33,0xA7,0x9E,0xA0,0x6A,0xF1,0xAD,0x9E,0xB2,0xE2,0xEE,0x49,0xAB,0x3A,0xCA,0x2A,0x66,0x72,0x94,0xE9,0xDA,0xBB,0x0A,0xC3,0x30,0x8C,0xB5,0x1D,0x5B,0x4C,0x42,0xB9,0xBB,0x88,0x6C,0x00,0x80,0xFF,0x4E};
uint8_t spNINE_[]     PROGMEM = {0xA1,0x4A,0x4C,0xF4,0x31,0xDD,0x85,0x32,0x71,0xB6,0xC7,0x74,0x57,0xF2,0x4C,0x4D,0x1F,0x33,0x79,0xCB,0x1A,0x48,0x3E,0xD6,0xFA,0x27,0xE9,0xB2,0xD5,0xC4,0x1B,0x9D,0xB8,0xD9,0x4B,0x17,0x4F,0x74,0xD2,0xAE,0x6E,0x42,0x3C,0xD1,0x29,0xA7,0xE9,0xAA,0x90,0x54,0xA7,0x9A,0xBE,0x3D,0x52,0x5A,0x9D,0x66,0xC5,0x51,0x49,0x6B,0x74,0xDA,0x95,0x46,0x30,0xA2,0xD1,0xE8,0x66,0x2E,0xE4,0xCA,0xCA,0x6D,0x58,0x21,0x89,0x3A,0x23,0x87,0x21,0x73,0xB5,0x71,0x4D,0x6A,0x86,0x20,0x2C,0xCE,0xCD,0xC9,0xFF,0x41};
uint8_t sp_TEEN[]     PROGMEM = {0xA0,0x80,0x25,0x5C,0x14,0x70,0x5C,0x71,0x89,0x87,0x21,0xCA,0x19,0xDB,0x2D,0xE9,0x8E,0xA8,0x77,0xA2,0x8C,0x64,0x06,0x01,0xDF,0xAA,0x3C,0xEB,0xD6,0xAE,0xA4,0x20,0x3B,0xB3,0x4B,0x3F,0x12,0x48,0x5E,0xC5,0x29,0xC3,0x4C,0x48,0x76,0x5D,0xBB,0x0C,0x23,0xA2,0xC4,0x75,0xE4,0x32,0x64,0xAE,0x36,0xAE,0x49,0xC3,0x10,0x84,0xC5,0xB9,0x39,0x71,0x43,0x10,0x96,0xAB,0x96,0x44,0x0D,0x59,0x72,0x96,0x59,0x6A,0x31,0x74,0x19,0xE6,0x66,0xB6,0xFF,0x09,0x15,0x5A};
uint8_t sp_T[]        PROGMEM = {0x04,0x68,0x24,0xC4,0x01,0x07,0x44,0x1A,0xA0,0x42,0xE3,0xD1,0x0C,0x67,0x68,0x36,0xB5,0x5B,0x3F,0xBC,0x91,0x47,0xCD,0x49,0xD3,0x70,0x4A,0x91,0x35,0x3B,0x2F,0xFF,0x2D,0x5A};
uint8_t spOCLOCK[]    PROGMEM = {0x2B,0xAB,0xA6,0xC3,0x9D,0x37,0xAF,0x3C,0x87,0x0C,0x17,0x79,0xD5,0x8A,0x38,0x9D,0xDD,0x7A,0x16,0x2A,0x84,0x72,0x77,0x11,0xD9,0x00,0x00,0x06,0x28,0xA5,0x3B,0x00,0x5D,0x6B,0xA4,0x60,0x59,0x0D,0x09,0x55,0x32,0xBC,0xA4,0x35,0x4B,0xAD,0xD1,0x70,0x73,0xF6,0x16,0xD7,0x29,0x2B,0xCC,0xAD,0xCA,0x4D,0x67,0xAD,0x2C,0xF5,0xAE,0x50,0x9D,0x38,0x86,0xD4,0x3B,0x4B,0x65,0x65,0x98,0xD2,0x4B,0x75,0xF3,0xDA,0x64,0x12,0xCA,0xDD,0x45,0x64,0x03,0x00,0x00,0x28,0x20,0x15,0x23,0x02,0xE4,0xE4,0x8C,0x80,0x2C,0x07,0xFE,0x31,0x79};
uint8_t spO[]         PROGMEM = {0x2B,0xC9,0x21,0xCD,0x2C,0x1F,0xEE,0xE4,0xA4,0xC5,0x54,0x9A,0xE9,0xA6,0x9B,0xAE,0x2C,0xBB,0x4A,0x55,0xDB,0xB4,0xB3,0x95,0xA7,0xD4,0x2E,0xEA,0xAB,0x67,0xDE,0xF2,0x68,0xC7,0x4D,0x74,0x63,0x29,0x82,0x5E,0x4F,0xD4,0x9D,0xB9,0x08,0x95,0xB1,0xE7,0x2E,0xB6,0xD1,0x57,0xA6,0x52,0x69,0xD4,0xB5,0x16,0xAA,0xCA,0xB7,0x54,0xE1,0x1C,0xFD,0x69,0x61,0x79,0x19,0x61,0x72,0x79};
uint8_t spZERO[]      PROGMEM = {0xA2,0x2B,0x20,0x2D,0xAA,0x1A,0xAA,0xB6,0x81,0xD4,0x88,0x72,0xAC,0x80,0x8F,0xC4,0x34,0x90,0xAA,0x8F,0x44,0xD5,0x43,0x4D,0xCB,0x16,0x33,0x8C,0xB6,0x44,0x23,0x9A,0xDC,0x21,0xA7,0x6B,0xAD,0x60,0x28,0x83,0x9C,0x9E,0x75,0x82,0x69,0x12,0x74,0xB2,0xD1,0xF1,0x87,0x74,0xAA,0x89,0x46,0x27,0x18,0x36,0x39,0x5C,0x17,0x9D,0x60,0xA8,0x92,0x34,0x5B,0xB4,0xA2,0xA6,0xCA,0xD2,0x7D,0xD1,0x88,0x73,0xB6,0xF2,0xA8,0x96,0x23,0xCD,0x83,0x4D,0x23,0x5D,0xB7,0x2C,0x0F,0x74,0xF3,0xC8,0xDC,0x8A,0x5C,0xA9,0xA4,0x3B,0x55,0xAB,0x73,0xE5,0xE2,0x3A,0xD7,0x6D,0x2C,0x49,0x8B,0x3D,0x6F,0x95,0xB1,0x78,0x4D,0xD7,0x78,0x94,0xA6,0x64,0xC3,0x33,0xE2,0x52,0x9A,0x92,0x8D,0x08,0xF3,0x4B,0x61,0x4A,0x31,0xDC,0xB8,0x26,0xBB,0x25,0x05,0x77,0x95,0x7A,0xF4,0x06,0x06};
uint8_t spHUNDRED[]   PROGMEM = {0xA2,0x6D,0x76,0xD2,0x5D,0x1B,0xE9,0x62,0xFB,0xD7,0x3F,0x7E,0xB7,0x69,0x05,0x9E,0x7A,0x04,0x95,0xBB,0xAC,0x64,0xE2,0x11,0x35,0x9C,0x7C,0xE2,0x49,0x4A,0x1C,0xA5,0xC5,0x52,0xB9,0x0E,0x89,0xD5,0x56,0xA1,0x63,0x4B,0x16,0xA1,0x2D,0x21,0xCD,0x84,0x23,0x85,0xB6,0xD7,0x11,0x75,0x93,0xDD,0xDA,0x52,0x38,0xC9,0xAA,0x75,0xEB,0xB3,0xA3,0xF2,0xC8,0xC6,0xA5,0x2F,0x8E,0xCA,0x33,0x16,0x85,0xB1,0x58,0xAA,0xC8,0x6A,0x28,0xA6,0x2C,0x45,0xC3,0xB3,0x31,0x99,0x84,0x72,0x77,0x11,0xD9,0x60,0xA6,0x6D,0xDC,0xC5,0xD4,0xCD,0xFF,0x06,0x06,0x06};
uint8_t spTEN[]       PROGMEM = {0x0E,0x38,0xD4,0x53,0x01,0x8B,0x85,0x68,0x60,0x05,0xDD,0x29,0x5B,0xBA,0xE9,0x1B,0x9D,0x68,0xE6,0x62,0x73,0x6F,0x7C,0xA2,0x19,0x46,0x34,0xBC,0xD1,0x49,0x56,0x68,0xD1,0xB4,0xC5,0x27,0x1F,0x39,0xC5,0xCD,0x67,0x9F,0xB2,0x3B,0xD3,0x8C,0x9C,0x33,0x9A,0xEE,0x4C,0x5D,0x62,0x4E,0xEA,0xAB,0x61,0x4B,0x49,0xB9,0xA9,0xCF,0x4A,0xBC,0x34,0xED,0x84,0x21,0x69,0x4D,0xD7,0x74,0x15,0x86,0x24,0xDC,0xCA,0x4A,0xB1,0x1B,0x92,0x94,0x28,0x4B,0x55,0x6E,0x48,0x52,0xC2,0x33,0x55,0xFF,0x69,0x39,0x41,0x09,0x15};
uint8_t spELEVEN[]    PROGMEM = {0x25,0xED,0x5A,0x29,0x36,0xAB,0x8C,0xAC,0x1B,0xC3,0xD8,0x5A,0xB8,0xE2,0x41,0x5C,0xEC,0x32,0xD3,0x48,0x07,0x56,0xB5,0xB2,0x34,0x2D,0xA9,0xC0,0xC3,0x3A,0x56,0xB5,0xA4,0x80,0x08,0xED,0x6C,0xD5,0xE2,0x0E,0xDC,0xB9,0xA3,0xE5,0x09,0x06,0x77,0xEE,0xB4,0x45,0x27,0x1A,0xA2,0x34,0xD2,0x16,0x9D,0xA8,0xCB,0xB4,0x72,0x7F,0x74,0x92,0xAE,0xC7,0xDD,0x78,0x51,0xCB,0x4B,0x2C,0x0F,0x96,0xDA,0xA1,0x69,0xAA,0x2C,0x84,0x63,0xBB,0xB9,0xF1,0x52,0x57,0x4E,0x9C,0xC6,0x5C,0x23,0x9C,0x6C,0x76,0x98,0x72,0xD6,0x22,0xDF,0x3A,0x66,0x4A,0x42,0xBC,0xDD,0x1B,0xDB,0x09,0x8D,0x22,0xB8,0x8B,0x88,0x6C,0x00,0x80,0xFF,0x11,0x51,0x71,0x41,0x71,0x39,0x51};
uint8_t spTWELVE[]    PROGMEM = {0x06,0x58,0xCA,0xCC,0x00,0x4D,0x57,0x09,0xA0,0xC4,0x88,0xE4,0x85,0x1A,0x66,0xEA,0xAB,0x9A,0x1F,0x6B,0xAB,0x8B,0x6E,0x3A,0x7E,0x71,0xA3,0x6E,0xBC,0xF9,0x84,0xD5,0x8D,0xBA,0xCB,0xCA,0x13,0x35,0xD5,0xEA,0xA9,0x9B,0x4E,0xD2,0xED,0x78,0x18,0xAD,0x3A,0x45,0x0D,0xE5,0xC9,0xB6,0x7A,0x0C,0x25,0xB6,0x25,0xC5,0xED,0x32,0xE4,0xD6,0x16,0x54,0xB7,0xCB,0x9C,0x83,0x57,0x50,0x2D,0x2A,0x6B,0x76,0x9E,0x89,0xBE,0xAA,0x2C,0x29,0x64,0x18,0x59,0xEA,0xB2,0x24,0x9F,0x69,0xE8,0xA9,0xD3,0x12,0x8D,0x75,0xB1,0x75,0x4D,0x4B,0x8C,0x5E,0x46,0xD6,0x3A,0xCD,0xC1,0xB5,0x86,0xF8,0x66,0x04,0xB0,0x16,0x4A,0x80,0xA2,0xCB,0x10,0x50,0x55,0xDB,0xFF,0x51,0x05,0x4D,0x15};

// Speech parameter decoding tables
//
// These tables are used to decompress the bitstreams above into coeffients for the synthesis lattice filter.
//
// Note that K1 and K2 tables are truncated so the coefficients can be multiplied more quickly.
// See Talkie for higher precision tables.
//
uint8_t tmsEnergy[0x10] = {0x00,0x02,0x03,0x04,0x05,0x07,0x0a,0x0f,0x14,0x20,0x29,0x39,0x51,0x72,0xa1,0xff};
uint8_t tmsPeriod[0x40] = {0x00,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2D,0x2F,0x31,0x33,0x35,0x36,0x39,0x3B,0x3D,0x3F,0x42,0x45,0x47,0x49,0x4D,0x4F,0x51,0x55,0x57,0x5C,0x5F,0x63,0x66,0x6A,0x6E,0x73,0x77,0x7B,0x80,0x85,0x8A,0x8F,0x95,0x9A,0xA0};
int8_t tmsK1[0x20]     =  {0x83,0x84,0x84,0x84,0x85,0x85,0x86,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8F,0x91,0x93,0x99,0xA1,0xAC,0xB8,0xC7,0xD9,0xEC,0x00,0x14,0x27,0x39,0x48,0x55,0x5F,0x67,0x6D};
int8_t tmsK2[0x20]     =  {0xAE,0xB5,0xBC,0xC3,0xCC,0xD4,0xDE,0xE8,0xF2,0xFC,0x06,0x10,0x1A,0x24,0x2D,0x36,0x3E,0x46,0x4D,0x53,0x59,0x5E,0x62,0x66,0x6A,0x6D,0x70,0x72,0x74,0x76,0x77,0x7F};
int8_t tmsK3[0x10]      = {0x92,0x9F,0xAD,0xBA,0xC8,0xD5,0xE3,0xF0,0xFE,0x0B,0x19,0x26,0x34,0x41,0x4F,0x5C};
int8_t tmsK4[0x10]      = {0xAE,0xBC,0xCA,0xD8,0xE6,0xF4,0x01,0x0F,0x1D,0x2B,0x39,0x47,0x55,0x63,0x71,0x7E};
int8_t tmsK5[0x10]      = {0xAE,0xBA,0xC5,0xD1,0xDD,0xE8,0xF4,0xFF,0x0B,0x17,0x22,0x2E,0x39,0x45,0x51,0x5C};
int8_t tmsK6[0x10]      = {0xC0,0xCB,0xD6,0xE1,0xEC,0xF7,0x03,0x0E,0x19,0x24,0x2F,0x3A,0x45,0x50,0x5B,0x66};
int8_t tmsK7[0x10]      = {0xB3,0xBF,0xCB,0xD7,0xE3,0xEF,0xFB,0x07,0x13,0x1F,0x2B,0x37,0x43,0x4F,0x5A,0x66};
int8_t tmsK8[0x08]      = {0xC0,0xD8,0xF0,0x07,0x1F,0x37,0x4F,0x66};
int8_t tmsK9[0x08]      = {0xC0,0xD4,0xE8,0xFC,0x10,0x25,0x39,0x4D};
int8_t tmsK10[0x08]     = {0xCD,0xDF,0xF1,0x04,0x16,0x20,0x3B,0x4D};

// Voiced formant excitation signal
//
// This is the sound of one cycle of the simulated vocal chords.
#define CHIRP_SIZE 41
int8_t chirp[CHIRP_SIZE] = {0x00,0x2a,0xd4,0x32,0xb2,0x12,0x25,0x14,0x02,0xe1,0xc5,0x02,0x5f,0x5a,0x05,0x0f,0x26,0xfc,0xa5,0xa5,0xd6,0xdd,0xdc,0xfc,0x25,0x2b,0x22,0x21,0x0f,0xff,0xf8,0xee,0xed,0xef,0xf7,0xf6,0xfa,0x00,0x03,0x02,0x01};

// Synthesis parameters
//
uint8_t synthPeriod;
uint16_t synthEnergy;
int16_t synthK1,synthK2;
int8_t synthK3,synthK4,synthK5,synthK6,synthK7,synthK8,synthK9,synthK10;
uint8_t talkieSetup = 0;
uint8_t* ptrAddr;
uint8_t ptrBit;


/////////////////
// Say the time
/////////////////
//
void sayTime() {
  // Get the current time
  //
  checktime();
  int hours = HourTens * 10 + HourOnes;
  int minutes = MinTens * 10 + MinOnes;

  // We need to shut down the LED matrix, because:
  //  1) We need as many CPU cycles as we can get for all the synthesis maths
  //  2) We need Timer 1 as a timebase for our synthesis
  //  3) Don't want to burn out any LEDs by leaving them on.
  //
  Timer1.detachInterrupt();
  // Force LEDs off
  PORTC |= B00001111;
  PORTB = B11111111;
  PORTD |= B11110000;

  // Prep speech synth audio output
  //
  Timer1.initialize(125); // 8kHz sample rate
  Timer1.attachInterrupt(talkieInterruptHandler); 

  // This part converts the time into speech segments
  // You may need to alter this if you're using another voice or different speech segments.
  //
  // Most pronounciations have zero as a special case ('o'clock', 'zero', 'oh' or 'hundred'),
  // so sayNum() accepts a zero value parameter.
  //
  // 
  if (TH_Not24_flag) {
    // 12 hour pronunciation
    //
    // 12:00 => twelve o'clock
    // 12:03 => twelve oh three
    // 11:59 => eleven fifty-nine
    //
    sayNum(hours,spZERO);
    if (minutes > 0 && minutes < 10) talkieSay(spO);
    sayNum(minutes,spOCLOCK);
  } else {
    // 24 hour pronunciation
    //
    // 00:00 => zero hundred
    // 00:03 => zero oh three
    // 23:59 => twenty-three fifty-nine
    //
    sayNum(hours,spZERO);
    if (minutes > 0 && minutes < 10) talkieSay(spO);
    sayNum(minutes,spHUNDRED);
  }

  talkieEnd();
  // Speech is complete, so shut down audio system
  Timer1.detachInterrupt();

  // Fix up pin 3 state
  #if ARDUINO >= 101 
  pinMode(3, INPUT_PULLUP);
  #else
  digitalWrite(3, HIGH);
  pinMode(3, INPUT);
  #endif

  // Redirect timer1 back to LED matrix
  //
  Timer1.initialize(100);
  Timer1.attachInterrupt(LEDupdateTWO);   
}

// Say a single number, with english pronounciation rules.
// 0 is pronounced different ways in different contexts,
// so this is handled as a special case.
//
void sayNum(int number,uint8_t* zero_phrase) {
  if (number==0) {
    talkieSay(zero_phrase);
  } else {
    if (number>=50) { talkieSay(spFIF_); talkieSay(sp_T); number-=50; }
    if (number>=40) { talkieSay(spFOUR_); talkieSay(sp_T); number-=40; }
    if (number>=30) { talkieSay(spTHIR_); talkieSay(sp_T); number-=30; }
    if (number>=20) { talkieSay(spTWEN_); talkieSay(sp_T); number-=20; }
    switch (number) {
      case 19: talkieSay(spNINE_); talkieSay(sp_TEEN); break;
      case 18: talkieSay(spEIGH_); talkieSay(sp_TEEN); break;
      case 17: talkieSay(spSEVEN_); talkieSay(sp_TEEN); break;
      case 16: talkieSay(spSIX_); talkieSay(sp_TEEN); break;
      case 15: talkieSay(spFIF_); talkieSay(sp_TEEN); break;
      case 14: talkieSay(spFOUR_); talkieSay(sp_TEEN); break;
      case 13: talkieSay(spTHIR_); talkieSay(sp_TEEN); break;
      case 12: talkieSay(spTWELVE); break;
      case 11: talkieSay(spELEVEN); break;
      case 10: talkieSay(spTEN); break;
      case 9: talkieSay(spNINE); break;
      case 8: talkieSay(spEIGHT); break;
      case 7: talkieSay(spSEVEN); break;
      case 6: talkieSay(spSIX); break;
      case 5: talkieSay(spFIVE); break;
      case 4: talkieSay(spFOUR); break;
      case 3: talkieSay(spTHREE); break;
      case 2: talkieSay(spTWO); break;
      case 1: talkieSay(spONE); break;
      default: break; // Say nothing more for numbers like 20 or 50
    }
  }
}



void talkieSetPtr(uint8_t* addr) {
  ptrAddr = addr;
  ptrBit = 0;
}

// The ROMs used with the TI speech were serial, not byte wide.
// Here's a handy routine to flip ROM data which is usually reversed.
uint8_t talkieRev(uint8_t a) {
  // 76543210
  a = (a>>4) | (a<<4); // Swap in groups of 4
  // 32107654
  a = ((a & 0xcc)>>2) | ((a & 0x33)<<2); // Swap in groups of 2
  // 10325476
  a = ((a & 0xaa)>>1) | ((a & 0x55)<<1); // Swap bit pairs
  // 01234567
  return a;
}
uint8_t talkieGetBits(uint8_t bits) {
  uint8_t value;
  uint16_t data;
  data = talkieRev(pgm_read_byte(ptrAddr))<<8;
  if (ptrBit+bits > 8) {
    data |= talkieRev(pgm_read_byte(ptrAddr+1));
  }
  data <<= ptrBit;
  value = data >> (16-bits);
  ptrBit += bits;
  if (ptrBit >= 8) {
    ptrBit -= 8;
    ptrAddr++;
  }
  return value;
}
void talkieBegin() {
    // Auto-setup.
    // 
    // Enable the speech system whenever say() is called.

    pinMode(3,OUTPUT);
    // Timer 2 set up as fast-as-possible PWM.
    //
    // 78.125kHz on 20MHz Arduino
    // 62.5kHz on 16MHz Arduino
    // 31.25kHz on 8MHz Arduino
    //
    // The PWM 'buzz' is well above human hearing range and is
    // very easy to filter out.
    //
    TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS20);
    TIMSK2 = 0;

    // Unfortunately we can't calculate the next sample every PWM cycle
    // as the routine is too slow. So use Timer 1 to trigger that.

    // Timer 1 set up as a 8000Hz sample interrupt
    talkieSetup = 1;
}
void talkieEnd() {
    TCCR2A = 0;
    TCCR2B = 0;
    TIMSK2 = 0;

    // Unfortunately we can't calculate the next sample every PWM cycle
    // as the routine is too slow. So use Timer 1 to trigger that.

    // Timer 1 set up as a 8000Hz sample interrupt
    talkieSetup = 0;
}
void talkieSay(uint8_t* addr) {
  uint8_t energy;

  if (!talkieSetup) talkieBegin();

  talkieSetPtr(addr);
  do {
    uint8_t repeat;

    // Read speech data, processing the variable size frames.
    
    energy = talkieGetBits(4);
    if (energy == 0) {
      // Energy = 0: rest frame
      synthEnergy = 0;
    } else if (energy == 0xf) {
      // Energy = 15: stop frame. Silence the synthesiser.
      synthEnergy = 0;
      synthK1 = 0;
      synthK2 = 0;
      synthK3 = 0;
      synthK4 = 0;
      synthK5 = 0;
      synthK6 = 0;
      synthK7 = 0;
      synthK8 = 0;
      synthK9 = 0;
      synthK10 = 0;
    } else {
      synthEnergy = tmsEnergy[energy];
      repeat = talkieGetBits(1);
      synthPeriod = tmsPeriod[talkieGetBits(6)];
      // A repeat frame uses the last coefficients
      if (!repeat) {
        // All frames use the first 4 coefficients
        synthK1 = tmsK1[talkieGetBits(5)];
        synthK2 = tmsK2[talkieGetBits(5)];
        synthK3 = tmsK3[talkieGetBits(4)];
        synthK4 = tmsK4[talkieGetBits(4)];
        if (synthPeriod) {
          // Voiced frames use 6 extra coefficients.
          synthK5 = tmsK5[talkieGetBits(4)];
          synthK6 = tmsK6[talkieGetBits(4)];
          synthK7 = tmsK7[talkieGetBits(4)];
          synthK8 = tmsK8[talkieGetBits(3)];
          synthK9 = tmsK9[talkieGetBits(3)];
          synthK10 = tmsK10[talkieGetBits(3)];
        }
      }
    }
    delay(25);
  } while (energy != 0xf);
}


void talkieInterruptHandler(){
  static uint8_t nextPwm;
  static uint8_t periodCounter;
  static int16_t x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10;
  int16_t u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10;

  OCR2B = nextPwm;
  if (synthPeriod) {
    // Voiced source
    if (periodCounter < synthPeriod) {
      periodCounter++;
    } else {
      periodCounter = 0;
    }
    if (periodCounter < CHIRP_SIZE) {
      u10 = ((chirp[periodCounter]) * (uint32_t) synthEnergy) >> 8;
    } else {
      u10 = 0;
    }
  } else {
    // Unvoiced source
    static uint16_t synthRand = 1;
    synthRand = (synthRand >> 1) ^ ((synthRand & 1) ? 0xB800 : 0);
    u10 = (synthRand & 1) ? synthEnergy : -synthEnergy;
  }
  // Lattice filter forward path
  u9 = u10 - (((int16_t)synthK10*x9) >> 7);
  u8 = u9 - (((int16_t)synthK9*x8) >> 7);
  u7 = u8 - (((int16_t)synthK8*x7) >> 7);
  u6 = u7 - (((int16_t)synthK7*x6) >> 7);
  u5 = u6 - (((int16_t)synthK6*x5) >> 7);
  u4 = u5 - (((int16_t)synthK5*x4) >> 7);
  u3 = u4 - (((int16_t)synthK4*x3) >> 7);
  u2 = u3 - (((int16_t)synthK3*x2) >> 7);
  u1 = u2 - (((int16_t)synthK2*x1) >> 7); // K1 and K2 should be calculated with higher precision,
  u0 = u1 - (((int16_t)synthK1*x0) >> 7); // but this is a speed shortcut.

  // Output clamp
  if (u0 > 511) u0 = 511;
  if (u0 < -512) u0 = -512;
  
  // Lattice filter reverse path
  x9 = x8 + (((int16_t)synthK9*u8) >> 7);
  x8 = x7 + (((int16_t)synthK8*u7) >> 7);
  x7 = x6 + (((int16_t)synthK7*u6) >> 7);
  x6 = x5 + (((int16_t)synthK6*u5) >> 7);
  x5 = x4 + (((int16_t)synthK5*u4) >> 7);
  x4 = x3 + (((int16_t)synthK4*u3) >> 7);
  x3 = x2 + (((int16_t)synthK3*u2) >> 7);
  x2 = x1 + (((int16_t)synthK2*u1) >> 7);
  x1 = x0 + (((int16_t)synthK1*u0) >> 7);
  x0 = u0;

  nextPwm = (u0>>2)+0x80;
}
