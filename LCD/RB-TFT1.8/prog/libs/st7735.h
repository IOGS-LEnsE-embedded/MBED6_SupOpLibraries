/**
 * FILENAME :        st7735.h          
 *
 * DESCRIPTION :
 *       TFT Joy-It RB-TFT1.8 - 1.8' LCD display - Library
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    17/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 *
 *  @see : https://github.com/Matiasus/ST7735
 *  @see : https://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
 */

#ifndef __ST7735_H__
#define __ST7735_H__

#include "mbed.h"
#include "st7735_constants.h"
#include "LCD_graphics.h"

/**
 * @class ST7735
 * @brief 	Class to control a LCD display driven by a ST7735 device
 * @details ST7735 is a 262K Color Single-Chip TFT Controller/Driver
 */

class ST7735 : public LCD_graphics {
    private:
        /// SPI interface 
        SPI 			*__spi;
		/// CS pin of the ST7735 driver
		DigitalOut		__cs;
		/// RS/DC pin of the ST7735 driver
		DigitalOut		__rs_dc;
		/// Reset pin of the ST7735 driver
		DigitalOut		__reset;
		
		/// Width and Height of the screen
		uint16_t		__width;
		uint16_t		__height;
		
		/// Background color
		uint16_t		__bg_color;
		
        /**
        * @brief Send a command of 8 bits to the driver.
        * @param cmd uint8_t - Command to send, 1 byte.
		*/
		void 	send_command(uint8_t cmd);

        /**
        * @brief Send a data of 8 bits to the driver.
        * @param data uint8_t - Data to send, 1 byte.
		*/		
		void	send_data_8bits(uint8_t data);
		
        /**
        * @brief Send a data of 16 bits to the driver.
        * @param data uint16_t - Data to send, 2 bytes.
		*/				
		void 	send_data_16bits (uint16_t data);
		
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
        * @param SPI SPI - SPI interface. Initialization at 20MHz speed
        * @param cs PinName - CS pin of the ST7735 driver
        * @param rs_dc PinName - RS/DC pin of the ST7735 driver
        * @param reset PinName - Reset pin of the ST7735 driver
        */
        ST7735(SPI *spi, PinName cs, PinName rs_dc, PinName reset);
		
		/**
        * @brief Hardware reset of the display.
		*/
		void 	reset(void);

		/**
        * @brief Initialization of the display.
		*/		
		void	init(void);

		/**
        * @brief Switch on the screen.
		*/			
		void 	display_on(void);

		/**
        * @brief Switch off the screen.
		*/	
		void 	display_off(void);
		
		/**
        * @brief Clear the screen in a specific color
		* @param color 	uint16_t - Color in 16 bits mode
		*/		
		void 	clear_screen(uint16_t color);
		
		/**
        * @brief Set the screen size in pixels
		* @param width  uint16_t - width of the screen in pixels
		* @param height uint16_t - height of the screen in pixels
		*/		
		void 	set_screen_size(uint16_t width, uint16_t height);
		
		/**
		 * @brief    Set position of the window
		 * @param x0  uint16_t - start position on X axis
		 * @param x1  uint16_t - end position on X axis
		 * @param y0  uint16_t - start position on Y axis
		 * @param y1  uint16_t - end position on Y axis
		 * @return false if the positions are out of range of the screen
		 */
		bool 	set_window(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);

		/**
		 * @brief   Set the color of the pixel
		 * @param color - uint16_t - Color in 16 bits mode
		 * @param nb_pixels - uint16_t - Number of pixels to change
		 */
		void 	set_color(uint16_t color, uint16_t nb_pixels);
		
		/**
		 * @brief    Draw a pixel at a specific position
		 * @param x - uint16_t - x position / 0 <= cols <= MAX_X-1
		 * @param y - uint16_t - y position / 0 <= rows <= MAX_Y-1
		 * @param color - uint16_t - Color in 16 bits mode
         * @return  false if x and y are out of range
		 */
		bool	draw_pixel (uint16_t x, uint16_t y, uint16_t color);
};

#endif