/**
 * \file
 * \brief This is a configuration file for the RNet stack
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * Here the stack can be configured using macros.
 */

#ifndef __RNET_APP_CONFIG__
#define __RNET_APP_CONFIG__

#include "Platform.h"
#if PL_CONFIG_HAS_RADIO
/*! type ID's for application messages */
typedef enum {
  RAPP_MSG_TYPE_STDIN = 0x00,
  RAPP_MSG_TYPE_STDOUT = 0x01,
  RAPP_MSG_TYPE_STDERR = 0x02,
  RAPP_MSG_TYPE_ACCEL = 0x03,
  RAPP_MSG_TYPE_DATA = 0x04,
  RAPP_MSG_TYPE_JOYSTICK_XY = 0x05,
  RAPP_MSG_TYPE_JOYSTICK_BTN = 0x54, /* Joystick button message (data is one byte: 'A', 'B', ... 'F' and 'K') */
  RAPP_MSG_TYPE_SIGNALS = 0xAC,
} RAPP_MSG_Type;

typedef enum {
  RAPP_BTN_MSG_DRIVE = 0x47,
  RAPP_BTN_MSG_CALIB= 0x43,
  RAPP_BTN_MSG_STOP = 0x47,
  RAPP_BTN_MSG_HORN = 'A',
} RAPP_BTN_MSG_t;

typedef enum {
  RAPP_SIG_A = 'A',
  RAPP_SIG_B= 'B',
  RAPP_SIG_C = 'C',
  RAPP_SIG_T = 'T',
} RAPP_SIG_MSG_t;

#endif /* PL_CONFIG_HAS_RADIO */

#endif /* __RNET_APP_CONFIG__ */
