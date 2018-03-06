#include <FastLED.h>
int piston1= 2;
int piston2= 3;
int piston3= 4;
int piston4= 5;
int incomingByte = 0;

#define NUM_LEDS 56

#define LED_DATA_PIN 10

CRGB leds[NUM_LEDS];
CRGB blink_color; // saved color
CRGB snapshot_colors[] = {CRGB::White,CRGB::Blue,CRGB::Red,CRGB::Yellow,CRGB::Green};

void setup() {
   Serial.begin(9600);
   FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);
   for(int i = 2;  i<6; i++){
    pinMode(i,OUTPUT);
    
   }
   
 
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if (Serial.available()>0){
   incomingByte = Serial.read();
   Serial.println("recieved command" + (char)incomingByte);
  
   if (incomingByte == '1'){
    powerPiston(piston1);
   }
    else if (incomingByte == '2'){
    powerPiston(piston2);
   }
    else if (incomingByte == '3'){
    powerPiston(piston3);
   }
    else if (incomingByte == '4'){
    powerPiston(piston4);
   }
   
}
}

void powerPiston(int pistonNumber ){
  int startNumber = (pistonNumber - 2) * 14;
  int endNumber = (pistonNumber - 1) * 14;
 
  if(digitalRead(pistonNumber) == 1){  
   
    Serial.println(startNumber);
    Serial.println(endNumber);
    for (int led = startNumber; led < endNumber; led++) {
    leds[led] = CRGB::Yellow;
    FastLED.show();
    }
    digitalWrite(pistonNumber, LOW);
    Serial.println("relay on");
    
    } 
  
  else{
    digitalWrite(pistonNumber, HIGH);
    Serial.print("relay off");
    for (int led = startNumber; led < endNumber; led++) {
    leds[led] = CRGB::Black;
    FastLED.show();
    }
  }
}

