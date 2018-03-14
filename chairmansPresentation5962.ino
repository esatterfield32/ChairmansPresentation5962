#include <FastLED.h>
int piston4= 8;
int piston3= 6;
int piston2= 4;
int piston1= 2;
int basket1 = 0;
int basket2 = 1;
int incomingByte = 0;
bool basketOn[] = {false,false};
#define NUM_LEDS 76

#define LED_DATA_PIN 10

CRGB leds[NUM_LEDS];
CRGB blink_color; // saved color
CRGB snapshot_colors[] = {CRGB::White,CRGB::Blue,CRGB::Red,CRGB::Yellow,CRGB::Green};

void setup() {
   Serial.begin(9600);
   FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);
   for(int i = 2;  i<10; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,1);
    
   }
   for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB::Black;
    FastLED.show();
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
    else if (incomingByte == '5'){
    lightBaskets(basket1);
   }
   else if (incomingByte == '6'){
   lightBaskets(basket2);
   }
   else if (incomingByte == '7'){
    bigFinale();
   }
}
}

void powerPiston(int pistonPin){
  int pistonNumber = pistonPin/2 - 1;
  int endLED = 56-(pistonNumber) * 14;
  int startLED = 56-(pistonNumber + 1) * 14;
 
  if(digitalRead(pistonPin) == 1){  
   
    Serial.println(startLED);
    Serial.println(endLED);
    for (int led = startLED; led < endLED; led++) {
    leds[led] = CRGB::Yellow;
    FastLED.show();
    }
    digitalWrite(pistonPin, LOW);
    digitalWrite(pistonPin + 1,HIGH);
    Serial.println("relay on");
    
    } 
  
  else{
    digitalWrite(pistonPin, HIGH);
    digitalWrite(pistonPin +1, LOW);
    Serial.print("relay off");
    for (int led = startLED; led < endLED; led++) {
    leds[led] = CRGB::Black;
    FastLED.show();
    }
  }
}

void lightBaskets(int basketNumber){
  int LEDStart = 56 + (basketNumber)*10;
  int LEDEnd = LEDStart + 10;
  if (!basketOn[basketNumber]){
    for (int led = LEDStart; led < LEDEnd; led++) {
    leds[led] = CRGB::Yellow;
    FastLED.show();
    }
    basketOn[basketNumber] = true;
  }
  else{
    for (int led = LEDStart; led < LEDEnd; led++) {
    leds[led] = CRGB::Black;
    FastLED.show();
  }
  basketOn[basketNumber] = false;
  }
}

void bigFinale (){
   for (int colors = 0; colors < 255; colors++) {
    for (int windows = 0; windows < 4; windows++) {
      for (int led = 0; led < 14; led++) {
        int index = windows * 14 + led;
        int color_index = colors % 5 + windows;
        leds[index] = snapshot_colors[color_index];     
      }
    }
    for (int baskets = 0; baskets <2; baskets++){
      for (int led = 0; led < 10; led++) {
        int index = 56 + baskets*10 + led;
        int color_index = colors % 5 + baskets;
        leds[index] = snapshot_colors[color_index];
    }
    }
   }
}
