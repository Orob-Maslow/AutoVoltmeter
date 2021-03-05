/*******************************************************************************
* File Name: Battery.h  
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

#if !defined(CY_PINS_Battery_H) /* Pins Battery_H */
#define CY_PINS_Battery_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Battery_aliases.h"


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
} Battery_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Battery_Read(void);
void    Battery_Write(uint8 value);
uint8   Battery_ReadDataReg(void);
#if defined(Battery__PC) || (CY_PSOC4_4200L) 
    void    Battery_SetDriveMode(uint8 mode);
#endif
void    Battery_SetInterruptMode(uint16 position, uint16 mode);
uint8   Battery_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Battery_Sleep(void); 
void Battery_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Battery__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Battery_DRIVE_MODE_BITS        (3)
    #define Battery_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Battery_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Battery_SetDriveMode() function.
         *  @{
         */
        #define Battery_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Battery_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Battery_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Battery_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Battery_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Battery_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Battery_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Battery_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Battery_MASK               Battery__MASK
#define Battery_SHIFT              Battery__SHIFT
#define Battery_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Battery_SetInterruptMode() function.
     *  @{
     */
        #define Battery_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Battery_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Battery_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Battery_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Battery__SIO)
    #define Battery_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Battery__PC) && (CY_PSOC4_4200L)
    #define Battery_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Battery_USBIO_DISABLE              ((uint32)(~Battery_USBIO_ENABLE))
    #define Battery_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Battery_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Battery_USBIO_ENTER_SLEEP          ((uint32)((1u << Battery_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Battery_USBIO_SUSPEND_DEL_SHIFT)))
    #define Battery_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Battery_USBIO_SUSPEND_SHIFT)))
    #define Battery_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Battery_USBIO_SUSPEND_DEL_SHIFT)))
    #define Battery_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Battery__PC)
    /* Port Configuration */
    #define Battery_PC                 (* (reg32 *) Battery__PC)
#endif
/* Pin State */
#define Battery_PS                     (* (reg32 *) Battery__PS)
/* Data Register */
#define Battery_DR                     (* (reg32 *) Battery__DR)
/* Input Buffer Disable Override */
#define Battery_INP_DIS                (* (reg32 *) Battery__PC2)

/* Interrupt configuration Registers */
#define Battery_INTCFG                 (* (reg32 *) Battery__INTCFG)
#define Battery_INTSTAT                (* (reg32 *) Battery__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Battery_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Battery__SIO)
    #define Battery_SIO_REG            (* (reg32 *) Battery__SIO)
#endif /* (Battery__SIO_CFG) */

/* USBIO registers */
#if !defined(Battery__PC) && (CY_PSOC4_4200L)
    #define Battery_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Battery_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Battery_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Battery_DRIVE_MODE_SHIFT       (0x00u)
#define Battery_DRIVE_MODE_MASK        (0x07u << Battery_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Battery_H */


/* [] END OF FILE */
