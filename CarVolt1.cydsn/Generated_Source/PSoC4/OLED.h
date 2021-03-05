/*******************************************************************************
* File Name: OLED.h
* Version 1.20
*
* Description:
*  This header file contains registers and constants associated with the
*  I2C LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_LCD_OLED_H)
#define CY_I2C_LCD_OLED_H

#include "cytypes.h"
#include "cyfitter.h"

#include "I2C.h"

#if defined(I2C_SCB_MODE)
    #include "I2C_I2C.h"
#endif /* I2C_M_SCB_MODE */


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* This condition checks if I2C Master implemented on SCB
* block. There is mismatch in function names between I2C Master that is
* implemented on SCB and I2C Master that is implemented on UDB.
*/
#if defined(I2C_SCB_MODE)
    /* In this case always returns - "true" */
    #define OLED_IS_SCB_MASTER_USED     (0x01u == 0x01u)
#else
    /* Always "false" */
    #define OLED_IS_SCB_MASTER_USED     (0x01u == 0x00u)
#endif /* I2C_M_SCB_MODE */

#define OLED_CUSTOM_CHAR_SET            (0x00u)

/* Custom character set types */
#define OLED_NONE                       (0u)    /* No Custom Fonts      */
#define OLED_HORIZONTAL_BG              (1u)    /* Horizontal Bar Graph */
#define OLED_VERTICAL_BG                (2u)    /* Vertical Bar Graph   */
#define OLED_USER_DEFINED               (3u)    /* User Defined Fonts   */

#define OLED_COMMAND_FORMAT             (1u)

/* Possible command format values */
#define OLED_NXP_PCF2119X               (0x00u)
#define OLED_CUSTOM                     (0x01u)

/********************
* Generated Code
********************/
/* Indexes of command patterns in the look-up array. Required for a quick 
* access for the command.
*/
#define OLED_WRITE_DATA (0x00u)
#define OLED_DISPLAY_ON_CURSOR_OFF (0x0Cu)
#define OLED_DISPLAY_CURSOR_OFF (0x08u)
#define OLED_DDRAM_0 (0x80u)
#define OLED_CURSOR_HOME (0x02u)
#define OLED_RESET_CURSOR_POSITION (0x03u)
#define OLED_CURSOR_SH_LEFT (0x10u)
#define OLED_CURSOR_SH_RIGHT (0x14u)
#define OLED_DISPLAY_CURSOR_ON (0x0Eu)
#define OLED_CURSOR_WINK (0x0Du)
#define OLED_CURSOR_BLINK (0x0Fu)
#define OLED_CLEAR_DISPLAY (0x01u)
#define OLED_CGRAM_0 (0x40u)
#define OLED_DISPLAY_2_LINES_5X10 (0x24u)
#define OLED_CURSOR_RIGHT (0x06u)
#define OLED_CURSOR_LEFT (0x04u)


/***************************************
*        Function Prototypes
***************************************/
void OLED_Init(void) ;
void OLED_Enable(void) ;
void OLED_Start(void) ;
void OLED_Stop(void) ;
void OLED_WriteControl(uint8 cByte) ;
void OLED_WriteData(uint8 dByte) ;
void OLED_PrintString(char8 const string[]) ;
void OLED_Position(uint8 row, uint8 column) ;
void OLED_PutChar(char8 character) ;
void OLED_SetAddr(uint8 address) ;
void OLED_HandleCustomCommand(uint8 cmdId, uint8 dataLength, uint8 const cmdData[])
                                            ;
void OLED_HandleOneByteCommand(uint8 cmdId, uint8 cmdByte)
                                                        ;
/* ASCII Conversion Routines */
void OLED_PrintInt8(uint8 value) ;
void OLED_PrintInt16(uint16 value) ;
void OLED_PrintNumber(uint16 value) ;

