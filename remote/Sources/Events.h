/* ###################################################################
**     Filename    : Events.h
**     Project     : INTRO_Remote_Master
**     Processor   : MK20DX128VFT5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-20, 21:05, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "LEDPin1.h"
#include "BitIoLdd17.h"
#include "SW1.h"
#include "BitIoLdd10.h"
#include "SW2.h"
#include "BitIoLdd11.h"
#include "SW3.h"
#include "BitIoLdd12.h"
#include "SW4.h"
#include "BitIoLdd13.h"
#include "SW5.h"
#include "BitIoLdd14.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "SW6.h"
#include "BitIoLdd15.h"
#include "SW7.h"
#include "BitIoLdd16.h"
#include "PTA.h"
#include "PTB.h"
#include "PTD.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "KIN1.h"
#include "KSDK1.h"
#include "HF1.h"
#include "CS1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX128EX5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
