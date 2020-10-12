/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"


/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/


/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */

/* ********************************* TASK_1 *************************** */

/*TaskHandle_t LED_Toggel_handler = NULL;


void LED_Toggel( void * pvParameters )
{
	
    for( ;; )
    {
        GPIO_write(PORT_0, PIN1, PIN_IS_HIGH);
			
			  vTaskDelay( 1000 );
			
			  GPIO_write(PORT_0, PIN1, PIN_IS_LOW);
			  vTaskDelay( 1000 );
    }
}
*/

/* *********************************** TASK_2 ************************** */
/*
TaskHandle_t LED1_handeler = NULL;
TaskHandle_t LED2_handeler = NULL;
TaskHandle_t LED3_handeler = NULL;


void LED_1( void * pvParameters )
{
	
    for( ;; )
    {
        GPIO_write(PORT_0, PIN1, PIN_IS_HIGH);
			
			  vTaskDelay( 100 );
			
			  GPIO_write(PORT_0, PIN1, PIN_IS_LOW);
			  vTaskDelay( 100 );
    }
}


void LED_2( void * pvParameters )
{
	
    for( ;; )
    {
        GPIO_write(PORT_0, PIN2, PIN_IS_HIGH);
			
			  vTaskDelay( 500 );
			
			  GPIO_write(PORT_0, PIN2, PIN_IS_LOW);
			  vTaskDelay( 500 );
    }
}

void LED_3( void * pvParameters )
{
	
    for( ;; )
    {
        GPIO_write(PORT_0, PIN3, PIN_IS_HIGH);
			
			  vTaskDelay( 1000 );
			
			  GPIO_write(PORT_0, PIN3, PIN_IS_LOW);
			  vTaskDelay( 1000 );
    }
}
*/

/* ******************************* TASK_3 ******************************* */

TaskHandle_t Button_Task_handeler = NULL;
TaskHandle_t LED_state_1_handeler = NULL;
TaskHandle_t LED_state_2_handeler = NULL;
TaskHandle_t LED_state_3_handeler = NULL;

int Button_counter =0;
int state=0;

void Button_Task( void * pvParameters )
{
	
    for( ;; )
    {
			
			 state = GPIO_read( PORT_0 , PIN0);
			
			if(state == PIN_IS_HIGH )
			{
				Button_counter = Button_counter+1;
			}
			
			  vTaskDelay( 1000 );
    }
}


void LED_state_1( void * pvParameters )
{
	
    for( ;; )
    {
			if(  Button_counter>2 && Button_counter<4)
			{
				
				GPIO_write(PORT_0, PIN1, PIN_IS_HIGH);
				
				vTaskDelay( 400 );
				
				GPIO_write(PORT_0, PIN1, PIN_IS_LOW);
				
				
				vTaskDelay( 400 );
				
			}
			else
			{
				vTaskDelay( 400 );
			}
      
    }
}

void LED_state_2( void * pvParameters )
{
	
    for( ;; )
    {
			if(  Button_counter>4 )
			{
				
				GPIO_write(PORT_0, PIN1, PIN_IS_HIGH);
				
				vTaskDelay( 100 );
				
				GPIO_write(PORT_0, PIN1, PIN_IS_LOW);
				
				
				vTaskDelay( 100 );
				
			}
			else
			{
				vTaskDelay( 100 );
			}
      
    }
}


void LED_state_3( void * pvParameters )
{
	
    for( ;; )
    {
			if(  Button_counter<2 )
			{
				
				
				GPIO_write(PORT_0, PIN1, PIN_IS_LOW);
				
				
				vTaskDelay( 50 );
				
			}
			
			else
			{
				vTaskDelay( 50 );
			}
      
    }
}

/* **************************************************************** */

int main( void )
{
	
	prvSetupHardware();

	/* *************************** TASK_1 **************************** */
	/*
	xTaskCreate(    LED_Toggel,
                            "LED_1 toggel",
                            100,
                            NULL,
                            1,
                            &LED_Toggel_handler
                          );
	*/
	
	/* ***************************** TASK_2 ************************** */
	/*
	 xTaskCreate(    LED_1,
                            "LED_1 toggel",
                            100,
                            NULL,
                            1,
                            &LED1_handeler
                          );

	
	xTaskCreate(    LED_2,
                            "LED_2 toggel",
                            100,
                            NULL,
                            2,
                            &LED2_handeler
                          );
	
	
	xTaskCreate(    LED_3,
                            "LED_3 toggel",
                            100,
                            NULL,
                            3,
                            &LED3_handeler
                          );
	*/
	/* ******************************** Task_3 **************************** */
	
	xTaskCreate(    Button_Task,
                            "Button task",
                            100,
                            NULL,
                            1,
                            &Button_Task_handeler
                          );
	
	
	xTaskCreate(    LED_state_1,
                            "LED will toggel for 400 ms",
                            100,
                            NULL,
                            2,
                            &LED_state_1_handeler
                          );
	
	
	xTaskCreate(    LED_state_2,
                            "LED will toggel for 100 ms",
                            100,
                            NULL,
                            3,
                            &LED_state_2_handeler
                          );
	
	
	xTaskCreate(    LED_state_3,
                            "LED will close",
                            100,
                            NULL,
                            4,
                            &LED_state_3_handeler
                          );
	
	/* **************************************************************** */
	
	
	
	vTaskStartScheduler();

	for( ;; );
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/


