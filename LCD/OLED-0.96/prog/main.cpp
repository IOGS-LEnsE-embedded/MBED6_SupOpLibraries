/**
 * FILENAME :        main.cpp          
 *
 * DESCRIPTION :
 *       LCD Joy-It OLED-0.96 - 0.96' LCD display - testing program
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    29/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#include "mbed.h"
#include "ssd1306.h"
#include "ssd1306_constants.h"


/// Inputs/outputs declaration 
Ticker controlLoopTik;

InterruptIn     mode_change(BUTTON1);

I2C         my_i2c(D14, D15);
SSD1306     my_lcd(&my_i2c, MAX_X, MAX_Y);


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

/// Internal boolean print function
void printbool(bool v, char* name);

// 
int	cpt = 0;

/* Main code */
int main()
{
    // Initialization 
    printf("OLED0.96 / LCD Screen / Initialization\r\n");
    thread_sleep_for(100);

	printbool(my_lcd.init(), "INIT ");
	my_lcd.clear_screen();
    thread_sleep_for(200);
    printf("\tEND Initialization\r\n");

    int k = my_lcd.get_buffer().size();
    printf("Screen Buffer size = %d\r\n", k);


    
    my_lcd.draw_pixel(5, 10, SSD1306_WHITE);
    my_lcd.fill_rect(10, 20, 20, 30, SSD1306_WHITE);
    my_lcd.set_position(50, 20);
    my_lcd.draw_string("Test LCD", SSD1306_WHITE, NORMAL);
    
    my_lcd.draw_line(30, 50, 60, 40, SSD1306_WHITE);
    my_lcd.display();

    // Initialization of interrupt on falling edge of the push button
    mode_change.fall(&ISR_change_mode);

    // Initialization of main ticker
    controlLoopTik.attach(&ISR_controlLoopTik, 100ms);

    while (true){

		if(cpt % 20 == 0){
            // BackLight can not be disable on the Joy-IT RB-TFT1.8
			my_lcd.invertDisplay(true);
		}
		if(cpt % 20 == 10){
			my_lcd.invertDisplay(false);
		}
    }
}


/* */
void ISR_controlLoopTik(void){
    //printf("Main\r\n");
	cpt++;
}

/* */
void ISR_change_mode(void){
    printf("Button\r\n");
}


/// Internal boolean print function
void printbool(bool v, char* name){
    if(v == true)
        printf("%s = True \r\n", name);
    else
        printf("%s = False \r\n", name);
    
}