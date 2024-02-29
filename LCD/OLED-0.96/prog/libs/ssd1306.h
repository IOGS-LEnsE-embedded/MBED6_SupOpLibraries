/**
 * FILENAME :        ssd1306.h          
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

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "mbed.h"
#include "ssd1306_constants.h"
#include "LCD_graphics.h"
#include <vector>

/**
 * @class SSD1306
 * @brief 	Class to control a LCD display driven by a SSD1306 device
 * @details ST7735 is a 128 x 64 Dot Matrix OLED/PLED Segment/Common 
 *      Driver with Controller 
 */

class SSD1306 : public LCD_graphics {
    private:
	    /// The memory buffer for the LCD
	    std::vector<uint8_t> __buffer;
        uint16_t    __buff_size;

        /// I2C interface 
        I2C			*__i2c;
		
		/// Width and Height of the screen
		uint16_t		__width;
		uint16_t		__height;
		
        
		
        /**
        * @brief Send a command of 8 bits to the driver.
        * @param cmd uint8_t - Command to send, 1 byte.
        * @return bool - True if acknowledgement is done.
		*/
		bool 	send_command(uint8_t cmd);

        /**
        * @brief Send a data of 8 bits to the driver.
        * @param data std::vector<uint8_t> - Data to send, 1 byte.
        * @param size uint16_t - Number of data to send.
        * @return bool - True if acknowledgement is done.
		*/		
		bool	send_data(std::vector<uint8_t> data, uint16_t size);
				
		/**
        * @brief Check if the coordinates are in the range of the screen size
		* @param x  uint16_t - coordinate on X axis
		* @param y 	uint16_t - coordinate on Y axis
		* @return true if is in the range of the screen size
		*/			
		bool    check_range(uint16_t x, uint16_t y);

		/**
        * @brief Check if the value is in the range
		* @param val  uint16_t - value to test
		* @param min  uint16_t - minimum value of the range
		* @param max  uint16_t - maximum value of the range
		* @return true if is in the range 
		*/			
		bool    check_value_range(uint16_t val, uint16_t min, uint16_t max);
		

    public:
        /**
        * @brief Simple constructor of the ST7735 class.
        * @details Create a ST7735 object based on a SPI interface
        * @param i2c I2C - I2C interface.
		* @param width  uint16_t - width of the screen in pixels.
		* @param height uint16_t - height of the screen in pixels.
        */
        SSD1306(I2C *i2C, uint16_t width, uint16_t height);

		/**
        * @brief Initialization of the display.
        * @return bool - True if aknowledgement is done.
		*/		
		bool	init(void);

		/**
        * @brief Switch on the screen.
		*/			
		void 	display_on(void);

		/**
        * @brief Switch off the screen.
		*/	
		void 	display_off(void);

		/**
        * @brief Invert the color of the screen.
		*/	
        void    invertDisplay(bool i);
		
		/**
        * @brief Clear the screen 
		*/		
		void 	clear_screen(void);
		
		/**
        * @brief Update the buffer to the display.
        * @return bool - True if aknowledgement is done.
		*/
        bool    display(void);
		
		/**
		 * @brief    Draw a pixel at a specific position
		 * @param x - uint16_t - x position / 0 <= cols <= MAX_X-1
		 * @param y - uint16_t - y position / 0 <= rows <= MAX_Y-1
		 * @param color - uint16_t - Color in 16 bits mode
         * @return  false if x and y are out of range
		 */
		bool	draw_pixel (uint16_t x, uint16_t y, uint16_t color);

        /**
		 * @brief    Return the buffer of the screen
         */
        std::vector<uint8_t> get_buffer(void);
};

#endif