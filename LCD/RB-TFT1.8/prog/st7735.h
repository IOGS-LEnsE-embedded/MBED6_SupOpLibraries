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
#include <cstdint>

/**
 * @class ST7735
 * @brief Class to control a LCD display driven by a ST7735 device
 * @details     ST7735 is a 262K Color Single-Chip TFT Controller/Driver
 */

class ST7735 {
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

        /// Text position
        uint16_t        __text_x;
        uint16_t        __text_y;
		
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
		 * @brief    Set position of the window
		 * @param x0  uint8_t - start position on X axis
		 * @param x1  uint8_t - end position on X axis
		 * @param y0  uint8_t - start position on Y axis
		 * @param y1  uint8_t - end position on Y axis
		 * @return false if the positions are out of range of the screen
		 */
		bool 	set_window(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1);

        /**
        * @brief   Set text position x, y
        * @param x  uint8_t - position on X axis
        * @param y  uint8_t - position on Y axis
        * @return  false if x and y are out of range
        */
        bool    set_position (uint8_t x, uint8_t y);

		/**
		 * @brief   Set the color of the pixel
		 * @param color 	uint16_t - Color in 16 bits mode
		 * @param nb_pixels	uint16_t - Number of pixels to change
		 */
		void 	set_color(uint16_t color, uint16_t nb_pixels);
		
		/**
		 * @brief    Draw a pixel at a specific position
		 * @param x  uint8_t - x position / 0 <= cols <= MAX_X-1
		 * @param y  uint8_t - y position / 0 <= rows <= MAX_Y-1
		 * @param color 	uint16_t - Color in 16 bits mode
		 */
		void 	draw_pixel (uint16_t x, uint16_t y, uint16_t color);
			   
		/**
		 * @brief   Draw a character on the screen
		 * @param character char - character to draw
		 * @param color  uint16_t - Color of the character
		 * @param size - enum Size - (X1, X2, X3)
		 * @return false if character is not in the possible table of characters
		 */
		bool 	draw_char(char character, uint16_t color, enum Size size);
};

#endif