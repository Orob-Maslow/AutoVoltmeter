/*******************************************************************************
* File Name: Inside.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Inside_H) /* Pins Inside_H */
#define CY_PINS_Inside_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Inside_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Inside_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Inside_Read(void);
void    Inside_Write(uint8 value);
uint8   Inside_ReadDataReg(void);
#if defined(Inside__PC) || (CY_PSOC4_4200L) 
    void    Inside_SetDriveMode(uint8 mode);
#endif
void    Inside_SetInterruptMode(uint16 position, uint16 mode);
uint8   Inside_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Inside_Sleep(void); 
void Inside_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Inside__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Inside_DRIVE_MODE_BITS        (3)
    #define Inside_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Inside_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Inside_SetDriveMode() function.
         *  @{
         */
        #define Inside_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Inside_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Inside_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Inside_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Inside_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Inside_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Inside_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Inside_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Inside_MASK               Inside__MASK
#define Inside_SHIFT              Inside__SHIFT
#define Inside_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Inside_SetInterruptMode() function.
     *  @{
     */
        #define Inside_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Inside_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Inside_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Inside_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Inside__SIO)
    #define Inside_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Inside__PC) && (CY_PSOC4_4200L)
    #define Inside_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Inside_USBIO_DISABLE              ((uint32)(~Inside_USBIO_ENABLE))
    #define Inside_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Inside_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Inside_USBIO_ENTER_SLEEP          ((uint32)((1u << Inside_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Inside_USBIO_SUSPEND_DEL_SHIFT)))
    #define Inside_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Inside_USBIO_SUSPEND_SHIFT)))
    #define Inside_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Inside_USBIO_SUSPEND_DEL_SHIFT)))
    #define Inside_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Inside__PC)
    /* Port Configuration */
    #define Inside_PC                 (* (reg32 *) Inside__PC)
#endif
/* Pin State */
#define Inside_PS                     (* (reg32 *) Inside__PS)
/* Data Register */
#define Inside_DR                     (* (reg32 *) Inside__DR)
/* Input Buffer Disable Override */
#define Inside_INP_DIS                (* (reg32 *) Inside__PC2)

/* Interrupt configuration Registers */
#define Inside_INTCFG                 (* (reg32 *) Inside__INTCFG)
#define Inside_INTSTAT                (* (reg32 *) Inside__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Inside_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Inside__SIO)
    #define Inside_SIO_REG            (* (reg32 *) Inside__SIO)
#endif /* (Inside__SIO_CFG) */

/* USBIO registers */
#if !defined(Inside__PC) && (CY_PSOC4_4200L)
    #define Inside_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Inside_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Inside_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Inside_DRIVE_MODE_SHIFT       (0x00u)
#define Inside_DRIVE_MODE_MASK        (0x07u << Inside_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Inside_H */


/* [] END OF FILE */
