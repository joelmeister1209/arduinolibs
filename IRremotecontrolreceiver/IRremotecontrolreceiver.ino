/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <Motor.h>

int LED = A0;
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

Motor motor(6,9,20);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED,OUTPUT);
}

void loop() {
  int res = 0;
  if (irrecv.decode(&results)) {
    digitalWrite(LED,LOW);
    res = getResult();
    parseResult(res);
  }
  digitalWrite(LED,HIGH);
  delay(50);
}
void fwd(){
  motor.forward();
}
void back(){
  motor.backward();
}
void left(){
  motor.turnLeft();
}
void right(){
  motor.turnRight();
}
void idle(){
  motor.stop();
}
void parseResult(int res){
  res/=2;
   if(res > 79 && res <= 88){
     fwd();
   }
  else if(res > 89 && res < 98){
    back();
  }
  else if(res > 99 && res < 108){
    left();
  }
  else if(res > 109 && res < 118){
    right();
  }
  else{
    idle();
  }
}
int getResult(){
    delay(50);
    int i=0;
    int sum=0;
    for(i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
     Serial.print(results.rawbuf[i],DEC); 
     Serial.print(" "); 
    }
    Serial.println(sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]);
    irrecv.resume(); // Receive the next value
    return sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1];
}
