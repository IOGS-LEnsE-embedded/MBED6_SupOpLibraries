

/**
 * @desc    Draw character
 *
 * @param   struct st7735 *
 * @param   char character
 * @param   uint16_t color
 * @param   enum Size (X1, X2, X3)
 *
 * @return  void
 */
char ST7735_DrawChar (struct st7735 * lcd, char character, uint16_t color, enum Size size)
{
  // variables
  uint8_t letter, idxCol, idxRow;
  // check if character is out of range
  if ((character < 0x20) &&
      (character > 0x7f)) { 
    // out of range
    return 0;
  }
  // last column of character array - 5 columns 
  idxCol = CHARS_COLS_LEN;
  // last row of character array - 8 rows / bits
  idxRow = CHARS_ROWS_LEN;

  // --------------------------------------
  // SIZE X1 - normal font 1x high, 1x wide
  // --------------------------------------
  if (size == X1) {  
    // loop through 5 bits
    while (idxCol--) {
      // read from ROM memory 
      letter = pgm_read_byte (&FONTS[character - 32][idxCol]);
      // loop through 8 bits
      while (idxRow--) {
        // check if bit set
        if (letter & (1 << idxRow)) {
          // draw pixel 
          ST7735_DrawPixel (lcd, cacheMemIndexCol + idxCol, cacheMemIndexRow + idxRow, color);
        }
      }
      // fill index row again
      idxRow = CHARS_ROWS_LEN;
    }
    // update x position
    cacheMemIndexCol = cacheMemIndexCol + CHARS_COLS_LEN + 1;
  
  // --------------------------------------
  // SIZE X2 - font 2x higher, normal wide
  // --------------------------------------
  } else if (size == X2) {
    // loop through 5 bytes
    while (idxCol--) {
      // read from ROM memory 
      letter = pgm_read_byte (&FONTS[character - 32][idxCol]);
      // loop through 8 bits
      while (idxRow--) {
        // check if bit set
        if (letter & (1 << idxRow)) {
          // draw first left up pixel; 
          // (idxRow << 1) - 2x multiplied 
          ST7735_DrawPixel (lcd, cacheMemIndexCol + idxCol, cacheMemIndexRow + (idxRow << 1), color);
          // draw second left down pixel
          ST7735_DrawPixel (lcd, cacheMemIndexCol + idxCol, cacheMemIndexRow + (idxRow << 1) + 1, color);
        }
      }
      // fill index row again
      idxRow = CHARS_ROWS_LEN;
    }
    // update x position
    cacheMemIndexCol = cacheMemIndexCol + CHARS_COLS_LEN + 1;

  // --------------------------------------
  // SIZE X3 - font 2x higher, 2x wider
  // --------------------------------------
  } else if (size == X3) {
    // loop through 5 bytes
    while (idxCol--) {
      // read from ROM memory 
      letter = pgm_read_byte (&FONTS[character - 32][idxCol]);
      // loop through 8 bits
      while (idxRow--) {
        // check if bit set
        if (letter & (1 << idxRow)) {
          // draw first left up pixel; 
          // (idxRow << 1) - 2x multiplied 
          ST7735_DrawPixel (lcd, cacheMemIndexCol + (idxCol << 1), cacheMemIndexRow + (idxRow << 1), color);
          // draw second left down pixel
          ST7735_DrawPixel (lcd, cacheMemIndexCol + (idxCol << 1), cacheMemIndexRow + (idxRow << 1) + 1, color);
          // draw third right up pixel
          ST7735_DrawPixel (lcd, cacheMemIndexCol + (idxCol << 1) + 1, cacheMemIndexRow + (idxRow << 1), color);
          // draw fourth right down pixel
          ST7735_DrawPixel (lcd, cacheMemIndexCol + (idxCol << 1) + 1, cacheMemIndexRow + (idxRow << 1) + 1, color);
        }
      }
      // fill index row again
      idxRow = CHARS_ROWS_LEN;
    }

    // update x position
    cacheMemIndexCol = cacheMemIndexCol + CHARS_COLS_LEN + CHARS_COLS_LEN + 1;
  }

  // return exit
  return ST7735_SUCCESS;
}

