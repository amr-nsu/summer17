#ifndef SERVO_H_
#define SERVO_H_

void Servo_Send(char *command);
void Servo_SendCommand(int servo, int position, int t);
void Servo_Rotate(int servo, int angle, int t);

#endif /* SERVO_H_ */
