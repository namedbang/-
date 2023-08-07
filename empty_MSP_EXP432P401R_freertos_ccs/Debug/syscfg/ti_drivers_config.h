/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSP_EXP432P401R
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_MSP_EXP432P401R

#ifndef DeviceFamily_MSP432P401x
#define DeviceFamily_MSP432P401x
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== ADC ========
 */

/* P5.2 */
#define CONFIG_ADC_0                0


/*
 *  ======== Capture ========
 */

/* P3.5 */
#define CONFIG_CAPTURE_1            0
/* P5.7 */
#define CONFIG_CAPTURE_2            1


/*
 *  ======== GPIO ========
 */

/* P1.0, LaunchPad LED 1 Red */
#define CONFIG_GPIO_LED_0           0
/* P4.0 */
#define AIN1                        1
/* P4.1 */
#define AIN2                        2
/* P4.2 */
#define BIN1                        3
/* P4.3 */
#define BIN2                        4
/* P4.4 */
#define STBY                        5
/* P1.6 */
#define mpu6050_sda                 6
/* P1.7 */
#define mpu6050_scl                 7
/* P2.1, LaunchPad LED 2 Green */
#define CONFIG_GPIO_7               8
/* P2.2, LaunchPad LED 2 Blue */
#define CONFIG_GPIO_8               9
/* P2.0, LaunchPad LED 2 Red */
#define CONFIG_GPIO_0               10
/* P5.0 */
#define CCD_clk                     11
/* P3.6 */
#define CCD_SI                      12
/* P1.4, LaunchPad Button S2 (Right) */
#define CONFIG_GPIO_4               13
/* P1.1, LaunchPad Button S1 (Left) */
#define CONFIG_GPIO_5               14

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== PWM ========
 */

/* P2.6 */
#define CONFIG_PWM_B                0
/* P2.3 */
#define CONFIG_PWM_A                1


/*
 *  ======== Timer ========
 */

#define CONFIG_TIMER_1              0

/*
 *  ======== UART ========
 */

/*
 *  TX: P2.4
 *  RX: P2.5
 */
#define CONFIG_UART_0               0
/*
 *  TX: P1.3
 *  RX: P1.2
 *  XDS110 UART
 */
#define CONFIG_UART_1               1


/*
 *  ======== Button ========
 */

/* P1.4, LaunchPad Button S2 (Right) */
#define CONFIG_BUTTON_0             0
/* P1.1, LaunchPad Button S1 (Left) */
#define CONFIG_BUTTON_1             1


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
