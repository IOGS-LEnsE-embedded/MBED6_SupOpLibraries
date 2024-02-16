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

 #include <cstdint>
#include <mbed.h>
 #include "LCD_EA_DOG.h"


/****************************************************************/
LCD_EA_DOG::LCD_EA_DOG(PinName rs, PinName cs, SPI *spi, int freq, uint8_t nb_lines, uint8_t nb_chars): 
    __cs(cs), __rs(rs){
    this->_frequency = freq;
    this->_nb_lines = nb_lines;
    this->_nb_chars = nb_chars;
    /* Initialisation of the SPI connection */
    if (spi){ delete this->__spi; }
    this->__spi=spi;
    this->__spi->frequency(this->_frequency);
    this->__spi->format(8, 3);      // 8 bits, mode 3
    /* Initialisation of RS and CS pin */
    this->__rs.write(1);
    this->__cs.write(1);
    thread_sleep_for(10);      // 10 ms
}

/****************************************************************/
void LCD_EA_DOG::initLCD(void){
    this->__rs.write(0);
    this->__cs.write(0);
    thread_sleep_for(10);       // 10 ms
    this->__spi->write(0x29);   // Function Set - table 1
    this->__spi->write(0x1D);   // Bias Set
    this->__spi->write(0x50);   // Power Control
    this->__spi->write(0x6C);   // Follower Control
    this->__spi->write(0x78);   // Contrast Set
    this->__spi->write(0x03);   // Function Set - table 0
    this->__spi->write(0x0F);   
    this->__spi->write(0x01);   // Clear Display
    thread_sleep_for(2);        // 2 ms
    this->__spi->write(0x06);   // Display On
    thread_sleep_for(10);       // 10 ms
    this->__rs.write(1);
    this->__cs.write(1);
    thread_sleep_for(10);       // 10 ms

    /*
    writeLCD('_');
    */
    return;
}


void LCD_EA_DOG::display_off(void){
    this->__rs.write(0);
    this->__cs.write(0);
    this->__spi->write(0x08);  // Display Off
    thread_sleep_for(2);       // 10 ms
    this->__rs.write(1);
    this->__cs.write(1);
}

void LCD_EA_DOG::display_on(void){
    this->__rs.write(0);
    this->__cs.write(0);
    this->__spi->write(0x0F);  // Display On
    thread_sleep_for(2);       // 10 ms
    this->__rs.write(1);
    this->__cs.write(1);
}

bool LCD_EA_DOG::set_contrast(uint8_t val){
    if((val < 0) || (val > 7)){
        return false;
    }
    uint8_t contrast = 0x78 + val;
    this->__rs.write(0);
    this->__cs.write(0);
    this->__spi->write(contrast);   // Contrast Set
    thread_sleep_for(2);       // 10 ms
    this->__rs.write(1);
    this->__cs.write(1);
    return true;
}
 
/****************************************************************/
void LCD_EA_DOG::clearLCD(void){
    this->__rs.write(0);
    this->__cs.write(0);
    this->__spi->write(0x01);   // Clear Display
    thread_sleep_for(2);        // 2 ms
    this->__rs.write(1);
    this->__cs.write(1); 
    return;
}

/****************************************************************/
void LCD_EA_DOG::writeCmdLCD(char c){
    this->__rs.write(0);
    this->__cs.write(0);
    this->__spi->write(c);   // Send command
    thread_sleep_for(1);     // 1 ms
    this->__rs.write(1);
    this->__cs.write(1); 
    return;
}


/****************************************************************/
void LCD_EA_DOG::writeLCD(char c){
    this->__rs.write(1);
    this->__cs.write(0);
    this->__spi->write(c);   // Send char
    thread_sleep_for(1);     // 1 ms
    this->__cs.write(1);
    return;
}

/****************************************************************/
bool LCD_EA_DOG::writeStrLCD(char c[], char line, char col){
    char i = 0;
    bool pos = setPosition(line, col);
    if(pos){
        while(c[i] != '\0'){
            writeLCD(c[i]);
            i++;
        }
    }
    return pos;
}

/****************************************************************/
bool LCD_EA_DOG::writeCstStrLCD(const char c[], char line, char col){
    char i = 0;
    bool pos = setPosition(line, col);
    if(pos){
        while(c[i] != '\0'){
            writeLCD(c[i]);
            i++;
        }
    }
    return pos;
}

 /****************************************************************/
bool LCD_EA_DOG::setPosition(uint8_t line, uint8_t col){
    if((line <= 0) || (line > this->_nb_lines)){
        return false;
    }
    if((col <= 0) || (col > this->_nb_chars)){
        return false;
    }
    char adress = 0x80 + ((line-1) * 16) + (col - 1);
    this->writeCmdLCD(adress);
    thread_sleep_for(1);        // 1 ms
    return true;
}