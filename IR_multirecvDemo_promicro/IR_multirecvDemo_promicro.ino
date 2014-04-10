/*
tag
*/
#include <IRremote.h>
#include <NewPing.h>
#define SEND 0
#define RECEIVE 1
#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     9  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define BACK 3

int LED=3;
int LED1 = A3;
int LED2 = A2;
int LED3 = A1;
int LED4 = A0;

int RECV1 = 10;
int RECV2 = 16;
int RECV3 = 14;
int RECV4 = 15;
int MODE = SEND; //0 for send

IRrecv irrecv1(RECV1);
IRrecv irrecv2(RECV2);
IRrecv irrecv3(RECV3);
IRrecv irrecv4(RECV4);
IRsend irsend;
decode_results results;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


unsigned int not_it_buf[9] = {500,500,500,500,500,500,500,500}; //82
unsigned int ack_buf[9] = {500,500,500,500,500,500,500,1000}; //92
unsigned int ack2_buf[9] = {500,500,500,500,500,500,1000,1000}; //102- not sure if we should use
unsigned int tag_buf[9] = {500,500,500,500,500,1000,1000,1000}; //112


int use_test_circuit =1;

void setup()
{
  Serial.begin(9600);
  irrecv1.enableIRIn(); // Start the receiver
  irrecv2.enableIRIn(); // Start the receiver
  irrecv3.enableIRIn(); // Start the receiver
  irrecv4.enableIRIn(); // Start the receiver
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}
void loop() {
  getIRMessage();
  digitalWrite(LED,HIGH);
  delay(50);
}
void parseResult(int res, int dir){
  if(res > 87 && res < 96){
  }
  else if(res > 97 && res < 106){
    //got ack2 message
  }
  else if(res > 77 && res < 86){
     //8x500 us message - sees a robot that isn't it
   }
  else if(res > 107 && res < 116)
  {
  }
}
void getIRMessage(){
  if (irrecv1.decode(&results)) {
    LEDOn(LED1);
    int res = getResult(irrecv1);
    parseResult(res, FRONT);
  } else {LEDOff(LED1);}
  if (irrecv2.decode(&results)) {
    LEDOn(LED2);
    int res = getResult(irrecv2);
    parseResult(res, LEFT);
  } else {LEDOff(LED2);}
  if (irrecv3.decode(&results)) {
    LEDOn(LED3);
    int res = getResult(irrecv3);
    parseResult(res, RIGHT);
  } else {LEDOff(LED3);}
  if (irrecv4.decode(&results)) {
    LEDOn(LED4);
    int res = getResult(irrecv4);
    parseResult(res, BACK);
  } else {LEDOff(LED4);}

}
void resumeAll(){
    irrecv1.enableIRIn(); // Start the receiver
    irrecv2.enableIRIn(); // Start the receiver
    irrecv3.enableIRIn(); // Start the receiver
    irrecv4.enableIRIn(); // Start the receiver
    irrecv1.resume(); // Start the receiver
    irrecv2.resume(); // Start the receiver
    irrecv3.resume(); // Start the receiver
    irrecv4.resume(); // Start the receiver
}
void LEDOn(int pin){
       if(pin != -1){
          digitalWrite(pin, HIGH); //overwrite previous 
       }
}
void LEDOff(int pin){
       if(pin != -1){
          digitalWrite(pin, LOW); //overwrite previous 
       }
}
int getResult(IRrecv &irrecv){
    digitalWrite(LED,LOW);
    delay(50);
    //Serial.println(results.value, HEX);
    int i=0;
    int sum=0;
    for(i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
     Serial.print(results.rawbuf[i],DEC); 
     Serial.print(" "); 
    }
    Serial.println(sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]);
    irrecv.resume(); // Receive the next value
    return sum-results.rawbuf[0] ; //-results.rawbuf[results.rawlen-1];
}
