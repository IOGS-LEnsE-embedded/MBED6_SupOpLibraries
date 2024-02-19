/**
 * FILENAME :        LCD_graphics.h         
 *
 * DESCRIPTION :
 *       Graphics core library for LCD display.
 *       LCD library must implement 
 *      - a **draw_pixel** method with parameters : 
 *          -> uint16_t x, uint16_t y, uint16_t color, 
 *          -> returns false if x and y are out of the range of the screen
 *      - a **check_range** method with parameters : 
 *          -> uint16_t x, uint16_t y
 *          -> returns false if x and y are out of the range of the screen
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    19/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#include "LCD_graphics.h"


bool    LCD_graphics::set_position (uint16_t x, uint16_t y)
{
    // check if coordinates is out of range
    if (!this->check_range(x, y)) { return  LCD_ERROR; } 
    // set position x and y
    this->__text_x = x;
    this->__text_y = y;
    return  LCD_SUCCESS;
}

bool 	LCD_graphics::draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)  
{  
    // check if coordinates is out of range
    if (!this->check_range(x0, y0)) { return    LCD_ERROR; }
    if (!this->check_range(x1, y1)) { return    LCD_ERROR; }

	// Bresenham's Algorithm
	// @see : https://www.baeldung.com/cs/bresenhams-line-algorithm
    int8_t      sx = 1;         // Sign of the x slope
    int8_t      sy = 1;         // Sign of the y slope
    int16_t     err = 0, e2;    // error
    int16_t     dx = x1 - x0;
    int16_t     dy = y1 - y0;

    if(dx < 0){ dx = -dx; }
    if(dy < 0){ dy = -dy; }
    if(x0 > x1) { sx = -1; }
    if(y0 > y1) { sy = -1; }

    err = dx - dy;
    this->draw_pixel(x0, y0, color);
    
    while((x0 != x1) || (y0 != y1)){
        e2 = err << 1;  // err * 2
        if(e2 > -dy){
            err -= dy;
            x0 += sx;
        }
        if(e2 < dx){
            err += dx;
            y0 += sy;
        }
        this->draw_pixel(x0, y0, color);
    }

	return	LCD_SUCCESS;
} 

bool 	LCD_graphics::draw_char(char character, uint16_t color, enum Size size)
{
	// variables
	uint8_t letter, idxCol, idxRow;
	// check if character is out of range
	if ((character < MIN_ASCII_CHAR) &&
		(character > MAX_ASCII_CHAR)) { 
		// out of range
		return LCD_ERROR;
	}
	
	// last column of character array - 5 columns 
	idxCol = CHARS_COLS_LEN;
	// last row of character array - 8 rows / bits
	idxRow = CHARS_ROWS_LEN;

	// ------------------------
	// SIZE X1 - normal font 1x
	// ------------------------
	if (size == NORMAL) {  
		// loop through 5 bits
		while (idxCol--) {
			// read from ROM memory 
			letter = FONTS[character - 0x20][idxCol];
			// loop through 8 bits
			while (idxRow--) {
				// check if bit set
				if (letter & (1 << idxRow)) {
					// draw pixel 
					this->draw_pixel(this->__text_x + idxCol, this->__text_y + idxRow, color);
				}
			}
			// fill index row again
			idxRow = CHARS_ROWS_LEN;
		}
		// update x position
		this->__text_x += CHARS_COLS_LEN + 1;
	/*
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
	
		*/
	}

	// return exit
	return LCD_SUCCESS;
}


bool 	LCD_graphics::draw_string(char *str, uint16_t color, enum Size size)
{
	// variables
	unsigned int i = 0;
	bool check;
	unsigned char delta_y;
	uint16_t max_x_pos;
	uint16_t max_y_pos;
	unsigned char new_x_pos;
	unsigned char new_y_pos;
	
	// Check if string size is in the range of the screen
	max_x_pos = this->__text_x + ((CHARS_COLS_LEN+1) * size);
	max_y_pos = this->__text_y + (CHARS_ROWS_LEN * size);
	// check if coordinates is out of range
    if (!this->check_range(max_x_pos, max_y_pos)) { return  LCD_ERROR; }

	// loop through character of string
	while (str[i] != '\0') {
		// read characters and increment index
		this->draw_char(str[i++], color, size);
	}
    return LCD_SUCCESS;
}




/*
void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    // stupidest version - update in subclasses if desired!
    for (int16_t i=x; i<x+w; i++)
        drawFastVLine(i, y, h, color); 
}
#endif

#if defined(GFX_WANT_ABSTRACTS)
// draw a rectangle
void Adafruit_GFX::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    drawFastHLine(x, y, w, color);
    drawFastHLine(x, y+h-1, w, color);
    drawFastVLine(x, y, h, color);
    drawFastVLine(x+w-1, y, h, color);
}
*/