/**
 * @desc    Set text position x, y
 *
 * @param   uint8_t x - position
 * @param   uint8_t y - position
 *
 * @return  char
 */
char ST7735_SetPosition (uint8_t x, uint8_t y)
{
  // check if coordinates is out of range
  if ((x > MAX_X) && (y > MAX_Y)) {
    // error
    return ST7735_ERROR;

  } else if ((x > MAX_X) && (y <= MAX_Y)) {
    // set position y
    cacheMemIndexRow = y;
    // set position x
    cacheMemIndexCol = 2;
  } else {
    // set position y 
    cacheMemIndexRow = y;
    // set position x
    cacheMemIndexCol = x;
  }
  // success
  return ST7735_SUCCESS;
}

/**
 * @desc    Check text position x, y
 *
 * @param   unsigned char x - position
 * @param   unsigned char y - position
 * @param   unsigned char
 *
 * @return  char
 */
char ST7735_CheckPosition (unsigned char x, unsigned char y, unsigned char max_y, enum Size size)
{
  // check if coordinates is out of range
  if ((x > MAX_X) && (y > max_y)) {
    // out of range
    return ST7735_ERROR;

  }
  // if next line
  if ((x > MAX_X) && (y <= max_y)) {
    // set position y
    cacheMemIndexRow = y;
    // set position x
    cacheMemIndexCol = 2;
  } 

  // success
  return ST7735_SUCCESS;
}

/**
 * @desc    Draw string
 *
 * @param   struct st7735 *
 * @param   char * string 
 * @param   uint16_t color
 * @param   enum Size (X1, X2, X3)
 *
 * @return  void
 */
void ST7735_DrawString (struct st7735 * lcd, char *str, uint16_t color, enum Size size)
{
  // variables
  unsigned int i = 0;
  unsigned char check;
  unsigned char delta_y;
  unsigned char max_y_pos;
  unsigned char new_x_pos;
  unsigned char new_y_pos;

  // loop through character of string
  while (str[i] != '\0') {
    // max x position character
    new_x_pos = cacheMemIndexCol + CHARS_COLS_LEN + (size & 0x0F);
    // delta y
    delta_y = CHARS_ROWS_LEN + (size >> 4);
    // max y position character
    new_y_pos = cacheMemIndexRow + delta_y;
    // max y pos
    max_y_pos = MAX_Y - delta_y;
    // control if will be in range
    check = ST7735_CheckPosition (new_x_pos, new_y_pos, max_y_pos, size);
    // update position
    if (ST7735_SUCCESS == check) {
      // read characters and increment index
      ST7735_DrawChar (lcd, str[i++], color, size);
    }
  }
}

/**
 * @desc    Draw line by Bresenham algoritm
 * @surce   https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *  
 * @param   struct st7735 *
 * @param   uint8_t x start position / 0 <= cols <= MAX_X-1
 * @param   uint8_t x end position   / 0 <= cols <= MAX_X-1
 * @param   uint8_t y start position / 0 <= rows <= MAX_Y-1 
 * @param   uint8_t y end position   / 0 <= rows <= MAX_Y-1
 * @param   uint16_t color
 *
 * @return  void
 */
