/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "TCS34725.h"

/// Internal boolean print function
void printbool(bool v, char* name);

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

I2C my_i2c(D14, D15);
TCS34725    my_rgb(&my_i2c);

uint16_t    r, g, b, c;

int main()
{
    printbool(my_rgb.init(), "RGB sensor init");
    printbool(my_rgb.setIntegrationTime(TCS34725_INTEGRATIONTIME_24MS), "Integ Time init");
    printbool(my_rgb.setGain(TCS34725_GAIN_4X), "Gain Init");
    printbool(my_rgb.enable(), "Enable");   

    printbool(my_rgb.getRawData(&c, &r, &g, &b), "Get Data Init"); 
    printf("R=%d / G=%d / B=%d // C=%d \r\n", r, g, b, c);    

    while (true)
    {
        led1 = !led1;
        printbool(my_rgb.getRawData(&c, &r, &g, &b), "Get Data Init"); 
        printf("R=%d / G=%d / B=%d // C=%d \r\n", r, g, b, c);  
        thread_sleep_for(WAIT_TIME_MS);
    }
}


/// Internal boolean print function
void printbool(bool v, char* name){
    if(v == true)
        printf("%s = True \r\n", name);
    else
        printf("%s = False \r\n", name);
    
}