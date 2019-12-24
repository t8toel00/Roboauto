int ultrasensor(char sensor)
/*
   Returns distance from ultrasonic sensor in CM
*/
{
  long duration;
  int distance;

  switch (sensor) {
    case FORWARD:
      digitalWrite(TRIG_PIN_F, LOW);
      delay(1);
      digitalWrite(TRIG_PIN_F, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN_F, LOW);
      duration = pulseIn(ECHO_PIN_F, HIGH);
      distance = (duration / 2) * 0.0346;         //Äänen nopeus huoneenlämmössä on 346 m/s (Google)
      return distance;
  
    case RIGHT:
      digitalWrite(TRIG_PIN_R, LOW);
      delay(1);
      digitalWrite(TRIG_PIN_R, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN_R, LOW);
      duration = pulseIn(ECHO_PIN_R, HIGH);
      distance = (duration / 2) * 0.0346;         //Äänen nopeus huoneenlämmössä on 346 m/s (Google)
      return distance;
  
    case LEFT:
      digitalWrite(TRIG_PIN_L, LOW);
      delay(1);
      digitalWrite(TRIG_PIN_L, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN_L, LOW);
      duration = pulseIn(ECHO_PIN_L, HIGH);
      distance = (duration / 2) * 0.0346;         //Äänen nopeus huoneenlämmössä on 346 m/s (Google)
      return distance;
    }
}
