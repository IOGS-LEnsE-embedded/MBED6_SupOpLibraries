

void drawline(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)  
{  
    uint16_t dx, dy, p, x, y;  
    dx=x1-x0;  
    dy=y1-y0;  
    x=x0;  
    y=y0;  
    p=2*dy-dx;  
    while(x<x1)  
    {  
        if(p>=0)  
        {  
            this->draw_pixel(x, y, color);  
            y=y+1;  
            p=p+2*dy-2*dx;  
        }  
        else  
        {  
            this->draw_pixel(x, y, color);  
            p=p+2*dy;}  
            x=x+1;  
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


