 /* 
Modified on Dec 1, 2020
Modified by MehranMaleki from Arduino Examples
Home
*/


//Mux control pins
int s0 = 4;
int s1 = 3;
int s2 = 2;


//Mux in "Z" pin
int Z_pin = A0;
int calibrate[] = {0,0,0,0,0,0,0,0};



void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);

  Serial.begin(9600);

  //Loop through and read all 8 values
//  for(int i = 0; i < 5; i ++){
//    for(int i = 0; i < 8; i ++){
//      Serial.print("Value at channel ");
//      Serial.print(i);
//      Serial.print("is : ");
//      calibrate[i] += readMux(i);
//      Serial.println(readMux(i));
//    }
//    delay(1000);
//  }
//  for(int i = 0; i < 8; i ++){
//    calibrate[i] = calibrate[i]/5;
//  }
}


void loop(){
  for(int i = 2; i < 8; i ++){
    Serial.print("Channel_");
    Serial.print(i);
    Serial.print("_");
    int original = readMux(i);
    Serial.print(original);
    Serial.print("/");
  }
  Serial.println("//");
  delay(500);
}




float readMux(int channel){
  int controlPin[] = {s0, s1, s2};

  int muxChannel[8][3]={
    
    {1,1,0}, //channel 3
    {0,0,0}, //channel 0
    {1,0,0}, //channel 1
    {0,1,0}, //channel 2
    {0,0,1}, //channel 4
    {0,1,1}, //channel 6
    {1,1,1}, //channel 7
    {1,0,1}, //channel 5
  };

  //loop through the 3 sig
  for(int i = 0; i < 3; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
      //Serial.print(muxChannel[channel][i]);
  }
  //Serial.println();
  //read the value at the Z pin
  int val = analogRead(Z_pin);
  return val;
}
