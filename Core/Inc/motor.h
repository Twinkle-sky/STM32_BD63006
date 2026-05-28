#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"

/* FGO pulses per revolution (1 or 3, depending on motor model) */
#define MOTOR_FGO_PPR  3

/* Pin definitions */
#define MOTOR_CW_CCW_Pin     GPIO_PIN_5
#define MOTOR_CW_CCW_Port    GPIOA
#define MOTOR_BRKB_Pin       GPIO_PIN_6
#define MOTOR_BRKB_Port      GPIOA
#define MOTOR_FGO_Pin        GPIO_PIN_4
#define MOTOR_FGO_Port       GPIOA

/* Direction: enum values map directly to GPIO_PinState */
typedef enum {
    MOTOR_DIR_CW  = 0,    /* PA5 LOW  → CW */
    MOTOR_DIR_CCW = 1     /* PA5 HIGH → CCW */
} Motor_Direction;

/* Brake: enum values map directly to GPIO_PinState */
typedef enum {
    MOTOR_BRAKE_ON  = 0,  /* PA6 LOW  → Brake engaged */
    MOTOR_BRAKE_OFF = 1   /* PA6 HIGH → Normal operation */
} Motor_Brake;

void Motor_Init(void);
void Motor_Start(void);
void Motor_Stop(void);
void Motor_SetSpeed(uint16_t duty);
void Motor_SetDirection(Motor_Direction dir);
void Motor_SetBrake(Motor_Brake state);
uint32_t Motor_GetPulseCount(void);
uint32_t Motor_GetRPM(void);

#endif /* __MOTOR_H__ */
