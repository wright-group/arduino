// yaqd-wright
// wright-arduino firmware 1.0 
// Digital Write to pins 0-13 of Arduino Micro
// author:  Kent Meyer 10/2024

// note that all pins are set to LOW on reset...this can be reconfigured if needed
const int numPins = 14;
const int defaultPinSetting = LOW;


void setup() {
  for(int i=0; i<numPins; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i,defaultPinSetting);
  }
  Serial.begin(9600);
}


void loop()
{
 if (Serial.available()) serialEvent();
}


void serialEvent() {  // occurs whenever new data comes in the hardware serial RX

  int input_size=3;
  int pin=0;
  int setval=LOW;
  char input[input_size] = {0};
  char pins[1]={'0'};
  char setting[1]={'0'};
  byte size = Serial.readBytesUntil('\n', input, input_size);
  
  char code=input[0];
  pins[0]= input[1];
  setting[0]=input[2];

  //setval = atoi(setting);
  if (setting[0] != '1') {
     setval = LOW;
  }
  else {
     setval = HIGH;
  }
    
  pin = int (strtol(pins, NULL, 16));

  if (pin > (numPins-1)) {
     Serial.println("INVALID PIN");
     return;
  }
  
  if (code == 'M')  { 
      digitalWrite(pin, setval);
  }
  else if (code == 'R') {
      for(int i=0; i<numPins; i++) {
      digitalWrite(i,defaultPinSetting);
      }
  }
}
