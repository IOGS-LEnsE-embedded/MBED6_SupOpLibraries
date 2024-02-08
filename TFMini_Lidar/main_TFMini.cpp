/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "TFMini.h"

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

TFMini    my_lidar(A4, A5);
char    lidar_data[9];


int main()
{
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        uint16_t dist = my_lidar.getDistance();
        uint16_t strength = my_lidar.getRecentSignalStrength();
        printf("Dist = %d cm  / %d \r\n", dist, strength);
    }
}
