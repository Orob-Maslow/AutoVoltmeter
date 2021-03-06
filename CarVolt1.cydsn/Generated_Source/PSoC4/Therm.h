/*******************************************************************************
* File Name: Therm.h
* Version 1.20
*
* Description:
*  This header file provides registers and constants associated with the
*  ThermistorCalc component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_THERMISTOR_CALC_Therm_H)
#define CY_THERMISTOR_CALC_Therm_H

#include "cyfitter.h"
#include "CyLib.h"

#define Therm_IMPLEMENTATION         (1u)
#define Therm_EQUATION_METHOD        (0u)
#define Therm_LUT_METHOD             (1u)

#if (Therm_IMPLEMENTATION == Therm_EQUATION_METHOD)
    #include <math.h>
#endif /* (Therm_IMPLEMENTATION == Therm_EQUATION_METHOD) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Therm_REF_RESISTOR           (10000)
#define Therm_REF_RES_SHIFT          (0u)
#define Therm_ACCURACY               (50u)
#define Therm_MIN_TEMP               (-20 * Therm_SCALE)


/***************************************
*        Function Prototypes
***************************************/

uint32 Therm_GetResistance(int16 vReference, int16 vThermistor)
                                      ;
int16 Therm_GetTemperature(uint32 resT) ;


/***************************************
*           API Constants
***************************************/

#define Therm_K2C                    (273.15)
#define Therm_SCALE                  (100)
#define Therm_LUT_SIZE               (201u)


#endif /* CY_THERMISTOR_CALC_Therm_H */


/* [] END OF FILE */
