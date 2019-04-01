/**
 * @file startup_tests.h
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief Built-in Start Up Tests for Temperature and Light Sensor
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef STARTUP_TESTS_H_
#define STARTUP_TESTS_H_

#include <stdio.h>
#include <stddef.h>

#include "driver_i2c.h"
#include "tmp102.h"
#include "apds9301.h"
#include "logger_task.h"
#include "temperature_task.h"
#include "light_task.h"

#define TLOW_VALUE              368     //23
#define THIGH_VALUE             400      //25
#define APDS903_TH_LOW_VAL      20      
#define APDS903_TH_HIGH_VAL     40     



#endif /* STARTUP_TESTS_H_ */
