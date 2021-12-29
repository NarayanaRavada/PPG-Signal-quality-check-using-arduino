/* Source code                                          */
/* author: LakshmiNarayana Ravada                       */
/* Connections..
   PPG sesnor :
   S to A0, +ve to 5v in arduino, -ve to Gnd in arduino.
   HC-05 Module:
   RX to 9, TX to 8, +5V to +5V, Gnd to Gnd in ardiuno. */
/* Use ardiuno due if n > 400 to avoid stroge issues    */


#include <SoftwareSerial.h>
SoftwareSerial btserial(8, 9);


void setup() {
  Serial.begin(9600);
  btserial.begin(9600);
}

void loop() {
  /* Variable */
  int i = 0;
  int n = 400;             // total samples
  int k = 4;               // total samples to be meaned over
  float data[n];           // raw_data taken as input from `analog 0` (A0)
  float mean = 0.0;        // mean of data
  int zcr = 0;             // total zero crossing rate
  
  // Takes input values
  while (i < n){
      float Val = analogRead(A0);
      data[i] = Val;
      delay(8);
      i = i + 1;
  }

  // Taking mean of data over next k values
  for(i = 0; i < n-k; i++){
   
//    data[i]=data[i]+data[i+1]+data[i+2]+data[i+3]+data[i+4];
      for(int j = i+1 ; j < i+k+1 ; j++){
        data[i] = data[i] + data[j];
      }
      data[i] = data[i]/(float)(k+1);
  }
 
 
  // Mean of all values in meaned data
  for (i = 0; i < n-k; i++){
      mean =  mean + data[i];
  }
  mean = mean/(float)n;

  // Normalising the meaned data
  for (i = 0; i < n-k; i++){
      data[i] = (data[i] - mean);
  }

  float maximum = data[0];
  for(i = 0; i < n-k; i++){

//    Serial.println(data[i]);
     if(data[i] > maximum){
       maximum = data[i];
     }
  }

  // To maintain The values in interval [-200,200]
  for(i = 0; i < n-k; i++){
      data[i] = (data[i]/maximum)*200;
  }
     
  for(i = 0; i < n-k; i++){

       // finding positive zero crossing rate pzcr
       if (data[i] < 0 && data[i+1] > 0){
           zcr = zcr + 1;
       }
       
       // finding negetive zero crossing rate pzcr
       else if(data[i] > 0 && data[i+1] < 0){
           zcr = zcr + 1;
       }
  }
     
  for(i = 0; i < n-k; i++){ 
    Serial.println(data[i]);
  }
  btserial.print(zcr);
  
}
