#pragma once

/* 32-bit and 64-bit check to keep MEM size same as LPVOID size. */
#ifdef _WIN64
    // 64-bit Windows
    #define MEM uint64_t
#else
    // 32-bit Windows
    #define MEM uint32_t
#endif


const int GAIA     = 0;
const int SOLARIAN = 1;
const int ANTARI   = 2;
const int SHINARI  = 3;
const int IBERON   = 4;
const int KRAHEN   = 5;
const int GODAN    = 6;
const int CHEBLON  = 7;
const int TOLUEN   = 8;
const int TRADERS  = 9;

const MEM MONEY_OFFSETS[9] = {
        0x7AD168,
        0x7AD170,
        0x7AD178,
        0x7AD180,
        0x7AD188,
        0x7AD190,
        0x7AD198,
        0x7AD1A0,
        0x7AD1A8,
};

const MEM CURRENT_RACE_OFFSET = 0x512A3C;
