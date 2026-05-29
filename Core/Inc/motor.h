#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"

/* FGO pulses per revolution (3 pulses/electrical-rev × N pole-pairs) */
#define MOTOR_FGO_PPR   12      /* 电机旋转1圈机械角度对应的中断数量 2对极 * 3FGO * 2上下沿 */


#define MOTOR_FGO_TIME  1200    /* 转换成1分钟 60s * 1000ms / 50ms计算周期 */

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
void Motor_SetPulseCount(uint32_t count);
uint32_t Motor_GetRPM(void);
void Motor_PulseCallback(void);

#endif /* __MOTOR_H__ */
