int piston1= 2;
int piston2= 3;
int piston3= 4;
int piston4= 5;
int piston5= 6;
int incomingByte = 0;

void setup() {
   Serial.begin(9600);
   for(int i = 2;  i<7; i++){
    pinMode(i,OUTPUT);
   }
   
 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){
   incomingByte = Serial.read();
   Serial.println("recieved command" + (char)incomingByte);
   if (incomingByte == 'o'){
    
    Serial.println();
   }
   else{
    Serial.println();
   }
}
}

void powerPiston(int pistonNumber){
  if(digitalRead(pistonNumber) == 1){
    digitalWrite(pistonNumber, LOW);
    Serial.println("relay on");
  }
  else{
    digitalWrite(pistonNumber, HIGH);
    Serial.print("relay off");
  }
}

