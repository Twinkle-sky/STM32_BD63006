#include "motor.h"
#include "tim.h"

static volatile uint32_t fgo_pulse_count = 0;
static uint32_t fgo_last_count = 0;
static uint32_t fgo_last_tick = 0;
static uint32_t motor_rpm = 0;
static uint16_t motor_period = 0;

void Motor_Init(void)
{
    motor_period = htim2.Init.Period;

    /* Safe default: stop and brake */
    Motor_SetSpeed(0);
    Motor_SetDirection(MOTOR_DIR_CW);
    Motor_SetBrake(MOTOR_BRAKE_ON);
}

void Motor_Start(void)
{
    Motor_SetBrake(MOTOR_BRAKE_OFF);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void Motor_Stop(void)
{
    Motor_SetSpeed(0);
    HAL_Delay(10);
    Motor_SetBrake(MOTOR_BRAKE_ON);
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}

void Motor_SetSpeed(uint16_t duty)
{
    if (duty > motor_period) {
        duty = motor_period;
    }
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
}

void Motor_SetDirection(Motor_Direction dir)
{
    HAL_GPIO_WritePin(MOTOR_CW_CCW_Port, MOTOR_CW_CCW_Pin, (GPIO_PinState)dir);
}

void Motor_SetBrake(Motor_Brake state)
{
    HAL_GPIO_WritePin(MOTOR_BRKB_Port, MOTOR_BRKB_Pin, (GPIO_PinState)state);
}

uint32_t Motor_GetPulseCount(void)
{
    return fgo_pulse_count;
}

uint32_t Motor_GetRPM(void)
{
    uint32_t tick = HAL_GetTick();
    uint32_t elapsed = tick - fgo_last_tick;

    if (elapsed >= 1000) {
        uint32_t pulses = fgo_pulse_count - fgo_last_count;
        motor_rpm = (pulses * 60000UL) / (elapsed * MOTOR_FGO_PPR);
        fgo_last_count = fgo_pulse_count;
        fgo_last_tick = tick;
    }

    return motor_rpm;
}

/* Override HAL weak callback — invoked by EXTI4_IRQHandler via HAL_GPIO_EXTI_IRQHandler */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == MOTOR_FGO_Pin) {
        fgo_pulse_count++;
    }
}
