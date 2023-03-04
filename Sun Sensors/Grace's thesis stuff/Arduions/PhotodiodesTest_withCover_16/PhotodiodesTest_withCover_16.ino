 /* 
Modified on Dec 1, 2020
Modified by MehranMaleki from Arduino Examples
Home
*/


//Mux control pins
int s0_1 = 3;
int s1_1 = 4;
int s2_1 = 5;

int s0_2 = 0;
int s1_2 = 1;
int s2_2 = 2;

//Mux in "Z" pin
int Z_pin_1 = A2;
int Z_pin_2 = A1;
double  values[2][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
};
int counter = 0;
double height = 10.61; //This is full height, 2.3 subtracted later, tested with 17.7

void setup(){
  pinMode(s0_1, OUTPUT); 
  pinMode(s1_1, OUTPUT); 
  pinMode(s2_1, OUTPUT); 
  pinMode(s0_2, OUTPUT); 
  pinMode(s1_2, OUTPUT); 
  pinMode(s2_2, OUTPUT); 

  digitalWrite(s0_1, LOW);
  digitalWrite(s1_1, LOW);
  digitalWrite(s2_1, LOW);
  digitalWrite(s0_2, LOW);
  digitalWrite(s1_2, LOW);
  digitalWrite(s2_2, LOW);


  Serial.begin(9600);
}


void loop(){
  for(int i = 0; i < 10; i ++){
  for(int i = 0; i < 8; i ++){
    values[0][i] = 1023-readMux_1(i);
    values[1][i] = (8-i)*-1;
  }
  for(int i = 0; i < 8; i ++){
    values[0][i+8] = 1023-readMux_2(i);
    values[1][i+8] = i+1;
  }
  
  Serial.println("Full array:");
  printArray();
  Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");

//  
//  Serial.print("Angle: ");
//  Serial.println(angleMeasure());
  delay(100);
  }
//  Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");

}

double  angleMeasure(){
  double  total_current_distance = 0;
  double  total_current = 0;
  for(int i = 0; i < 16; i ++){
    double  distance = (values[1][i]*2.54);
    if (distance < 0){
      distance += (2.54/2);
    }
    else{
      distance -= (2.54/2);
    }
    total_current_distance += values[0][i]*(distance); //distance is 2.54mm
    total_current += values[0][i];
  }
  double  normalized_current_distance = total_current_distance/total_current;
  return( atan(normalized_current_distance/(height-3.2))* 4068 / 71*-1);
}

void printArray(){
  for(int i = 0; i < 16; i ++){
    Serial.print(values[0][i]);
    Serial.print(" //index:// ");
    Serial.println(values[1][i]);
  }
}
void bubblesort(){
  for (uint8_t c = 0; c < 15; c++) { // do a bubble sort
    for (uint8_t d = 0; d < 15 - c; d++) {
      if (values[0][d] > values[0][d + 1]) { // compare
        for (uint8_t e = 0; e <= 1; e++) { // swap both values & index
          int tempval = values[e][d];
          values[e][d] = values[e][d + 1];
          values[e][d + 1] = tempval;
        }
      }
    }
  } 
}

float readMux_1(int channel){
  int controlPin[] = {s0_1, s1_1, s2_1};

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
  int val = analogRead(Z_pin_1);
  return val;
}



float readMux_2(int channel){
  int controlPin[] = {s0_2, s1_2, s2_2};

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
  int val = analogRead(Z_pin_2);
  return val;
}
