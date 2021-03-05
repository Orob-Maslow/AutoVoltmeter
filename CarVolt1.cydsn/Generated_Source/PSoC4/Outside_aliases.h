/*******************************************************************************
* File Name: Outside.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Outside_ALIASES_H) /* Pins Outside_ALIASES_H */
#define CY_PINS_Outside_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Outside_0			(Outside__0__PC)
#define Outside_0_PS		(Outside__0__PS)
#define Outside_0_PC		(Outside__0__PC)
#define Outside_0_DR		(Outside__0__DR)
#define Outside_0_SHIFT	(Outside__0__SHIFT)
#define Outside_0_INTR	((uint16)((uint16)0x0003u << (Outside__0__SHIFT*2u)))

#define Outside_INTR_ALL	 ((uint16)(Outside_0_INTR))


#endif /* End Pins Outside_ALIASES_H */


/* [] END OF FILE */
