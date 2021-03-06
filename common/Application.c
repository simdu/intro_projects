/**
 * \file
 * \brief Main application file
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This provides the main application entry point.
 */

#include "Platform.h"
#include "Application.h"
#include "Event.h"
#include "LED.h"
#include "WAIT1.h"
#include "CS1.h"
#include "Keys.h"
#include "KeyDebounce.h"
#include "KIN1.h"
#include "Sem.h"
#include "Remote.h"
#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
#endif
#if PL_CONFIG_HAS_BUZZER
#include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_RTOS
#include "FRTOS1.h"
#include "RTOS.h"
#endif
#if PL_CONFIG_HAS_SHELL
#include "Shell.h"
#endif
#if PL_CONFIG_HAS_QUADRATURE
#include "Q4CLeft.h"
#include "Q4CRight.h"
#endif
#if PL_CONFIG_HAS_MOTOR
#include "Motor.h"
#endif
#if PL_CONFIG_BOARD_IS_ROBO_V2
#include "PORT_PDD.h"
#endif

#if PL_CONFIG_HAS_REFLECTANCE
#include "LineFollow.h"
#endif

static bool driveON = TRUE;

void setInterfaceMode(bool mode) {
	driveON = mode;
}

#if PL_CONFIG_HAS_EVENTS
void APP_EventHandler(EVNT_Handle event) {
	switch (event) {
	case EVNT_STARTUP:
#if PL_CONFIG_HAS_LEDS
		LED1_On(); /* just do something */
#endif
#if PL_CONFIG_HAS_BUZZER
		BUZ_PlayTune(BUZ_TUNE_WELCOME);
#endif
		break;
	case EVNT_LED_HEARTBEAT:
#if PL_CONFIG_HAS_LEDS
		LED1_Neg();
#endif
		break;

#if PL_CONFIG_HAS_KEYS
#if PL_CONFIG_NOF_KEYS>=1
	case EVNT_SW1_PRESSED:
	case EVNT_SW1_LPRESSED:
#if PL_CONFIG_BOARD_IS_FRDM
		REMOTE_Horn();
#endif

#if PL_CONFIG_HAS_LINE_FOLLOW
		LF_StartFollowing();
#endif

#if PL_CONFIG_HAS_LCD
		if (driveON) {
			EVNT_SetEvent(EVNT_LCD_BTN_RIGHT);
			SHELL_SendString("LCD Right\r\n");
		}
#endif

		break;
#endif
#if PL_CONFIG_NOF_KEYS>=2
	case EVNT_SW2_PRESSED:
#if PL_CONFIG_HAS_LCD
		if (driveON) {
			EVNT_SetEvent(EVNT_LCD_BTN_LEFT);
			SHELL_SendString("LCD Left\r\n");
		}
#endif
		break;
#endif
#if PL_CONFIG_NOF_KEYS>=3
	case EVNT_SW3_PRESSED:
#if PL_CONFIG_HAS_JOYSTICK
		REMOTE_StartCalib();
#endif
#if PL_CONFIG_HAS_LCD
		if (driveON) {
			EVNT_SetEvent(EVNT_LCD_BTN_DOWN);
			SHELL_SendString("LCD Down\r\n");
		}else{
			 REMOTE_Turn();
		}
#endif
		break;
#endif
#if PL_CONFIG_NOF_KEYS>=4
	case EVNT_SW4_PRESSED:
#if PL_CONFIG_HAS_LCD
		if (driveON) {
			EVNT_SetEvent(EVNT_LCD_BTN_CENTER);
			SHELL_SendString("LCD Center\r\n");
		}
#endif
		break;
	case EVNT_SW4_LPRESSED:
#if PL_CONFIG_HAS_LCD
		EVNT_SetEvent(EVNT_LCD_BTN_CENTER);
		driveON = TRUE;
		REMOTE_Stop();
		REMOTE_SetDriveMode();
		SHELL_SendString("Stop/DriveMode\r\n");
#endif
		break;
#endif
#if PL_CONFIG_NOF_KEYS>=5
	case EVNT_SW5_PRESSED:
#if PL_CONFIG_HAS_JOYSTICK
		REMOTE_SetOnOff(TRUE);
#endif
#if PL_CONFIG_HAS_LCD
		if (driveON) {
			EVNT_SetEvent(EVNT_LCD_BTN_UP);
			SHELL_SendString("LCD Up\r\n");
		} else{
			REMOTE_StartLineFollowing();
			SHELL_SendString("State Maschine next state\r\n");
		}
#endif
		break;
#endif
#if PL_CONFIG_NOF_KEYS>=6
	case EVNT_SW6_PRESSED:
#if PL_CONFIG_HAS_JOYSTICK
		REMOTE_Stop();
		REMOTE_SetOnOff(FALSE);
#endif
		SHELL_SendString("Remote OFF\r\n");
		break;
#endif
#if PL_CONFIG_NOF_KEYS>=7
	case EVNT_SW7_PRESSED:
	case EVNT_SW7_LPRESSED:
#if PL_CONFIG_HAS_JOYSTICK
		REMOTE_SetDriveMode();
#endif
		//REMOTE_StartLineFollowing();
//		REMOTE_SendSpeed(30);
		SHELL_SendString("Start Line Following\r\n");
		break;
#endif
#endif /* PL_CONFIG_HAS_KEYS */

	default:
		break;
		/* \todo extend handler as needed */
	} /* switch */
	//REMOTE_EventHandler(EVNT_Handle event)
}
#endif /* PL_CONFIG_HAS_EVENTS */

