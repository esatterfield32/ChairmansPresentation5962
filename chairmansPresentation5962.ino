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
    powerPiston(piston5);
   }
    else if (incomingByte == '6'){
    
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

