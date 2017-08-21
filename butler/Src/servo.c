#include "servo.h"
#include "usart.h"
#include "string.h"


void Servo_Send(char *command)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)command, strlen(command), 100);
}


void Servo_SendCommand(int servo, int position, int t)
{
    static const int command_len = 32;
    char command[command_len];
    snprintf(command, command_len, "#%dP%dT%d\r\n", servo, position, t);
    Servo_Send(command);
}

void Servo_Rotate(int servo, int angle, int t)
{
    static const int init_interval = 1500;
    static const double angle_to_interval = 1000.0 / 90.0;
    int position = init_interval + angle_to_interval * angle;
    Servo_SendCommand(servo, position, t);
}
