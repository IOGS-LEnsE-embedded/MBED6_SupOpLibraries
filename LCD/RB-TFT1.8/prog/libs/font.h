/** 
 * ---------------------------------------------------------------+ 
 * @desc        FONTs
 * ---------------------------------------------------------------+ 
 *              Copyright (C) 2020 Marian Hrinko.
 *              Written by Marian Hrinko (mato.hrinko@gmail.com)
 *
 * @author      Marian Hrinko
 * @datum       07.10.2020
 * @file        font.h
 * @tested      AVR Atmega16
 *
 * @depend      
 * ---------------------------------------------------------------+
 */

#ifndef __FONT_H__
#define __FONT_H__

#include "mbed.h"

#define     MIN_ASCII_CHAR  0x20
#define     MAX_ASCII_CHAR  0x7F

#define CHARS_COLS_LEN        5                 // number of columns for chars
#define CHARS_ROWS_LEN        8                 // number of rows for chars


/** @enum Font sizes */
enum Size {
    // 1x 
    NORMAL = 1,
    // 2x 
    LARGE = 2,
    // 4x 
    HUGE = 4
};


  // Characters definition
  // -----------------------------------
  // number of columns for chars
  #define CHARS_COLS_LENGTH  5
  // @const Characters
  extern const uint8_t FONTS[][CHARS_COLS_LENGTH];

#endif