#if((OLED_CUSTOM_CHAR_SET == OLED_VERTICAL_BG) || \
                (OLED_CUSTOM_CHAR_SET == OLED_HORIZONTAL_BG))

    void  OLED_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void OLED_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((OLED_CUSTOM_CHAR_SET == OLED_VERTICAL_BG) ||
       * (OLED_CUSTOM_CHAR_SET == OLED_HORIZONTAL_BG))
       */

#if(OLED_CUSTOM_CHAR_SET != OLED_NONE)

    void OLED_LoadCustomFonts(uint8 const customData[])
                            ;

#endif /* ((OLED_CUSTOM_CHAR_SET == OLED_USER_DEFINED) */


/***************************************
*        Macros
***************************************/

/* Clear Macro */
#define OLED_ClearDisplay()            OLED_WriteControl(OLED_CLEAR_DISPLAY)
/* Off Macro */
#define OLED_DisplayOff()              OLED_WriteControl(OLED_DISPLAY_CURSOR_OFF)
/* On Macro */
#define OLED_DisplayOn()               OLED_WriteControl(OLED_DISPLAY_ON_CURSOR_OFF)

/* Function-like macros for handling I2C MAster API names on SCB and UDB */
#if(OLED_IS_SCB_MASTER_USED)
    #define OLED_MasterWriteBuf(slaveAddress, wrData, cnt, mode)  \
                                I2C_I2CMasterWriteBuf(slaveAddress, wrData, cnt, mode)

    #define OLED_MasterReadStatus()     I2C_I2CMasterStatus()
#else
    #define OLED_MasterWriteBuf(slaveAddress, wrData, cnt, mode)  \
                                I2C_MasterWriteBuf(slaveAddress, wrData, cnt, mode)

    #define OLED_MasterReadStatus()     I2C_MasterStatus()
#endif /* OLED_IS_SCB_MASTER_USED */


#define OLED_AddrStart(addr) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_Start();\
                                                }while(0)

#define OLED_AddrStop(addr) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_Stop(); \
                                                }while(0)

#define OLED_AddrDisplayOn(addr) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_DisplayOn();\
                                                }while(0)

#define OLED_AddrDisplayOff(addr) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_DisplayOff();\
                                                }while(0)

#define OLED_AddrPrintString(addr, str) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_PrintString(str);\
                                                }while(0)

#define OLED_AddrPutChar(addr, ch) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_PutChar(ch);\
                                               }while(0)

#define OLED_AddrPosition(addr, row, col) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_Position(row, col);\
                                                }while(0)

#define OLED_AddrWriteData(addr, dByte) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_WriteData(dByte);\
                                                }while(0)

#define OLED_AddrWriteControl(addr, cByte) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_WriteControl(cByte);\
                                                }while(0)

#define OLED_AddrClearDisplay(addr) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_ClearDisplay();\
                                                }while(0)

#define OLED_AddrEnable(addr) \
                                                do {\
                                                    OLED_SetAddr(addr); \
                                                    OLED_Enable();\
                                                }while(0)

#define OLED_AddrPrintInt8(addr, value) \
                                                do {\
                                                    OLED_SetAddr(addr); \
                                                    OLED_PrintInt8(value);\
                                                }while(0)
                                                
#define OLED_AddrPrintInt16(addr, value) \
                                                do {\
                                                    OLED_SetAddr(addr); \
                                                    OLED_PrintInt16(value);\
                                                }while(0)
                                                
#define OLED_AddrPrintNumber(addr, value) \
                                                do {\
                                                    OLED_SetAddr(addr); \
                                                    OLED_PrintNumber(value);\
                                                }while(0)

#if(OLED_CUSTOM_CHAR_SET != OLED_NONE)

    #define OLED_AddrLoadCustomFonts(addr, customFont) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_LoadCustomFonts(customFont);\
                                                }while(0)

#endif /* (OLED_CUSTOM_CHAR_SET != OLED_NONE) */


