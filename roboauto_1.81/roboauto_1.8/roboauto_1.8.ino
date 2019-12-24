/*
 
 * Roboauto
 * By: Nasir Kainulainen, Jaakko Piirainen and Elias Toivola
 
 */

 
#include <SoftwareSerial.h>

/*CONTROL SETUP*/
#define FORWARD 'F'
#define STOP 'S'
#define BACKWARD 'B'
#define RIGHT 'R'
#define LEFT 'L'
#define F_RIGHT 'I'
#define F_LEFT 'G'
#define B_RIGHT 'J'
#define B_LEFT 'H'
#define BOT_MODE_ACTIVATE 'X'
#define BOT_MODE_DEACTIVATE 'x'
#define LINE_FOLLOW_ACTIVATE 'W'
#define LINE_FOLLOW_DEACTIVATE 'w'

/*SERIAL SETUP*/
#define RX 2
#define TX 3
#define BAUD 9600
SoftwareSerial bt_module(RX, TX);

/* IR SENSOR CONNECTION SETUP */
#define LEFT_IR A3
#define RIGHT_IR A4

/* MOTOR H-BRIDGE CONTROLLER CONNECTION SETUP */
#define ENABLE_PWM_R 5
#define ENABLE_PWM_L 6
#define IN_1_MOTOR_R 7
#define IN_2_MOTOR_R 8
#define IN_3_MOTOR_L 12
#define IN_4_MOTOR_L 13

/* ULTRASENSOR CONNECTION SETUP */
#define TRIG_PIN_R 9     //Detection pins: Right, Left, Foward
#define ECHO_PIN_R 10
#define TRIG_PIN_L 11
#define ECHO_PIN_L 4
#define TRIG_PIN_F A1
#define ECHO_PIN_F A2


/* GLOBAL VARIABLES */
int g_drivingSpeed = 0;
char g_currentDirection = NULL;
int g_botMode = 0;
int g_lineFollowMode = 0;


void setup()
{
  /* MOTOR PINS */
  pinMode(ENABLE_PWM_R, OUTPUT);  //Enable A / PWM
  pinMode(ENABLE_PWM_L, OUTPUT);  //Enable B / PWM
  pinMode(IN_1_MOTOR_R, OUTPUT);  //In1 MOTOR A
  pinMode(IN_2_MOTOR_R, OUTPUT);  //In2 MOTOR A
  pinMode(IN_3_MOTOR_L, OUTPUT);  //In3 MOTOR B
  pinMode(IN_4_MOTOR_L, OUTPUT);  //In4 MOTOR B

  /* ULTRASENSOR PINS */
  pinMode(TRIG_PIN_R, OUTPUT); //pin 9
  pinMode(ECHO_PIN_R, INPUT);  //pin 10
  pinMode(TRIG_PIN_L, OUTPUT); //pin 11
  pinMode(ECHO_PIN_L, INPUT);  //pin 4
  pinMode(TRIG_PIN_F, OUTPUT); //pin A1
  pinMode(ECHO_PIN_F, INPUT);  //pin A2

  /* SERIAL PINS */
  Serial.begin(BAUD);
  bt_module.begin(BAUD);
}

void loop()
{
  controller(NULL);
}
