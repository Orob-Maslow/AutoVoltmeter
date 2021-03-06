/*******************************************************************************
* File Name: TX.h
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_TX_H
#define CY_SW_TX_UART_TX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define TX_BAUD_RATE                      (115200u)
#define TX_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(TX_PIN_STATIC_MODE == 1u)
    void TX_Start(void) ;
#else
    void TX_StartEx(uint8 port, uint8 pin) ;
#endif /* (TX_PIN_STATIC_MODE == 1u) */

void TX_Stop(void) ;
void TX_PutChar(uint8 txDataByte) ;
void TX_PutString(const char8 string[]) ;
void TX_PutArray(const uint8 array[], uint32 byteCount) ;
void TX_PutHexByte(uint8 txHexByte) ;
void TX_PutHexInt(uint16 txHexInt) ;
void TX_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_TX_H */


/* [] END OF FILE */
