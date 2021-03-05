/*******************************************************************************
* File Name: Battery.h  
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

#if !defined(CY_PINS_Battery_ALIASES_H) /* Pins Battery_ALIASES_H */
#define CY_PINS_Battery_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Battery_0			(Battery__0__PC)
#define Battery_0_PS		(Battery__0__PS)
#define Battery_0_PC		(Battery__0__PC)
#define Battery_0_DR		(Battery__0__DR)
#define Battery_0_SHIFT	(Battery__0__SHIFT)
#define Battery_0_INTR	((uint16)((uint16)0x0003u << (Battery__0__SHIFT*2u)))

#define Battery_INTR_ALL	 ((uint16)(Battery_0_INTR))


#endif /* End Pins Battery_ALIASES_H */


/* [] END OF FILE */
