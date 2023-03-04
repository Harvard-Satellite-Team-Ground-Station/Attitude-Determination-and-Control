

#include <Servo.h>

byte servoPin = 8; // signal pin for the ESC.
Servo servo;

///////Encoder Stuff
//include directional code which monitors A and B signal
// Input pin for encoder, can be any interrupt capable pin
const uint8_t ENCODER = 5; // change to 0, 1, 2, or 3 on Feather 32u4
// Variable for tracking number of pulses from Hall effect sensor
volatile int hall = 0;

// Timing variables
unsigned long prevMicros = 0;
unsigned long curMicros = 0;
const unsigned long WINDOW = 100000;

// Motor/encoder parameters
const float PULSE_PER_REV = 1; //this is the I signal
const float GEARING = 1; //there is no gearbox

///////ISR Direction Stuff
//https://arduino.stackexchange.com/questions/32572/how-to-detect-the-direction-of-a-rotary-encoder
// Connect pin A (one of the outer ones) to a pin that can generate interrupts (eg. D2)
// Connect pin B (the other outer one) to another free pin (eg. D5)
volatile bool fired;
volatile bool up;

const byte encoderPinA = 2;
const byte encoderPinB = 3;

// Interrupt Service Routine for a change to encoder pin A
void isr ()
{
  if (digitalRead (encoderPinA))
    up = digitalRead (encoderPinB);
  else
    up = !digitalRead (encoderPinB);
  fired = true;
}  // end of isr

void setup() {
///Motor Stuff
Serial.begin(9600);
servo.attach(servoPin);
servo.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.
delay(7000); // delay to allow the ESC to recognize the stopped signal.

///Encoder Stuff
pinMode(ENCODER, INPUT);
attachInterrupt(digitalPinToInterrupt(ENCODER), hallInt, FALLING); //when encoder falls, run hall int which is an iterative func, counts pulses
prevMicros = micros();

//Direction Stuff

pinMode (encoderPinA, INPUT_PULLUP);     // enable pull-ups
pinMode (encoderPinB, INPUT_PULLUP); 
attachInterrupt(digitalPinToInterrupt(encoderPinA), isr, CHANGE);   // interrupt 0 is pin 2
Serial.begin(115200);
}


void loop() 
{
  //Motor Stuff
  servo.writeMicroseconds(1550); // Send signal to ESC.

  //Direction Stuff
  static long rotaryCount = 0;

  if (fired)
    {
    if (up)
      rotaryCount++;
    else
      rotaryCount--;
    fired = false;
    Serial.print ("Count = ");  
    Serial.println (rotaryCount);
    }  // end if fired

  //Encoder Stuff
  curMicros = micros();
  float rotSpeed;
  unsigned long delta_t = curMicros - prevMicros;
  if (delta_t >= WINDOW && hall > 0) 
    {
      prevMicros = curMicros; //rest timestamp
      float dt = float(delta_t)/1.0e6; // convert to seconds (and to a float)
      float rev = hall / (GEARING*PULSE_PER_REV); // convert raw pulse counts to revolutions (and convert to float)

      rotSpeed = rev/dt;

      rotSpeed *= 60; // convert to rpm

      // Report speed
      //Serial.print("Motor speed (RPM): "); 
      Serial.println(rotSpeed);

      hall = 0;
    }

}

void hallInt() 
{
  hall++;
}