/**
 * @file unittest.c
 ** @author Deepesh Sonigra
 *          Madhumitha Tolakanahalli
 * @brief Functions related to unit testing using CUnit framework
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019
 * @citation http://wpollock.com/CPlus/CUnitNotes.htm was referred to for the code
 */

#include "unittest.h"

mqd_t ut_mq_log;

int init_suite(void) 
{ 
	srand(time(NULL));
	return 0; 
}
int clean_suite(void) { return 0; }

/* Testing Posix Mqueue Init */
void unittest_mqueue_init()
{
    ut_mq_log = log_task_mq_init();
    CU_ASSERT_EQUAL(ut_mq_log,-1);
}
/* Testing Temperature conversions */
void unittest_regval_totempC()
{
    uint16_t regval = 0x320;
    float temperature = regval_to_tempC(regval);
    printf("\n - Regval %f",temperature);
    CU_ASSERT_EQUAL(temperature,3.125000);
}

void unittest_getTemperature()
{
    float t=50,t_k=0,t_f=0;
    float t_c = 0;
   
    t_k = TMP_C_TO_K(t);
    printf("\n -temp in K %f",t_k);
    CU_ASSERT_EQUAL(t_k,(float)323.000000);
    
    t_f = TMP_C_TO_F(t);
    printf("\n -temp in F %f",t_f);
    CU_ASSERT_EQUAL(t_f,122.000000);

}
/* Testing Calculation of Lux Value and Thresholding for Day/Night detection */
void unittest_calculateLuminosity()
{
    float Ch0 = 3, Ch1 = 2, lux = 0;
    light val;
    lux = calculateLuminosity(Ch0, Ch1);
    printf("lux %f",lux);
    CU_ASSERT_EQUAL(lux,(float)0.007800);

    val = is_Day_or_Night(lux);
    CU_ASSERT_EQUAL(val,NIGHT);
}

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* Initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* Add a suite to the registry */
   pSuite = CU_add_suite( "unittest_mqueue_init", init_suite, clean_suite );
   pSuite = CU_add_suite( "unittest_regval_totempC", init_suite, clean_suite );  
   pSuite = CU_add_suite( "unittest_getTemperature", init_suite, clean_suite );  
   pSuite = CU_add_suite( "unittest_calculateLuminosity", init_suite, clean_suite );
  
   if ( NULL == pSuite ) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Add the tests to the suite */
    if ( (NULL == CU_add_test(pSuite, "Posix MQueue Init Test", unittest_mqueue_init)) || 
         (NULL == CU_add_test(pSuite, "Temperature Verification Test", unittest_getTemperature)) || 
         (NULL == CU_add_test(pSuite, "Temperature Verification Test", unittest_regval_totempC)) ||
         (NULL == CU_add_test(pSuite, "Luminosity Verification Test",  unittest_calculateLuminosity)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}