#if((OLED_CUSTOM_CHAR_SET == OLED_VERTICAL_BG) || \
                (OLED_CUSTOM_CHAR_SET == OLED_HORIZONTAL_BG))

    #define OLED_AddrDrawHorizontalBG(addr, row, column, maxCharacters, value) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_DrawHorizontalBG(row,column,maxCharacters,value);\
                                                }while(0)


    #define OLED_AddrDrawVerticalBG(addr, row, column, maxCharacters, value) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_DrawVerticalBG(row, column, maxCharacters, value);\
                                                }while(0)

#endif /* ((OLED_CUSTOM_CHAR_SET == OLED_VERTICAL_BG) ||
       * (OLED_CUSTOM_CHAR_SET == OLED_HORIZONTAL_BG))
       */

#define OLED_AddrHandleCustomCommand(addr, cmdId, dataLength, cmdData) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_HandleCustomCommand(cmdId, dataLength, cmdData);\
                                                }while(0)

#define OLED_AddrHandleOneByteCommand(addr, cmdId, cmdByte) \
                                                do {\
                                                    OLED_SetAddr(addr);\
                                                    OLED_HandleOneByteCommand(cmdId, cmdByte);\
                                                }while(0)

/********************
* Generated Code
********************/



/***************************************
*           Global Variables
***************************************/

extern uint8 OLED_initVar;
extern uint8 const CYCODE OLED_customFonts[64u];


/***************************************
*           API Constants
***************************************/

#define OLED_ADDRESS_SHIFT              (0x01u)

/* Default I2C address in 7-bit mode */
#define OLED_DEFAULT_I2C_ADDRESS        ((uint8)((uint8)(60u) >> \
                                                                            OLED_ADDRESS_SHIFT))

/* This value should be generated by API customizer */
#define OLED_NUM_COMMANDS               (16u)

/********************
* Generated Code
********************/
/* Legacy names from Character LCD */
#define OLED_WRITE_DATA_IDX (0x00u)
#define OLED_DISPLAY_ON_CURSOR_OFF_IDX (0x01u)
#define OLED_DISPLAY_CURSOR_OFF_IDX (0x02u)
#define OLED_DDRAM_0_IDX (0x03u)
#define OLED_CURSOR_HOME_IDX (0x04u)
#define OLED_RESET_CURSOR_POSITION_IDX (0x05u)
#define OLED_CURSOR_SH_LEFT_IDX (0x06u)
#define OLED_CURSOR_SH_RIGHT_IDX (0x07u)
#define OLED_DISPLAY_CURSOR_ON_IDX (0x08u)
#define OLED_CURSOR_WINK_IDX (0x09u)
#define OLED_CURSOR_BLINK_IDX (0x0Au)
#define OLED_CLEAR_DISPLAY_IDX (0x0Bu)
#define OLED_CGRAM_0_IDX (0x0Cu)
#define OLED_DISPLAY_2_LINES_5X10_IDX (0x0Du)
#define OLED_CURSOR_RIGHT_IDX (0x0Eu)
#define OLED_CURSOR_LEFT_IDX (0x0Fu)

#define OLED_DISPLAY_2_LINES_5x10       (OLED_DISPLAY_2_LINES_5X10)
#define OLED_CURSOR_AUTO_INCR_ON        (OLED_CURSOR_RIGHT)

/********************
* Generated Code
********************/
#define OLED_DDRAM_0_DATA_LEN (0x01u)
#define OLED_CGRAM_0_DATA_LEN (0x09u)

#if(OLED_IS_SCB_MASTER_USED)
    #define OLED_MODE_COMPLETE_XFER         (I2C_I2C_MODE_COMPLETE_XFER)
    #define OLED_WRITE_COMPLETE             (I2C_I2C_MSTAT_WR_CMPLT)
#else
    #define OLED_MODE_COMPLETE_XFER         (I2C_MODE_COMPLETE_XFER)
    #define OLED_WRITE_COMPLETE             (I2C_MSTAT_WR_CMPLT)
