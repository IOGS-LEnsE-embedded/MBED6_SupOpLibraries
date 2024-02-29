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

 
#ifndef __LCD_GRAPHICS_H__
#define __LCD_GRAPHICS_H__

#include "mbed.h"
#include "font.h"
#include <cstdint>

#define LCD_SUCCESS        true
#define LCD_ERROR          false


/**
 * @class LCD_graphics
 * @brief 	Graphics core class for LCD Display
 * @details  LCD library must implement 
 *      - a **draw_pixel** method with parameters : 
 *          -> uint16_t x, uint16_t y, uint16_t color, 
 *          -> returns false if x and y are out of the range of the screen
 *      - a **check_range** method with parameters : 
 *          -> uint16_t x, uint16_t y
 *          -> returns false if x and y are out of the range of the screen
 */

class LCD_graphics {
    public:

		/**
		 * @brief    Draw a pixel at a specific position
		 * @param x - uint16_t - x position / 0 <= cols <= MAX_X-1
		 * @param y - uint16_t - y position / 0 <= rows <= MAX_Y-1
		 * @param color - uint16_t - Color in 16 bits mode
         * @return  false if x and y are out of range
		 */
        virtual bool    draw_pixel(uint16_t x, uint16_t y, uint16_t color);

		/**
        * @brief Check if the coordinates are in the range of the screen size
		* @param x  uint16_t - coordinate on X axis
		* @param y 	uint16_t - coordinate on Y axis
		* @return true if is in the range of the screen size
		*/
        virtual bool    check_range(uint16_t x, uint16_t y);
		
        /**
		 * @param x - uint16_t - coordinate on X axis
		 * @param y - uint16_t - coordinate on Y axis
		 * @return true if is in the range of the screen size
		 */		
        bool    set_position(uint16_t x, uint16_t y);

		/**
		 * @brief    Draw a line using Bresenham's Algorithm
		 * @param x0 - uint16_t - x0 position of the first point of the line
		 * @param y0 - uint16_t - y0 position of the first point of the line
		 * @param x1 - uint16_t - x1 position of the first point of the line
		 * @param y1 - uint16_t - y1 position of the first point of the line
		 * @param color - uint16_t - Color in 16 bits mode
         * @return  false if x0,y0 and x1,y1 are out of range
		 */		
		bool 	draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
        
        /**
		 * @brief    Draw a rectangle using its top-left corner and its dimension
		 * @param x - uint16_t - x position of the top-left corner of the rectangle
		 * @param y - uint16_t - y position of the top-left corner of the rectangle
		 * @param w - uint16_t - width of the rectangle
		 * @param h - uint16_t - height of the rectangle
		 * @param color - uint16_t - Color in 16 bits mode
         * @return  false if x, y, x+w and y+h are out of range
		 */	
        bool    draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

        /**
		 * @brief    Draw a filled rectangle using its top-left corner and its dimension
		 * @param x - uint16_t - x position of the top-left corner of the rectangle
		 * @param y - uint16_t - y position of the top-left corner of the rectangle
		 * @param w - uint16_t - width of the rectangle
		 * @param h - uint16_t - height of the rectangle
		 * @param color - uint16_t - Color in 16 bits mode
         * @return  false if x, y, x+w and y+h are out of range
		 */	
        bool    fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);


        /**
		 * @brief   Draw a character on the screen
		 * @param character - char - character to draw
		 * @param color - uint16_t - Color of the character
		 * @param size - enum Size - (NORMAL, LARGE, HUGE)
		 * @return false if character is not in the possible table of characters
		 */
		bool 	draw_char(char character, uint16_t color, enum Size size);
			
		/**
		 * @brief    Draw a string of characters
		 * @param str - char * - String to display
		 * @param color - uint16_t - Color of the string
		 * @param size - enum Size - (NORMAL, LARGE, HUGE)
		 *
		 * @return  false if the string of characters is too large for the screen
		 */
		bool 	draw_string(char *str, uint16_t color, enum Size size);


    private:
        /// Text cursor position
        uint16_t        __text_x;
        uint16_t        __text_y;
};

#endif