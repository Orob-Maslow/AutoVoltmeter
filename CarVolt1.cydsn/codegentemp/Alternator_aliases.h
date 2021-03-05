/*******************************************************************************
* File Name: Alternator.h  
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

#if !defined(CY_PINS_Alternator_ALIASES_H) /* Pins Alternator_ALIASES_H */
#define CY_PINS_Alternator_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Alternator_0			(Alternator__0__PC)
#define Alternator_0_PS		(Alternator__0__PS)
#define Alternator_0_PC		(Alternator__0__PC)
#define Alternator_0_DR		(Alternator__0__DR)
#define Alternator_0_SHIFT	(Alternator__0__SHIFT)
#define Alternator_0_INTR	((uint16)((uint16)0x0003u << (Alternator__0__SHIFT*2u)))

#define Alternator_INTR_ALL	 ((uint16)(Alternator_0_INTR))


#endif /* End Pins Alternator_ALIASES_H */


/* [] END OF FILE */
