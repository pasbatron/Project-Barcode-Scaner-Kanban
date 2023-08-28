#include <SoftwareSerial.h>

#define BUTTON_PIN 2
#define LED_PIN 3

String dataIn;
String dt[10];
int i;
byte buttonState;

SoftwareSerial mySerialArduino(10, 11);

void parsingData(){
  int j=0;
  Serial.print("data masuk : ");
  Serial.print(dataIn);
  Serial.print("\n");
  dt[j]="";
  for(i=1;i<dataIn.length();i++){
    if ((dataIn[i] == '#') || (dataIn[i] == ',')){
      j++;
      dt[j]="";
    }else{
      dt[j] = dt[j] + dataIn[i];
    }
  }
  
  Serial.print("data 1 : ");
  Serial.print(dt[0]);
  if(dt[0] == "ng"){
    digitalWrite(LED_PIN, HIGH);
  }

    
  Serial.print("\n");
  Serial.print("data 2 : ");
  Serial.print(dt[1].toInt());
  Serial.print("\n");
  Serial.print("data 3 : ");
}


void setup(){
  Serial.begin(9600);
  mySerialArduino.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
}
void loop(){

  if(Serial.available() > 0){
    dataIn = Serial.readString();
    byte buttonState = digitalRead(BUTTON_PIN);
    parsingData(); 
  }
  delay(500);
}
