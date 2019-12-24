void controller(char command)
{
  if (command == NULL) {
    if (bt_module.available()) {
      command = bt_module.read();
    }
  }
  if (command == NULL) {
    return;
  }

  if (command == BOT_MODE_DEACTIVATE) {
    g_botMode = 0;
    return;
  }
  else if (command == LINE_FOLLOW_DEACTIVATE) {
    g_lineFollowMode = 0;
    return;
  }
  
  if (g_botMode == 1 || g_lineFollowMode == 1) {
    return;
  }
  
  switch (command) {
    case LINE_FOLLOW_ACTIVATE:
      g_lineFollowMode = 1;
      g_botMode = 0;
      line_follower();
      break;

    case BOT_MODE_ACTIVATE:
      g_botMode = 1;
      g_lineFollowMode = 0;
      bot_mode();
      break;

    case FORWARD:
      drive(FORWARD, NULL);
      break;

    case STOP:
      drive(STOP, NULL);
      break;

    case BACKWARD:
      drive(BACKWARD, NULL);
      break;

    case RIGHT:
      drive(RIGHT, NULL);
      break;

    case LEFT:
      drive(LEFT, NULL);
      break;

    case F_RIGHT:
      drive(F_RIGHT, NULL);
      break;

    case F_LEFT:
      drive(F_LEFT, NULL);
      break;

    case B_RIGHT:
      drive(B_RIGHT, NULL);
      break;

    case B_LEFT:
      drive(B_LEFT, NULL);
      break;
  }
  if ((int)command >= 48 && (int)command <= 57) {
    drive(NULL, command);
  }
}
