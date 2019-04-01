/**
 * @file startup_tests.c
 * @author Deepesh Sonigra
 *         Madhumitha Tolakanahalli
 * @brief 
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "startup_tests.h"

timer_t test_timerID;
int flag = 0;

void test_task_timer_handler()
{
    if(flag) 
    {
        stop_posixtimer(test_timerID);
        printf("Timer Stopped BIST \n");
    }
    else
    {
        printf("BIST failed. Exiting Program...");
        exit(1);
    }
    
}

return_status built_in_startup_tests()
{
    uint16_t register_val;
    
    return_status st_tmp102;
    int count;
    // /* Temperature Sensor Tests */
    // if(create_posixtimer(&test_timerID,&test_task_timer_handler) == -1)
    //     printf("Socket Timer Create Error \n");
    // else
    //     printf("Socket Timer created \n");   
    // if(start_posixtimer(test_timerID,5) == -1)
    //     printf("Socket Timer Start Error \n");
    // else
    //      printf("Socket Timer Started \n");

    //RESTART_T:
    tmp102_write_reg(TMP_REG_TLOW, TLOW_VALUE);
    register_val = tmp102_read_reg(TMP_REG_TLOW);
    if(register_val != TLOW_VALUE)
    {
        flag =1;
        printf("Error Reading TLOW reg \n");
        //goto RESTART_T;
    }

    tmp102_write_reg(TMP_REG_THIGH, THIGH_VALUE);
    register_val = tmp102_read_reg(TMP_REG_THIGH);
    if(register_val != THIGH_VALUE)
    {
        flag =1;
        printf("Error Reading THIGH reg \n");
        //goto RESTART_T;
    }

    tmp102_write_reg(TMP_REG_CONFIGURATION, TMP_CONFIG_FAULT(3));
    register_val = tmp102_read_reg(TMP_REG_CONFIGURATION);
    if(!(register_val | TMP_CONFIG_FAULT(3)))
    {
        flag =1;
        printf("Error Reading TCONFIGURATION reg %x \n",register_val);
        //goto RESTART_T;
    }

    int retval = 0;
    uint16_t val = 0;
    /* Light Sensor BISTs */
    //RESTART_L:
    
    retval = apds9301_power_on(); 
    if(retval == ERROR)
     {
         flag =1;
        printf("Error in APDS9301 Sensor PowerOn\n");
        //goto RESTART_L;
    }
    retval = apds9301_setup(); 
    if(retval == ERROR)
     {
         flag =1;
        printf("Error in APDS9301 Sensor Setup\n");
        //goto RESTART_L;
    }

    if(apds9301_write_reg(APDS9301_REG_TIMING,(APDS9301_REG_TIMING_GAIN | APDS9301_REG_TIMING_INTEG(0x00))) == ERROR)
    {
        printf("Error in APDS9301 Sensor Initialization\n");
        //goto RESTART_L;
    }

    val = apds9301_read_reg_1byte(APDS9301_REG_TIMING);
    if(val != (APDS9301_REG_TIMING_GAIN | APDS9301_REG_TIMING_INTEG(0x00)))
    {
        flag =1;
        printf("Error in read APDS9301 Timing Register\n");
        //goto RESTART_L;
    }
 
    if(apds9301_write_reg_2byte( APDS9301_REG_TH_LOW_LOW,APDS903_TH_LOW_VAL) == ERROR)
    {
        flag =1;
        printf("Error in writing APDS9301 TH Low \n");
        //goto RESTART_L;
    }

    val = apds9301_read_reg_2byte(APDS9301_REG_TH_LOW_LOW);
    
    if(val != APDS903_TH_LOW_VAL)
    {
        flag =1;
        printf("Error in read APDS9301 Th LOW\n");
        //goto RESTART_L;
    }
    if(apds9301_write_reg_2byte(APDS9301_REG_TH_HIGH_LOW,APDS903_TH_HIGH_VAL) == ERROR)
    {
        flag =1;
        printf("Error in writing APDS9301 TH HIGH \n");
        //goto RESTART_L;
    }
    val = apds9301_read_reg_2byte(APDS9301_REG_TH_HIGH_LOW);
     if(val != APDS903_TH_HIGH_VAL)
    {
        flag =1;
        printf("Error in read APDS9301 Th High\n");
        //goto RESTART_L;
    }

    if(flag)
    return ERROR;

    printf("BIST executed successfully \n");

    return SUCCESS;
}