char ST7735_DrawLine (struct st7735 * lcd, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2, uint16_t color)
{
  // determinant
  int16_t D;
  // deltas
  int16_t delta_x, delta_y;
  // steps
  int16_t trace_x = 1, trace_y = 1;

  // delta x
  delta_x = x2 - x1;
  // delta y
  delta_y = y2 - y1;

  // check if x2 > x1
  if (delta_x < 0) {
    // negate delta x
    delta_x = -delta_x;
    // negate step x
    trace_x = -trace_x;
  }

  // check if y2 > y1
  if (delta_y < 0) {
    // negate detla y
    delta_y = -delta_y;
    // negate step y
    trace_y = -trace_y;
  }

  // Bresenham condition for m < 1 (dy < dx)
  if (delta_y < delta_x) {
    // calculate determinant
    D = (delta_y << 1) - delta_x;
    // draw first pixel
    ST7735_DrawPixel (lcd, x1, y1, color);
    // check if x1 equal x2
    while (x1 != x2) {
      // update x1
      x1 += trace_x;
      // check if determinant is positive
      if (D >= 0) {
        // update y1
        y1 += trace_y;
        // update determinant
        D -= 2*delta_x;    
      }
      // update deteminant
      D += 2*delta_y;
      // draw next pixel
      ST7735_DrawPixel (lcd, x1, y1, color);
    }
  // for m > 1 (dy > dx)    
  } else {
    // calculate determinant
    D = delta_y - (delta_x << 1);
    // draw first pixel
    ST7735_DrawPixel (lcd, x1, y1, color);
    // check if y2 equal y1
    while (y1 != y2) {
      // update y1
      y1 += trace_y;
      // check if determinant is positive
      if (D <= 0) {
        // update y1
        x1 += trace_x;
        // update determinant
        D += 2*delta_y;    
      }
      // update deteminant
      D -= 2*delta_x;
      // draw next pixel
      ST7735_DrawPixel (lcd, x1, y1, color);
    }
  }
  // success return
  return 1;
}

/**
 * @desc    Fast draw line horizontal
 *
 * @param   struct st7735 *
 * @param   uint8_t xs - start position
 * @param   uint8_t xe - end position
 * @param   uint8_t y - position
 * @param   uint16_t color
 *
 * @return void
 */
void ST7735_DrawLineHorizontal (struct st7735 * lcd, uint8_t xs, uint8_t xe, uint8_t y, uint16_t color)
{
  uint8_t temp;
  // check if start is > as end  
  if (xs > xe) {
    // temporary safe
    temp = xs;
    // start change for end
    xe = xs;
    // end change for start
    xs = temp;
  }
  // set window
  ST7735_SetWindow (lcd, xs, xe, y, y);
  // draw pixel by 565 mode
  ST7735_SendColor565 (lcd, color, xe - xs);
}

/**
 * @desc    Fast draw line vertical
 *
 * @param   struct st7735 *
 * @param   uint8_t x - position
 * @param   uint8_t ys - start position
 * @param   uint8_t ye - end position
 * @param   uint16_t color
 *
 * @return  void
 */
void ST7735_DrawLineVertical (struct st7735 * lcd, uint8_t x, uint8_t ys, uint8_t ye, uint16_t color)
{
  uint8_t temp;
  // check if start is > as end
  if (ys > ye) {
    // temporary safe
    temp = ys;
    // start change for end
    ye = ys;
    // end change for start
    ys = temp;
  }
  // set window
  ST7735_SetWindow (lcd, x, x, ys, ye);
  // draw pixel by 565 mode
  ST7735_SendColor565 (lcd, color, ye - ys);
}

/**
 * @desc    Draw rectangle
 *
 * @param   struct st7735 *
 * @param   uint8_t x start position
 * @param   uint8_t x end position
 * @param   uint8_t y start position
 * @param   uint8_t y end position
 * @param   uint16_t color
 *
 * @return  void
 */
void ST7735_DrawRectangle (struct st7735 * lcd, uint8_t xs, uint8_t xe, uint8_t ys, uint8_t ye, uint16_t color)
{
  uint8_t temp;
  // check if start is > as end  
  if (xs > xe) {
    // temporary safe
    temp = xe;
    // start change for end
    xe = xs;
    // end change for start
    xs = temp;
  }
  // check if start is > as end
  if (ys > ye) {
    // temporary safe
    temp = ye;
    // start change for end
    ye = ys;
    // end change for start
    ys = temp;
  }
  // set window
  ST7735_SetWindow (lcd, xs, xe, ys, ye);
  // send color
  ST7735_SendColor565 (lcd, color, (xe-xs+1)*(ye-ys+1));  
}


