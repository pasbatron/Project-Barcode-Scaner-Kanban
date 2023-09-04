#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define LED_PIN_RED 3
#define LED_PIN_GREEN 2

String dataIn;
String dt[10];
boolean parsing=false;

SoftwareSerial mySerial(6, 7); //TX, RX
DFRobotDFPlayerMini myDFPlayer;

void parsingData(){
  int j=0;
  Serial.print("data masuk : ");
  Serial.print(dataIn);
  Serial.print("\n");
  dt[j]="";
  for(int i=1; i< dataIn.length(); i++){
    if ((dataIn[i] == '#') || (dataIn[i] == ',')){

      j++;
      dt[j]="";
    }
    else{
      dt[j] = dt[j] + dataIn[i];
    }
  }

  
  Serial.print("data 1 : ");
  Serial.print(dt[0]);


  
  if(dt[0] == "on"){
    digitalWrite(LED_PIN_RED, HIGH);
    digitalWrite(LED_PIN_GREEN, LOW);
    myDFPlayer.play(2);
    delay(1000);
  }

  else if(dt[0] == "off"){
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_GREEN, HIGH);
    while(true){
      myDFPlayer.play(1);
      delay(2000);
    }
  }
  
  Serial.print("\n");
  Serial.print("data 2 : ");
  Serial.print(dt[1].toInt());

  Serial.print("\n");
  Serial.print("data 3 : ");
  Serial.print(dt[2].toInt());
}


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  myDFPlayer.begin(mySerial);
  myDFPlayer.volume(60);  //Set volume value. From 0 to 30
  myDFPlayer.play(2);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  delay(2000);
  digitalWrite(LED_PIN_RED, HIGH);
  digitalWrite(LED_PIN_GREEN, HIGH);
}

void loop() {    
  if(Serial.available() > 1){
    String input = Serial.readString();
    Serial.println(input);
    dataIn = input;
    parsingData();
    delay(500);
  }
}
