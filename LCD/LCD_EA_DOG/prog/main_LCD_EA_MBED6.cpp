/**
 * FILENAME :        main.cpp          
 *
 * DESCRIPTION :
 *       LCD EA DOG 3 x 16 characters library test
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    16/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#include "LCD_EA_DOG.h"
#include "mbed.h"

/// Inputs/outputs declaration
SPI             my_spi(D11, D12, D13);
LCD_EA_DOG      my_lcd(D6, D8, &my_spi);


char        str_to_write[16];
int         k = 5;


/* Methods */
/**
 * Interrupt routine attached to the mode change button
 */
void ISR_change_mode(void);

/* Main code */
int main()
{
    // Initialization 
    printf("LCD EA DOG / Test program\r\n");

    // LCD Initialization
    my_lcd.initLCD();
    my_lcd.writeLCD('J');
    
    while (true){
        k++;
        sprintf(str_to_write, "Test k = %d", k);
        my_lcd.writeStrLCD(str_to_write, 2, 1);
        thread_sleep_for(500);
        if(k % 4 == 0){
            my_lcd.display_on();
            my_lcd.set_contrast(7);
        } 
        if(k % 4 == 1){
            my_lcd.display_on();
            my_lcd.set_contrast(4);
        }
        if(k % 4 == 2){
            my_lcd.display_off();
        }
        if(k % 4 == 3){
            my_lcd.display_on();
            my_lcd.set_contrast(0);
        }        
    }
}


