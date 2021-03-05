/*******************************************************************************
* File Name: Inside.h  
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

#if !defined(CY_PINS_Inside_ALIASES_H) /* Pins Inside_ALIASES_H */
#define CY_PINS_Inside_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Inside_0			(Inside__0__PC)
#define Inside_0_PS		(Inside__0__PS)
#define Inside_0_PC		(Inside__0__PC)
#define Inside_0_DR		(Inside__0__DR)
#define Inside_0_SHIFT	(Inside__0__SHIFT)
#define Inside_0_INTR	((uint16)((uint16)0x0003u << (Inside__0__SHIFT*2u)))

#define Inside_INTR_ALL	 ((uint16)(Inside_0_INTR))


#endif /* End Pins Inside_ALIASES_H */


/* [] END OF FILE */
