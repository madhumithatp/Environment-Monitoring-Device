/**
 * @file userled.c
 * @author sDeepesh Sonigra
 *          Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-30
 * @citation http://beaglebone.cameon.net/home/using-the-user-leds
 * @copyright Copyright (c) 2019
 * 
 */

#include "userled.h"

int Led_init(UserLed_t num)
{
    int fd ;
    switch(num)
    {
        case LED0:
        fd = open(USERLED0_PIN, O_WRONLY);
        break;

        case LED1:
        fd = open(USERLED1_PIN, O_WRONLY);
        break;

        case LED2:
        fd = open(USERLED2_PIN, O_WRONLY);
        break;

        case LED3:
        fd = open(USERLED3_PIN, O_WRONLY);
        break;

        default:
        printf("Invalid LED pin \n");
    
    }
    return fd;
}

int UserLed(UserLed_t num, int on_off)
{
    int fd_led;
    fd_led = Led_init(LED1);
    write(fd_led, on_off,1);
    close(fd_led);
}



