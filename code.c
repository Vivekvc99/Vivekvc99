#include <Servo.h>

// Create three Servo objects
Servo leftServo;
Servo rightServo;
Servo extraServo;

// Define the pin number connected to the buzzer
const int buzzer = 12; 

// Define the pin number connected to the ultrasonic sensor
int pingPin=4;

// Define variables to hold the duration of the pulse and the distance
long int duration, distanceInches;
long distanceFront=0; // in cm

// The starting distance to begin avoiding obstacles
int startAvoidanceDistance=20; // in cm

// Function to convert microseconds to inches
long microsecondsToInches(long microseconds) 
{ 
  return microseconds/74/2; 
} 

// Function to convert microseconds to centimeters
long microsecondsToCentimeters(long microseconds) 
{ 
  return microseconds/29/2; 
} 

// Function to measure the distance using ultrasonic sensor
long distanceCm()
{ 
  // Send a short pulse to trigger the ultrasonic sensor
  pinMode(pingPin,OUTPUT);
  digitalWrite(pingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin,LOW);

  // Read the echo pulse from the ultrasonic sensor
  pinMode(pingPin,INPUT);
  duration=pulseIn(pingPin,HIGH);

  // Convert pulse duration to distance in inches
  distanceInches=microsecondsToInches(duration);
  
  // Return distance in cm
  return microsecondsToCentimeters(duration);
} 

// Function to stop the robot and blink an LED when an obstacle is detected
void center() 
{ 
  digitalWrite(6,HIGH); // LED on pin 6 blinks to indicate an obstacle
  leftServo.write(90);
  rightServo.write(90);
  delay(100);
  digitalWrite(6,LOW);
  delay(100);
} 

// Function to make the robot move forward
void moveForward() 
{
  // Control servo motors to move forward
  leftServo.write(0);
  rightServo.write(180);
  delay(200);
  // Additional code for moving forward should go here
} 

// Function to make the robot turn around
void turnAround() 
{
  digitalWrite(6,HIGH); 
  delay(150); 
  digitalWrite(6,LOW);

  leftServo.write(180);
  rightServo.write(180);
  delay(600);

  // Make a beep sound when turning around
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000); // ...for 1 sec
  noTone(buzzer); // Stop sound...
  delay(1000); // ...for 1sec

  // Additional code for turning and avoiding obstacles should go here
}

// Function to initialize the robot
void setup() 
{ 
  // Attach the servos to the appropriate pins
  leftServo.attach(2);
  rightServo.attach(3); 
  extraServo.attach(5); 

  // Set the pin modes
  pinMode(4,OUTPUT); 
  pinMode(6,OUTPUT); 
  pinMode(7,OUTPUT); 
  pinMode(8,OUTPUT); 
  pinMode(9,OUTPUT);

  pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output 
} 

// Main loop of the robot
void loop () 
{ 
  digitalWrite(9,HIGH); 
  digitalWrite(7,LOW); 
  tone(6,1000,1000); 
  delay(1000);

  // Get the distance to the nearest object
  distanceFront=distanceCm();

  // If the object is closer than the avoidance distance, turn around
  // Otherwise, move forward
  if(distanceFront>1){
    if(distanceFront<startAvoidanceDistance){
      center();
      turnAround();
      delay(100); 
    } 
    else{ 
      moveForward(); 
      delay(125); 
    }
  }
}
