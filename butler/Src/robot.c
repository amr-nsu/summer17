#include "robot.h"
#include "servo.h"
#include "stm32f0xx_hal.h"
#include "adc.h"


void Robot_Init()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); // 1 - led off
    const int init_time = 500; // ms
    for(int servo=1; servo<=6; ++servo) {
        Servo_Rotate(servo, 0, init_time);
    }
    HAL_Delay(init_time);
}

int Robot_GetDistance()
{
  HAL_ADC_Start(&hadc);
  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
  return HAL_ADC_GetValue(&hadc);
}

void Robot_Greeting()
{
  const int greeting_time_begin = 1500;
  const int greeting_position = 30;
  Servo_Rotate(1, -greeting_position, greeting_time_begin);
  Servo_Rotate(2, greeting_position, greeting_time_begin);
  Servo_Rotate(4, greeting_position, greeting_time_begin);
  Servo_Rotate(5, -greeting_position, greeting_time_begin);
  HAL_Delay(greeting_time_begin);

  const int greeting_time_end = 1000;
  Servo_Rotate(1, 0, greeting_time_end);
  Servo_Rotate(2, 0, greeting_time_end);
  Servo_Rotate(4, 0, greeting_time_end);
  Servo_Rotate(5, 0, greeting_time_end);
  HAL_Delay(greeting_time_end);
}

