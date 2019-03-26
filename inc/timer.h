/**
 * @file timer.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Header File for timer functions
 * @version 0.1
 * @date 2019-03-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

#define FACTOR_NANOSEC      1000000000

/**
 * @brief Create a posixtimer object
 * 
 * @param timerID 
 * @return int 
 */
int create_posixtimer(timer_t timerID, void (*timer_callback)());

/**
 * @brief Start Posix Timer
 * 
 * @param timerID 
 * @param sec 
 * @return int 
 */
int start_posixtimer(timer_t timerID, unsigned int sec);

/**
 * @brief Stop Posix Timer
 * 
 * @param timerID 
 * @return int 
 */
int stop_posixtimer(timer_t timerID);

#endif /* TIMER_H_ */