static const KIN1_UID RoboIDs[] = {
/* 0: L20, V2 */{ { 0x00, 0x03, 0x00, 0x00, 0x4E, 0x45, 0xB7, 0x21, 0x4E, 0x45,
		0x32, 0x15, 0x30, 0x02, 0x00, 0x13 } },
/* 1: L21, V2 */{ { 0x00, 0x05, 0x00, 0x00, 0x4E, 0x45, 0xB7, 0x21, 0x4E, 0x45,
		0x32, 0x15, 0x30, 0x02, 0x00, 0x13 } },
/* 2: L4, V1  */{ { 0x00, 0x0B, 0xFF, 0xFF, 0x4E, 0x45, 0xFF, 0xFF, 0x4E, 0x45,
		0x27, 0x99, 0x10, 0x02, 0x00, 0x24 } }, /* revert right motor */
};

static void APP_AdoptToHardware(void) {
	KIN1_UID id;
	uint8_t res;

	res = KIN1_UIDGet(&id);
	if (res != ERR_OK) {
		for (;;)
			; /* error */
	}
#if PL_CONFIG_HAS_MOTOR
	MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* revert left motor */
	(void)Q4CLeft_SwapPins(TRUE);
	(void)Q4CRight_SwapPins(TRUE);

	if (KIN1_UIDSame(&id, &RoboIDs[2])) { /* L4 */
		MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* revert left motor */
#if PL_CONFIG_HAS_QUADRATURE
		(void)Q4CLeft_SwapPins(TRUE);
		(void)Q4CRight_SwapPins(TRUE);
#endif
	}
#endif
#if PL_CONFIG_HAS_QUADRATURE && PL_CONFIG_BOARD_IS_ROBO_V2
	/* pull-ups for Quadrature Encoder Pins */
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 10, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 10, PORT_PDD_PULL_ENABLE);
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 11, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 11, PORT_PDD_PULL_ENABLE);
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 16, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 16, PORT_PDD_PULL_ENABLE);
	PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 17, PORT_PDD_PULL_UP);
	PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 17, PORT_PDD_PULL_ENABLE);
#endif
}

void APP_Start(void) {
#if PL_CONFIG_HAS_RTOS
#if configUSE_TRACE_HOOKS
	PTRC1_uiTraceStart();
#endif
#endif
	PL_Init();
	APP_AdoptToHardware();
	vTaskStartScheduler();
}

