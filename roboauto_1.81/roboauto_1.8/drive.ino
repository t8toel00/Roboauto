void drive(char directionCommand, char speedCommand)
{
  float differential = 0.15;

  if (directionCommand != NULL) {
    g_currentDirection = directionCommand;
  }
  if (speedCommand != NULL) {
    g_drivingSpeed = map((int)speedCommand, 48, 57, 0, 215);
  }
  switch (g_currentDirection) {
    case FORWARD:
      digitalWrite(IN_1_MOTOR_R, LOW);
      digitalWrite(IN_2_MOTOR_R, HIGH);
      digitalWrite(IN_3_MOTOR_L, LOW);
      digitalWrite(IN_4_MOTOR_L, HIGH);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed);
      break;

    case STOP:
      digitalWrite(IN_1_MOTOR_R, LOW);
      digitalWrite(IN_2_MOTOR_R, LOW);
      digitalWrite(IN_3_MOTOR_L, LOW);
      digitalWrite(IN_4_MOTOR_L, LOW);
      analogWrite(ENABLE_PWM_R, 0);
      analogWrite(ENABLE_PWM_L, 0);
      break;

    case BACKWARD:
      digitalWrite(IN_1_MOTOR_R, HIGH);
      digitalWrite(IN_2_MOTOR_R, LOW);
      digitalWrite(IN_3_MOTOR_L, HIGH);
      digitalWrite(IN_4_MOTOR_L, LOW);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed);
      break;

    case RIGHT:
      digitalWrite(IN_1_MOTOR_R, HIGH);
      digitalWrite(IN_2_MOTOR_R, LOW);
      digitalWrite(IN_3_MOTOR_L, LOW);
      digitalWrite(IN_4_MOTOR_L, HIGH);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed);
      break;

    case LEFT:
      digitalWrite(IN_1_MOTOR_R, LOW);
      digitalWrite(IN_2_MOTOR_R, HIGH);
      digitalWrite(IN_3_MOTOR_L, HIGH);
      digitalWrite(IN_4_MOTOR_L, LOW);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed);
      break;

    case F_RIGHT:
      digitalWrite(IN_1_MOTOR_R, LOW);
      digitalWrite(IN_2_MOTOR_R, HIGH);
      digitalWrite(IN_3_MOTOR_L, LOW);
      digitalWrite(IN_4_MOTOR_L, HIGH);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed * differential);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed);
      break;

    case F_LEFT:
      digitalWrite(IN_1_MOTOR_R, LOW);
      digitalWrite(IN_2_MOTOR_R, HIGH);
      digitalWrite(IN_3_MOTOR_L, LOW);
      digitalWrite(IN_4_MOTOR_L, HIGH);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed * differential);
      break;

    case B_RIGHT:
      digitalWrite(IN_1_MOTOR_R, HIGH);
      digitalWrite(IN_2_MOTOR_R, LOW);
      digitalWrite(IN_3_MOTOR_L, HIGH);
      digitalWrite(IN_4_MOTOR_L, LOW);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed * differential);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed);
      break;

    case B_LEFT:
      digitalWrite(IN_1_MOTOR_R, HIGH);
      digitalWrite(IN_2_MOTOR_R, LOW);
      digitalWrite(IN_3_MOTOR_L, HIGH);
      digitalWrite(IN_4_MOTOR_L, LOW);
      analogWrite(ENABLE_PWM_R, g_drivingSpeed);
      analogWrite(ENABLE_PWM_L, g_drivingSpeed * differential);
      break;
  }
}
