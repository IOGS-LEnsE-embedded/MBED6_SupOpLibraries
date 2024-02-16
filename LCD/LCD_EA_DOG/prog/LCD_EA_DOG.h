/**
 * FILENAME :        LCD_EA_DOG.cpp          
 *
 * DESCRIPTION :
 *       LCD_EA_DOG library
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    16/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

// TODO : 
//      - setVref
//      - setPinConfig
//      - setConfig

#ifndef __LCD_EA_DOG_HEADER_H__
#define __LCD_EA_DOG_HEADER_H__

#include <cstdint>
#include <mbed.h>
 
/** Constant definition */
#define     DEBUG_MODE                  1

/**
 * @class LCD_EA_DOG
 * @brief Control a LCD screen from EA DOG
 */
class LCD_EA_DOG{
     private:
        /// SPI Frequency
        float       _frequency;
        /// Number of lines and characters per line
        uint8_t     _nb_lines;
        uint8_t     _nb_chars;

        /// interface to TMC2100 pins 
        DigitalOut  __rs; 
        DigitalOut  __cs;
        SPI         *__spi;


    public:
        /**
        * @brief Simple constructor of the LCD_EA_DOG class.
        * @details Create a LCD_EA_DOG object with
        *    a RS pin (Digital)
        *    a CS pin (Digital)
        *    a SPI connection
        * @param rs RS pin of the LCD screen
        * @param cs Chip Select pin of the LCD screen
        * @param spi SPI connection of the LCS screen
        * @param freq SPI frequency - default 100 kHz
        * @param nb_lines number of lines of the LCD screen - default 3
        * @param nb_chars number of characters per line of the LCD screen - default 16
        */
        LCD_EA_DOG(PinName rs, PinName cs, SPI *spi, int freq=100000, uint8_t nb_lines=3, uint8_t nb_chars=16);
        
        /**
        * @brief Initialization of the LCD screen.
        */
        void    initLCD(void);

        /**
        * @brief Clear the screen.
        */
        void    clearLCD(void);

        /**
        * @brief Switch off the screen.
        */
        void    display_off(void);

        /**
        * @brief Switch on the screen.
        */
        void    display_on(void);

        /**
        * @brief Change the contrast of the screen.
        * @param val Value of the contrast, between 0 to 7.
        * @return true if the value of contrast is in the good range.
        */ 
        bool    set_contrast(uint8_t val);

        /**
        * @brief Write a char on the LCD screen at the next position.
        * @param c Character to display.
        */        
        void    writeLCD(char c);

        /**
        * @brief Write a string of characters.
        * @details  Write a string of characters on the LCD screen 
        *       at a specific position.
        * @param c* String of characters to display.
        * @param line Number of the line to display the string of characters.
        * @param col Number of the column to display the string of characters.
        * @return true if the line and the column are in the good range.
        */  
        bool    writeStrLCD(char c[], char line, char col);

        /**
        * @brief Write a constant string of characters.
        * @details  Write a constant string of characters on the LCD screen 
        *       at a specific position.
        * @param c* Constant string of characters to display.
        * @param line Number of the line to display the string of characters.
        * @param col Number of the column to display the string of characters.
        * @return true if the line and the column are in the good range.
        */  
        bool    writeCstStrLCD(const char c[], char line, char col);

        /**
        * @brief Send a command to the LCD screen.
        * @param c Command to send.
        */
        void    writeCmdLCD(char c);

        /**
        * @brief Change the position of the cursor on the screen.
        * @param line Number of the line to move the cursor.
        * @param col Number of the column to move the cursor.
        * @return true if the line and the column are in the good range.
        */
        bool    setPosition(uint8_t line, uint8_t col);

};

#endif