#endif /* OLED_IS_SCB_MASTER_USED */

/* Constants for PrintNumber routine */
#define OLED_NUMBER_OF_REMAINDERS           (0x05u)
#define OLED_TEN                            (0x0Au)

/* Nibble Offset and Mask */
#define OLED_NIBBLE_SHIFT                   (0x04u)
#define OLED_NIBBLE_MASK                    (0x0Fu)
#define OLED_BUFF_SIZE                      (0x100u)
#define OLED_LENGTH_2_BYTES                 (0x02u)
#define OLED_COMMAND_BYTE_INDEX             (0x02u)

/* Delay value required for some commands to execute */
#define OLED_CMOMMAND_DELAY                 (1500u)

/* LCD Module RAM Address Constants */
#if (OLED_COMMAND_FORMAT == OLED_NXP_PCF2119X)
    #define OLED_ROW_0_START                    (0x80u)
    #define OLED_ROW_1_START                    (0xC0u)
    #define OLED_ROW_2_START                    (0x94u)
    #define OLED_ROW_3_START                    (0xD4u)
#else
    #define OLED_ROW_0_START                    (0x00u)
    #define OLED_ROW_1_START                    (0x40u)
    #define OLED_ROW_2_START                    (0x14u)
    #define OLED_ROW_3_START                    (0x54u)
#endif /* (OLED_COMMAND_FORMAT == OLED_NXP_PCF2119X)  */

/* Custom character handling related constants */
#if(OLED_CUSTOM_CHAR_SET != OLED_NONE)
    #define OLED_CHARACTER_WIDTH                (0x05u)
    #define OLED_CHARACTER_HEIGHT               (0x08u)
    #define OLED_CUSTOM_CHAR_SET_LEN            (0x40u)
#endif /* (OLED_CUSTOM_CHAR_SET != OLED_NONE) */

#define OLED_CUSTOM_CHAR_NUM                (0x08u)

#define OLED_ONE_BYTE_LEN                   (0x01u)

/* Other constants */
#define OLED_BYTE_UPPER_NIBBLE_SHIFT        (0x04u)
#define OLED_BYTE_LOWER_NIBBLE_MASK         (0x0Fu)
#define OLED_U16_UPPER_BYTE_SHIFT           (0x08u)
#define OLED_U16_LOWER_BYTE_MASK            (0xFFu)
                                                    
/* Custom Character References */
#define OLED_CUSTOM_0                       (0x00u)
#define OLED_CUSTOM_1                       (0x01u)
#define OLED_CUSTOM_2                       (0x02u)
#define OLED_CUSTOM_3                       (0x03u)
#define OLED_CUSTOM_4                       (0x04u)
#define OLED_CUSTOM_5                       (0x05u)
#define OLED_CUSTOM_6                       (0x06u)
#define OLED_CUSTOM_7                       (0x07u)

#if (OLED_COMMAND_FORMAT == OLED_NXP_PCF2119X)
    
    /* Command send opcode */
    #define OLED_COMMAND_SEND               (0x00u) 
    
    #define OLED_SET_EXTENDED_FUNC          (0x35u)      
    #define OLED_SPLIT_SCREEN               (0x02u)
    #define OLED_DISP_CONF                  (0x04u)
    
    #define OLED_ICON_CTL                   (0x08u)  
    #define OLED_VLCD_SET                   (0xA0u)
    #define OLED_FUNCTION_SET_STANDARD      (0x34u)  /* Select Standard Instruction set, 2x16 display */

    /* This is mask for character set "S" that is used in NXP
    * compatible LCD Module.
    */
    #define OLED_CHARACTER_SET_S_MASK       ((uint8) (0x80u))
    
#endif /* (OLED_COMMAND_FORMAT == OLED_NXP_PCF2119X) */


#endif /* CY_I2C_LCD_OLED_H */


/* [] END OF FILE */
