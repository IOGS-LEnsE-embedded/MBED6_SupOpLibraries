/**
 * FILENAME :        main.cpp          
 *
 * DESCRIPTION :
 *       TFT Joy-It RB-TFT1.8 - 1.8' LCD display - testing program
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

#include "mbed.h"
#include "st7735.h"


/// Inputs/outputs declaration 
Ticker controlLoopTik;

InterruptIn     mode_change(BUTTON1);

SPI         my_spi(D11, D12, D13);
ST7735      my_lcd(&my_spi, D8, D10, D9);


/* Methods */
/**
 * Interrupt routine attached to the sampling of the Contol Loop System
 *
 * @return Updates the system control loop outputs
 */
void ISR_controlLoopTik(void);

/**
 * Interrupt routine attached to the mode change button
 */
void ISR_change_mode(void);


// 
int	cpt = 0;

/* Main code */
int main()
{
    // Initialization 
    printf("RB-TFT1.8 / LCD Screen / Initialization\r\n");
	my_lcd.init();
	my_lcd.clear_screen(ST7735_BLACK);
	my_lcd.draw_pixel(20, 20, ST7735_RED);
    for(int i = 0; i < 10; i++){
        my_lcd.draw_pixel(30+i, 30+i, ST7735_RED);
    }
    my_lcd.set_position(50, 50);
	my_lcd.draw_char('a', ST7735_BLUE, X1);
    my_lcd.set_position(80, 100);
	my_lcd.draw_char('V', ST7735_GREEN, X1);

    printf("\tEND Initialization\r\n");
    // Initialization of interrupt on falling edge of the push button
    mode_change.fall(&ISR_change_mode);

    // Initialization of main ticker
    controlLoopTik.attach(&ISR_controlLoopTik, 100ms);
    
    while (true){
		if(cpt % 20 == 0){
			my_lcd.display_off();
		}
		if(cpt % 20 == 10){
			my_lcd.display_on();
		}
		
    }
}


/* */
void ISR_controlLoopTik(void){
    printf("Main\r\n");
	cpt++;
}

/* */
void ISR_change_mode(void){
    printf("Button\r\n");
}
