#include <Servo.h>

#define MOTOR_1_PIN_1 2
#define MOTOR_1_PIN_2 3
#define MOTOR_2_PIN_1 9
#define MOTOR_2_PIN_2 10

// Define color sensor pins

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

#define SERVO_PIN 11

#define END_STOP1_PIN 12

Servo sort_servo;

// Calibration Values
// Get these from Calibration Sketch

int redMin = 14; // Red minimum value
int redMax = 250; // Red maximum value
int greenMin = 15; // Green minimum value
int greenMax = 256; // Green maximum value
int blueMin = 13; // Blue minimum value
int blueMax = 200; // Blue maximum value

// Variables for Color Pulse Width Measurements

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values

int redValue;
int greenValue;
int blueValue;

void setup() {

  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(END_STOP1_PIN, INPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Setup Serial Monitor
  Serial.begin(9600);
  sort_servo.attach(SERVO_PIN);
}

// Function to read Red Pulse Widths
int getRedPW() {

  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return map(PW, redMin,redMax,255,0);

}

// Function to read Green Pulse Widths
int getGreenPW() {

  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return map(PW, greenMin,greenMax,255,0);

}

// Function to read Blue Pulse Widths
int getBluePW() {

  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return map(PW, blueMin,blueMax,255,0);
}

void start_motor1_dir1() {
  digitalWrite(MOTOR_1_PIN_1, HIGH);
  digitalWrite(MOTOR_1_PIN_2, LOW);
}

void start_motor1_dir2() {
  digitalWrite(MOTOR_1_PIN_1, LOW);
  digitalWrite(MOTOR_1_PIN_2, HIGH);
}

void stop_motor1() {
  digitalWrite(MOTOR_1_PIN_1, LOW);
  digitalWrite(MOTOR_1_PIN_2, LOW);
}

void start_motor2_dir1() {
  digitalWrite(MOTOR_2_PIN_1, HIGH);
  digitalWrite(MOTOR_2_PIN_2, LOW);
}

void start_motor2_dir2() {
  digitalWrite(MOTOR_2_PIN_1, LOW);
  digitalWrite(MOTOR_2_PIN_2, HIGH);
}

void stop_motor2() {
  digitalWrite(MOTOR_2_PIN_1, LOW);
  digitalWrite(MOTOR_2_PIN_2, LOW);
}

void loop() {

  redPW = getRedPW();
  delay(200);
  greenPW = getGreenPW();
  delay(200);
  bluePW = getBluePW();
  delay(200);

  // Print output to Serial M`onitor
  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.print(" - Green = ");
  Serial.print(greenValue);
  Serial.print(" - Blue = ");
  Serial.println(blueValue);

  if (redPW > 200)
  {
    sort_servo.write(179);
  } else if (greenPW > 200) {
    sort_servo.write(0);
  }

  if (digitalRead(END_STOP1_PIN) == HIGH) {
    stop_motor1();
  }
}
