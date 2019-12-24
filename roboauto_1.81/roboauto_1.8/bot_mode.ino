// Mikäli loiva käännös (esim F_RIGHT) kääntyy lähes/liian paikallaan, niin mene "drive" välilehteen ja
// muuta float "differential = 0.15;" arvoa suurempaan. 0.20 korjaa jo paljon, testattu lähes täysissä x6 1.5v = 9v AA-pattereissa.

// tapauksien laukaisutilanteet ovat visualisoitu loppuesityksessä

// (ultrasensor(FORWARD/RIGHT/LEFT) - muuttuja pyytää sensorilta uutta arvoa. distance_F/R/L pyytää vanhaa aikaisemmin haettua arvoa.

void bot_mode()
{

  while (g_botMode == 1)
  {

    extern volatile unsigned long timer0_millis;  //Arduino's native millis() variable. gets zeroed often for timing so timestamps with millis() are not available.

    g_drivingSpeed = 200; //default driving speed if a case doesn't specify one.
    int previousTurn;    //1 = right, 2 = left, 0 = null
    int distance_F = ultrasensor(FORWARD);
    int distance_R = ultrasensor(RIGHT);
    int distance_L = ultrasensor(LEFT);

    // CASE 1: SERPENTINE HALL CRUISE
    // car is positioned in middle and "weaves" foward, widening its detection angle in front.

    if ((distance_F >= 200) && ((distance_R < 360) && (distance_R >= 60))  &&  ((distance_L < 360) && (distance_L >= 60)))
    {
      g_drivingSpeed = 175; //max speed
      if (distance_R >= distance_L)
      {
        drive(F_RIGHT, NULL);
        previousTurn = 1;
      }
      if (distance_R < distance_L)
      {
        drive(F_LEFT, NULL);
        previousTurn = 2;
      }
    }

    // CASE 2: OBSTACLE/WALL COMING IN FRONT
    // car searches for a new clear path

    else if (((distance_F < 200) && (distance_F >= 100))  &&  ((distance_R < 360) && (distance_R >= 60))  &&  ((distance_L < 360) && (distance_L >= 60)))
    {
      g_drivingSpeed = 175;
      if (distance_R >= distance_L)
      {
        noInterrupts ();
        timer0_millis = 0;
        interrupts ();
        while (ultrasensor(FORWARD) < 220)
        {
          if (ultrasensor(FORWARD) < 150) //change search direction
          {
            while ((ultrasensor(FORWARD) < 220))
            {
              drive(LEFT, NULL);
              previousTurn = 2;
            }
          }
          drive(RIGHT, NULL);
          previousTurn = 1;
        }
        while (ultrasensor(FORWARD) > 220 && millis() < 5000) //car moves towards the free space for 5s or until it detects something
        {
          if ((ultrasensor(LEFT) < 30) || (ultrasensor(RIGHT) < 30))
          {
            break;
          }
          drive(FORWARD, NULL);
        }

      }
      if (distance_R < distance_L)
      {
        noInterrupts ();
        timer0_millis = 0;
        interrupts ();
        while (ultrasensor(FORWARD) < 220)
        {
          if (ultrasensor(FORWARD) < 150)
          {
            while ((ultrasensor(FORWARD) < 220))
            {
              drive(RIGHT, NULL);
              previousTurn = 1;
            }
          }
          drive(LEFT, NULL);
          previousTurn = 2;
        }
        while (ultrasensor(FORWARD) > 220 && millis() < 5000)
        {
          if ((ultrasensor(LEFT) < 30) || (ultrasensor(RIGHT) < 30))
          {
            break;
          }
          drive(FORWARD, NULL);
        }
      }
    }

    // CASE 3: L OR R > 360 = STEEP BALANCE BACK
    // if one of the side sensors have lost its echo -> slither towards the lost side (with case 4 most likely)

    else if
    (
      (distance_F > 100)
      &&
      ((distance_R > 360) && (distance_L >= 60) && (distance_L <= 360))  ||  ((distance_L > 360) && (distance_R >= 60) && (distance_R <= 360))
    )
    {
      g_drivingSpeed = 145; //low speed. Need extra time for bigger ultrasensor delays when one is over max distance.
      if (distance_R > distance_L)
      {
        drive(F_RIGHT, NULL);
        previousTurn = 1;
      }
      if (distance_R < distance_L)
      {
        drive(F_LEFT, NULL);
        previousTurn = 2;
      }
    }

    // CASE 4: R AND L SIDE REALIGNMENT
    // both side sensors have lost their echoes -> search the likely nearest wall

    else if ((distance_F > 100) && (distance_R >= 360) && (distance_L >= 360))
    {
      g_drivingSpeed = 145; //low speed2
      if (previousTurn = 2) //left
      {
        if (distance_F > 220 && distance_F < 360) //med distance
        {
          while ((ultrasensor(RIGHT)) > 345)
          {
            drive(RIGHT, NULL);
          }
        }
        if (distance_F >= 360) //max distance
        {
          while ((ultrasensor(RIGHT)) > 210)
          {
            drive(RIGHT, NULL);
          }
        }
        if (distance_F <= 220) //min distance
        {
          while ((ultrasensor(LEFT)) > 350)
          {
            drive(RIGHT, NULL);
          }
        }
      }
      if (previousTurn = 1) //right
      {
        if (distance_F > 220 && distance_F < 360)
        {
          while ((ultrasensor(LEFT)) > 345)
          {
            drive(LEFT, NULL);
          }
        }
        if (distance_F >= 360)
        {
          while ((ultrasensor(LEFT)) > 210)
          {
            drive(LEFT, NULL);
          }
        }
        if (distance_F <= 220)
        {
          while ((ultrasensor(RIGHT)) > 350)
          {
            drive(LEFT, NULL);
          }
        }
      }
    }

    // CASE 5: OBSTACLE IN FRONT
    // back track at least for 1s -> make a nudge to more spacious side

    else if
    (
      (distance_F < 100)
      &&
      (((360 > distance_R) && (distance_R > 60))  &&  ((360 > distance_L) && (distance_L > 60)))
      ||
      (((360 > distance_R) && (distance_R > 60))  ||  ((360 > distance_L) && (distance_L > 60)))
    )
    {
      g_drivingSpeed = 145; //low speed
      noInterrupts ();
      timer0_millis = 0;
      interrupts ();
      while ((ultrasensor(FORWARD) < 135) && (millis() < 4000))
      {
        drive(BACKWARD, NULL);
      }
      if (ultrasensor(RIGHT) > ultrasensor(LEFT))
      {
        noInterrupts ();
        timer0_millis = 0;
        interrupts ();
        while ((ultrasensor(FORWARD) < 150) || (millis() < 400)) //tarkista paljonko 400 ms kääntää
        {
          drive(RIGHT, NULL);
          previousTurn = 1;
        }
        while (millis() < 4000)
        {
          if ((ultrasensor(FORWARD) < 45) || (ultrasensor(LEFT) < 30) || (ultrasensor(RIGHT) < 30))
          {
            break;
          }
          drive(FORWARD, NULL);
        }
      }
      if (ultrasensor(RIGHT) < ultrasensor(LEFT))
      {
        noInterrupts ();
        timer0_millis = 0;
        interrupts ();
        while ((ultrasensor(FORWARD) < 150) || (millis() < 400))
        {
          drive(LEFT, NULL);
          previousTurn = 2;
        }
        while (millis() < 3500)
        {
          if ((ultrasensor(FORWARD) < 45) || (ultrasensor(LEFT) < 30) || (ultrasensor(RIGHT) < 30))
          {
            break;
          }
          drive(FORWARD, NULL);
        }
      }
    }

    // CASE 6: THERE'S AN OBSTACLE/WALL ON CAR'S RIGHT SIDE
    // spin away from the side obstacle

    else if ((distance_F >= 100) && (distance_R < 60) && (distance_L >= 60))
    {
      g_drivingSpeed = 185;
      noInterrupts ();
      timer0_millis = 0;
      interrupts ();
      while (ultrasensor(RIGHT) < 75 && millis() < 200) //a minimum timer to reduce the chance of spinning too much to change hallway direction,
        //because it might take a side sensor too long time to notice it's no longer < 75
      {
        drive(LEFT, NULL);
        previousTurn = 2;
      }
      while (ultrasensor(FORWARD) > 200 && (ultrasensor(LEFT) > 125))
      {
        drive(FORWARD, NULL);
      }
      if (distance_F < 200)
      {
        noInterrupts ();
        timer0_millis = 0;
        interrupts ();
        while (millis() < 200) //take a nudge forward in hopes to find more space (or to get case 9-11)
        { //in case there's another obstacle in maneuver path
          drive(FORWARD, NULL);
        }
      }
    }

    // CASE 7: THERE'S AN OBSTACLE/WALL ON CAR'S LEFT SIDE

    else if ((distance_F >= 100) && (distance_R >= 60) && (distance_L < 60))
    {
      g_drivingSpeed = 185;
      noInterrupts ();
      timer0_millis = 0;
      interrupts ();
      while (ultrasensor(LEFT) < 75 && millis() < 200)
      {
        drive(RIGHT, NULL);
        previousTurn = 1;
      }
      while (ultrasensor(FORWARD) > 200 && ultrasensor(RIGHT) > 125)
      {
        drive(FORWARD, NULL);
      }
      if (distance_F < 200)
      {
        noInterrupts ();
        timer0_millis = 0;
        interrupts ();
        while (millis() < 200) //take a nudge forward in hopes to find more space (or to get case 9-11)
        { //in case there's another obstacle in maneuver path
          drive(FORWARD, NULL);
        }
      }
    }

    // CASE 8: CAR STARES AT A HALL WALL
    // car has lost its side echoes & needs to reverse away. A bit rare case now that case 4 searches walls while being still
    //but this might still trigger when something breaks a maneuver loop in other case.

    else if ((distance_F < 100) && (distance_R >= 360) && (distance_L >= 360))
    {
      g_drivingSpeed = 185;
      noInterrupts ();
      timer0_millis = 0;
      interrupts ();
      while (ultrasensor(FORWARD) < 130 && millis() < 1000)
      {
        drive(BACKWARD, NULL);
      }
      if (previousTurn = 2) //left
      {
        while (ultrasensor(LEFT) >= 280)
        {
          drive(RIGHT, NULL);
          previousTurn = 1;
        }
      }
      if (previousTurn = 1) //right
      {
        while (ultrasensor(RIGHT) >= 280)
        {
          drive(LEFT, NULL);
          previousTurn = 2;
        }
      }
    }

    // CASE 9: CAR IS IN A NARROW "TUNNEL"/GAP
    // car slows down and tries to stay in middle

    else if ((distance_F > 100) && (distance_R < 60) && (distance_L < 60))
    {
      g_drivingSpeed = 165; //low speed2
      if (distance_R > distance_L)
      {
        drive(F_RIGHT, NULL);
        previousTurn = 1; //right
      }
      if (distance_R < distance_L)
      {
        drive(F_LEFT, NULL);
        previousTurn = 2; //left
      }
    }

    // CASE 10: CAR IS BLOCKED FROM ALL SIDES
    // car tries to reverse away, might take hits on its back if it's trapped
    // eventually car will start spinning to find a way out, if cases 9 & 10 stay true (no timer reset in this loop)

    //int escapeTries;

    else if ((distance_F <= 100) && (distance_R < 60) && (distance_L < 60))
    {
      g_drivingSpeed = 165; //low speed2
      if (distance_R > distance_L)
      {
        drive(B_RIGHT, NULL);
      }
      if (distance_R < distance_L)
      {
        drive(B_LEFT, NULL);
      }
      if (millis() > 20000)
      {
        noInterrupts ();
        timer0_millis = 0;
        interrupts ();
        while (millis() > 500)
        {
          drive(FORWARD, NULL);
        }
        while (ultrasensor(FORWARD) <= 200)
        {
          drive(LEFT, NULL);
        }
      }
    }

    // CASE 11: CAR IS BLOCKED FROM FRONT AND ONE OF EITHER SIDE
    // car spins until it finds the available way out

    else if ((distance_F <= 100) && ((distance_R < 60) || (distance_L < 60)))
    {
      if (distance_R > distance_L)
      {
        while (ultrasensor(FORWARD) < 120)
        {
          drive(RIGHT, NULL);
          previousTurn = 1;
        }
      }
      if (distance_R < distance_L)
      {
        while (ultrasensor(FORWARD) < 120)
        {
          drive(LEFT, NULL);
          previousTurn = 2;
        }
      }
      else
      {
        drive(BACKWARD, NULL);
      }
    }

    // CASE 0 UNKNOWN CONDITION
    // car does "hiccups" forward if it faces an encounter that CASES 1-11 don't know. Usually fixes errors with >=, <=, >, < and = mishaps.
    // "hiccups" are made to indicate that some value comparisons and mapping need to be corrected.

    else
    {
      drive(FORWARD, NULL);
      delay(100);
      drive(STOP, NULL);
      delay(500);
    }

    //check exit command
    controller(NULL);
    if (g_botMode == 0) {
      drive(STOP, NULL);
      return;
    }
  }
}
