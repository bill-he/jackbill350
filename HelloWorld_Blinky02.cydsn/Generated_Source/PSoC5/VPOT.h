/*******************************************************************************
* File Name: VPOT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VPOT_H) /* Pins VPOT_H */
#define CY_PINS_VPOT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VPOT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VPOT__PORT == 15 && ((VPOT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VPOT_Write(uint8 value);
void    VPOT_SetDriveMode(uint8 mode);
uint8   VPOT_ReadDataReg(void);
uint8   VPOT_Read(void);
void    VPOT_SetInterruptMode(uint16 position, uint16 mode);
uint8   VPOT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VPOT_SetDriveMode() function.
     *  @{
     */
        #define VPOT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VPOT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VPOT_DM_RES_UP          PIN_DM_RES_UP
        #define VPOT_DM_RES_DWN         PIN_DM_RES_DWN
        #define VPOT_DM_OD_LO           PIN_DM_OD_LO
        #define VPOT_DM_OD_HI           PIN_DM_OD_HI
        #define VPOT_DM_STRONG          PIN_DM_STRONG
        #define VPOT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VPOT_MASK               VPOT__MASK
#define VPOT_SHIFT              VPOT__SHIFT
#define VPOT_WIDTH              1u

/* Interrupt constants */
#if defined(VPOT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VPOT_SetInterruptMode() function.
     *  @{
     */
        #define VPOT_INTR_NONE      (uint16)(0x0000u)
        #define VPOT_INTR_RISING    (uint16)(0x0001u)
        #define VPOT_INTR_FALLING   (uint16)(0x0002u)
        #define VPOT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VPOT_INTR_MASK      (0x01u) 
#endif /* (VPOT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VPOT_PS                     (* (reg8 *) VPOT__PS)
/* Data Register */
#define VPOT_DR                     (* (reg8 *) VPOT__DR)
/* Port Number */
#define VPOT_PRT_NUM                (* (reg8 *) VPOT__PRT) 
/* Connect to Analog Globals */                                                  
#define VPOT_AG                     (* (reg8 *) VPOT__AG)                       
/* Analog MUX bux enable */
#define VPOT_AMUX                   (* (reg8 *) VPOT__AMUX) 
/* Bidirectional Enable */                                                        
#define VPOT_BIE                    (* (reg8 *) VPOT__BIE)
/* Bit-mask for Aliased Register Access */
#define VPOT_BIT_MASK               (* (reg8 *) VPOT__BIT_MASK)
/* Bypass Enable */
#define VPOT_BYP                    (* (reg8 *) VPOT__BYP)
/* Port wide control signals */                                                   
#define VPOT_CTL                    (* (reg8 *) VPOT__CTL)
/* Drive Modes */
#define VPOT_DM0                    (* (reg8 *) VPOT__DM0) 
#define VPOT_DM1                    (* (reg8 *) VPOT__DM1)
#define VPOT_DM2                    (* (reg8 *) VPOT__DM2) 
/* Input Buffer Disable Override */
#define VPOT_INP_DIS                (* (reg8 *) VPOT__INP_DIS)
/* LCD Common or Segment Drive */
#define VPOT_LCD_COM_SEG            (* (reg8 *) VPOT__LCD_COM_SEG)
/* Enable Segment LCD */
#define VPOT_LCD_EN                 (* (reg8 *) VPOT__LCD_EN)
/* Slew Rate Control */
#define VPOT_SLW                    (* (reg8 *) VPOT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VPOT_PRTDSI__CAPS_SEL       (* (reg8 *) VPOT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VPOT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VPOT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VPOT_PRTDSI__OE_SEL0        (* (reg8 *) VPOT__PRTDSI__OE_SEL0) 
#define VPOT_PRTDSI__OE_SEL1        (* (reg8 *) VPOT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VPOT_PRTDSI__OUT_SEL0       (* (reg8 *) VPOT__PRTDSI__OUT_SEL0) 
#define VPOT_PRTDSI__OUT_SEL1       (* (reg8 *) VPOT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VPOT_PRTDSI__SYNC_OUT       (* (reg8 *) VPOT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VPOT__SIO_CFG)
    #define VPOT_SIO_HYST_EN        (* (reg8 *) VPOT__SIO_HYST_EN)
    #define VPOT_SIO_REG_HIFREQ     (* (reg8 *) VPOT__SIO_REG_HIFREQ)
    #define VPOT_SIO_CFG            (* (reg8 *) VPOT__SIO_CFG)
    #define VPOT_SIO_DIFF           (* (reg8 *) VPOT__SIO_DIFF)
#endif /* (VPOT__SIO_CFG) */

/* Interrupt Registers */
#if defined(VPOT__INTSTAT)
    #define VPOT_INTSTAT            (* (reg8 *) VPOT__INTSTAT)
    #define VPOT_SNAP               (* (reg8 *) VPOT__SNAP)
    
	#define VPOT_0_INTTYPE_REG 		(* (reg8 *) VPOT__0__INTTYPE)
#endif /* (VPOT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VPOT_H */


/* [] END OF FILE */
