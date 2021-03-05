/*******************************************************************************
* File Name: Outside.h  
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

#if !defined(CY_PINS_Outside_H) /* Pins Outside_H */
#define CY_PINS_Outside_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Outside_aliases.h"


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
} Outside_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Outside_Read(void);
void    Outside_Write(uint8 value);
uint8   Outside_ReadDataReg(void);
#if defined(Outside__PC) || (CY_PSOC4_4200L) 
    void    Outside_SetDriveMode(uint8 mode);
#endif
void    Outside_SetInterruptMode(uint16 position, uint16 mode);
uint8   Outside_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Outside_Sleep(void); 
void Outside_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Outside__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Outside_DRIVE_MODE_BITS        (3)
    #define Outside_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Outside_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Outside_SetDriveMode() function.
         *  @{
         */
        #define Outside_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Outside_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Outside_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Outside_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Outside_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Outside_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Outside_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Outside_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Outside_MASK               Outside__MASK
#define Outside_SHIFT              Outside__SHIFT
#define Outside_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Outside_SetInterruptMode() function.
     *  @{
     */
        #define Outside_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Outside_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Outside_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Outside_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Outside__SIO)
    #define Outside_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Outside__PC) && (CY_PSOC4_4200L)
    #define Outside_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Outside_USBIO_DISABLE              ((uint32)(~Outside_USBIO_ENABLE))
    #define Outside_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Outside_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Outside_USBIO_ENTER_SLEEP          ((uint32)((1u << Outside_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Outside_USBIO_SUSPEND_DEL_SHIFT)))
    #define Outside_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Outside_USBIO_SUSPEND_SHIFT)))
    #define Outside_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Outside_USBIO_SUSPEND_DEL_SHIFT)))
    #define Outside_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Outside__PC)
    /* Port Configuration */
    #define Outside_PC                 (* (reg32 *) Outside__PC)
#endif
/* Pin State */
#define Outside_PS                     (* (reg32 *) Outside__PS)
/* Data Register */
#define Outside_DR                     (* (reg32 *) Outside__DR)
/* Input Buffer Disable Override */
#define Outside_INP_DIS                (* (reg32 *) Outside__PC2)

/* Interrupt configuration Registers */
#define Outside_INTCFG                 (* (reg32 *) Outside__INTCFG)
#define Outside_INTSTAT                (* (reg32 *) Outside__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Outside_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Outside__SIO)
    #define Outside_SIO_REG            (* (reg32 *) Outside__SIO)
#endif /* (Outside__SIO_CFG) */

/* USBIO registers */
#if !defined(Outside__PC) && (CY_PSOC4_4200L)
    #define Outside_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Outside_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Outside_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Outside_DRIVE_MODE_SHIFT       (0x00u)
#define Outside_DRIVE_MODE_MASK        (0x07u << Outside_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Outside_H */


/* [] END OF FILE */
