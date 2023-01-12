//include servo library
#include <Servo.h>

//define sensor pin
#define S0_PIN 5
#define S1_PIN 4
#define S2_PIN 7
#define S3_PIN 6
#define OUT_PIN 8

//define motor pin
#define MOTOR_1_PIN_1 2
#define MOTOR_2_PIN_1 3
#define MOTOR_3_PIN_1 9
#define MOTOR_4_PIN_1 10

//define limit switch
#define END_STOP1_PIN 12

//define buzzer pin
#define BUZZ_PIN 13

//define servo angle
Servo servom;
  int servogr = 20;
  int servobl = 150;
  int servomd = 65;

void setup()
{
  // Set the S0, S1, S2, S3 Pins as Output
  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.println("AgroTech: Integrating Technology In Agriculture");
  Serial.println("Machine In Action!");
  //Set OUT_PIN as Input
  pinMode(OUT_PIN, INPUT);
  
  // Set Pulse Width scaling to 20%

  digitalWrite(11, HIGH);
  digitalWrite(9, HIGH);
  //set the motors pin as output
  pinMode(MOTOR_1_PIN_1, OUTPUT);
  pinMode(MOTOR_2_PIN_1, OUTPUT);
  pinMode(MOTOR_3_PIN_1, OUTPUT);
  pinMode(MOTOR_4_PIN_1, OUTPUT);

  //set the pin for buzz
  pinMode(BUZZ_PIN, OUTPUT); 

  //set servo attach
  
  
  // Enabl UART for Debugging
  Serial.begin(9600);
  
  
}
void loop()
{
  int r, g, b;
  r = process_red_value();
  delay(200);
  g = process_green_value();
  delay(200);
  b = process_blue_value();
  delay(200);
  
 
  
  if ((g < 390) && (g > 300)) ////Bad Apple
  {
    Serial.println("Bad Apple");
    Serial.println("Turn Right Motor ON!");
    
   digitalWrite(BUZZ_PIN, LOW);
 digitalWrite(9, LOW);
    
  }
  else if ((g < 500) && (g > 410))
  {
    Serial.println("Good Apple");
    Serial.println("Turn Left Motor ON!");
    digitalWrite(BUZZ_PIN, LOW);
   digitalWrite(9, LOW); 
  }
  
  else
  {
   
    digitalWrite(BUZZ_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZ_PIN, LOW);
  delay(100); 
  }
  
  
  
  
   
      
}

int process_red_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, LOW);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_green_value()
{
  digitalWrite(S2_PIN, HIGH);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}
int process_blue_value()
{
  digitalWrite(S2_PIN, LOW);
  digitalWrite(S3_PIN, HIGH);
  int pulse_length = pulseIn(OUT_PIN, LOW);
  return pulse_length;
}


