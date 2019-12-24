void line_follower()
{
  while (g_lineFollowMode == 1)
  {
    
   if ((analogRead(LEFT_IR)* (5.0 / 1023.0)) < 2 && (analogRead(RIGHT_IR)* (5.0 / 1023.0)) < 2) {
    drive(FORWARD, '5'); 
   }
   
   if ((analogRead(LEFT_IR)* (5.0 / 1023.0)) >= 3 && (analogRead(RIGHT_IR)* (5.0 / 1023.0)) <= 2) {
     drive(LEFT, '9');
   }
   
   if ((analogRead(RIGHT_IR)* (5.0 / 1023.0)) >= 3 && (analogRead(LEFT_IR)* (5.0 / 1023.0)) <= 2) {
     drive(RIGHT, '9');
   }
   
    controller(NULL);
    if (g_lineFollowMode == 0) {
      drive(STOP, 0);
      return;
    }
  }
}
