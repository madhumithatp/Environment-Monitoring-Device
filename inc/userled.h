/**
 * @file userled.h
 * @author author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#ifndef USERLED_H
#define USERLED_H
#include <linux/gpio.h>
#include <unistd.h>
#include <fcntl.h>

typedef enum
{
LED0 = 0,
LED1 = 1,
LED2 = 2,
LED3 = 3
}UserLed_t;



#define     OFF  0
#define     ON   1


#define USERLED0_PIN			"/sys/class/gpio/gpio53/value"
#define USERLED1_PIN    		"/sys/class/gpio/gpio54/value"
#define USERLED2_PIN			"/sys/class/gpio/gpio55/value"
#define USERLED3_PIN			"/sys/class/gpio/gpio56/value"


/**
 * @brief open led file descriptor
 *  @param num 
 * 
 */
int Led_init(UserLed_t num);
/**
 * 
 * @brief Construct a new userled on object
 * 
 * @param led_num 
 */
int userled(UserLed_t led_num, int on_off);

#endif