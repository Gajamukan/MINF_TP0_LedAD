/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //Initialisation de LCD
            lcd_init();
            lcd_bl_on();
            
            //Ecriture sur la premi�re ligne
            lcd_gotoxy(1,1);
            printf_lcd("TP0 LED + AD 2023-24" );
            
            //Ecriture sur la deuxi�me ligne
            lcd_gotoxy(1,2);
            printf_lcd("Subramaniyam");
            
            //Initialisation de ADC
            BSP_InitADC10();
            
            //Allumer tous les LEDs
            LED0_W = 0;
            LED1_W = 0;
            LED2_W = 0;
            LED3_W = 0;
            LED4_W = 0;
            LED5_W = 0;
            LED6_W = 0;
            LED7_W = 0;

            //D�marrer le timer
            DRV_TMR0_Start();
             
            //Passer dans l'�tat WAIT
            appData.state = APP_STATE_WAIT;
            
           break;
        }
        
        case APP_STATE_WAIT:
        {
            //Ne rien faire
           break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            //Eteindre les leds
            static bool Offled = true;
            if (Offled)
            {
             BSP_LEDOff(BSP_LED_0);
             BSP_LEDOff(BSP_LED_1);
             BSP_LEDOff(BSP_LED_2);
             BSP_LEDOff(BSP_LED_3);
             BSP_LEDOff(BSP_LED_4);
             BSP_LEDOff(BSP_LED_5);
             BSP_LEDOff(BSP_LED_6);
             BSP_LEDOff(BSP_LED_7);
             Offled = false;
            } 
            
            //Lecture des ADC
            appData.AdcRes = BSP_ReadAllADC();
            
            //Afficher sur la 3�me ligne 
            lcd_gotoxy(1,3);
            printf_lcd("Ch0 %4d Ch1 %4d ",appData.AdcRes.Chan0 ,appData.AdcRes.Chan1);

            //Appel de fonction chenillard
            Chenillard ();
            
            //Passer dans l'�tat WAIT
             appData.state = APP_STATE_WAIT;
        
           break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void APP_UpdateState (APP_STATES NewState )
{
    appData.state = NewState;
}

void Chenillard (void)
{
    static uint32_t i = 0;
    
    switch (i)
    {
        case 0 : 
        {
            BSP_LEDOff(BSP_LED_7);
            BSP_LEDOn(BSP_LED_0);
            i++;
           break;
        }
        
        case 1 : 
        {
            LED0_W = 1;
            LED1_W = 0;
            i++;
           break;
        }
        
        case 2 : 
        {
            LED1_W = 1;
            LED2_W = 0;
            i++;
           break;
        }
                
        case 3 : 
        {
            LED2_W = 1;
            LED3_W = 0;
            i++;
           break;
        }
                        
        case 4 : 
        {
            LED3_W = 1;
            LED4_W = 0;
            i++;
           break;
        }
                                
        case 5 : 
        {
            LED4_W = 1;
            LED5_W = 0;
            i++;
           break;
        }
                                        
        case 6 : 
        {
            LED5_W = 1;
            LED6_W = 0;
            i++;
           break;
        }
                                                
        case 7 : 
        {
            LED6_W = 1;
            LED7_W = 0;
            i++;
           break;
        }
        
         /* The default state should never be executed. */
        default:
        {
            i = 0;
            /* TODO: Handle error in application's state machine. */
           break;
        }
    }
}

/*******************************************************************************
 End of File
 */
