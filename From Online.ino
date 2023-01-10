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
  
  //Set OUT_PIN as Input
  pinMode(OUT_PIN, INPUT);
  
  // Set Pulse Width scaling to 20%
  digitalWrite(S0_PIN, HIGH);
  digitalWrite(S1_PIN, LOW);
  
  //set the motors pin as output
  pinMode(MOTOR_1_PIN_1, OUTPUT);
  pinMode(MOTOR_2_PIN_1, OUTPUT);
  pinMode(MOTOR_3_PIN_1, OUTPUT);
  pinMode(MOTOR_4_PIN_1, OUTPUT);

  //set the pin for buzz
  pinMode(BUZZ_PIN, OUTPUT); 

  //set servo attach
  servom.attach(11);
  
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
  
  servom.write(servomd);
  
  if ((b < 1840) && (b > 1775))
  {
    Serial.println("Colour Blue");
    stop_motor1();
    start_motor2();
    servom.write(servobl);
    
  }
  else if ((b < 1900) && (b > 1855))
  {
    Serial.println("Colour Green");
    start_motor1();
    stop_motor2();
    servom.write(servogr);
    
  }
  else if ((b < 2000) && (b > 1945))
  {
    Serial.println("Colour Red");
    start_motor1();
    stop_motor2();
    servom.write(servogr);    
    


  }
  
  if (digitalRead(END_STOP1_PIN) == HIGH) 
  {
    stop_motor4();
    stop_motor3();
       
  }
   if (digitalRead(END_STOP1_PIN) == LOW)
   start_motor3();
  
  digitalWrite(BUZZ_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZ_PIN, LOW);
  delay(100);  
      
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
//start motor 1(green)
void start_motor1() {
  digitalWrite(MOTOR_1_PIN_1, HIGH);

}
//stop motor 1(green)
void stop_motor1() {
  digitalWrite(MOTOR_1_PIN_1, LOW);

}
//start motor 2(blue)
void start_motor2() {
  digitalWrite(MOTOR_2_PIN_1, HIGH);
  
}
//stop motor 2(blue)
void stop_motor2() {
  digitalWrite(MOTOR_2_PIN_1, LOW);
}
//start motor 3 (main conveyor belt)
void start_motor3() {
  digitalWrite(MOTOR_3_PIN_1, HIGH);

}
//stop motor 3 (main conveyor belt)
void stop_motor3() {
  digitalWrite(MOTOR_3_PIN_1, LOW);
}

void start_motor4() {
  digitalWrite(MOTOR_4_PIN_1, HIGH);

}

void stop_motor4() {
  digitalWrite(MOTOR_4_PIN_1, LOW);

}

