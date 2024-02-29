/**
 * FILENAME :        st7735_constants.h          
 *
 * DESCRIPTION :
 *       LCD Joy-It OLED-0.96 - 0.96' LCD display - Library
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    29/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */
 
#ifndef __SSD1306_CONSTANTS_H__
#define __SSD1306_CONSTANTS_H__

  // Success / Error
  // -----------------------------------
  #define SSD1306_SUCCESS        true
  #define SSD1306_ERROR          false

#define 	SSD_I2C_FREQ		100000

#define     SSD_I2C_ADDRESS     0x78


  // Colors
  // -----------------------------------
  #define SSD1306_BLACK         0
  #define SSD1306_WHITE         1

  // AREA definition
  // -----------------------------------
  #define MAX_X                 128               // max columns / MV = 0 in MADCTL
  #define MAX_Y                 64                // max rows / MV = 0 in MADCTL
  #define SIZE_X                MAX_X - 1         // columns max counter
  #define SIZE_Y                MAX_Y - 1         // rows max counter
  #define CACHE_SIZE_MEM        (MAX_X * MAX_Y)   // whole pixels



#define SSD1306_SETCONTRAST         0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON        0xA5
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7
#define SSD1306_DISPLAYOFF          0xAE
#define SSD1306_DISPLAYON           0xAF
#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_SETLOWCOLUMN        0x00
#define SSD1306_SETHIGHCOLUMN       0x10
#define SSD1306_SETSTARTLINE        0x40
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_COMSCANINC          0xC0
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SEGREMAP            0xA0
#define SSD1306_CHARGEPUMP          0x8D

#endif