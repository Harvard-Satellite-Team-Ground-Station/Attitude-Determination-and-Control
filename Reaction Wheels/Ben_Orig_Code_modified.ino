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

void setup() 
{
  pinMode(ENCODER, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER), hallInt, FALLING); //when encoder falls, run hall int which is an iterative func, counts pulses
  
  prevMicros = micros();
}

void loop() 
{

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
      Serial.print("Motor speed (RPM): "); Serial.println(rotSpeed);

      hall = 0;
    }
}

void hallInt() 
{
  hall++;
}