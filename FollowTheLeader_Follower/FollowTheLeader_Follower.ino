#include <NewPing.h>

#include <IRremote.h>
#include <CppList.h>
#include <IRremoteInt.h>

#include <Motor.h>

#include <IR.h>

#define WHEEL0 6
#define WHEEL1 9
#define MOTORENA 20
#define MSG_FWD 0
#define MSG_BACK 1
#define MSG_LEFT 2
#define MSG_RIGHT 3
#define MSG_SLOW 4
#define MSG_FAST 5
#define SLOW 75
#define FAST 125
#define MAXDIST 8
#define TURNSPEED 25
#define TRIG 7
#define ECHO 8
#define MAXDISTANCE 500
int LED = 17;
IR ir;
Motor motor(WHEEL0, WHEEL1, MOTORENA);
NewPing sonar(TRIG, ECHO, MAXDISTANCE);


int IT=0;
int motorSpeed = FAST; //175 slow, 255 fast 
void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
#define BIG 200
#define LITTLE 20
void loop(){
        digitalWrite(LED,HIGH);
	int res = ir.getMessage(); 
        if(res != -1){
          digitalWrite(LED,LOW);
        }	
         int son = sonar.ping_in();
          Serial.println(son);
        if(ir.front()){
            if(son > MAXDIST || son == 0)
	      motor.forward(motorSpeed);
            else
               motor.stop();
	}else if(ir.left()){
	    motor.turnLeft(TURNSPEED);
	}else if(ir.right()){
	    motor.turnRight(TURNSPEED);
	}else if(ir.back()){
	    motor.turnRight(TURNSPEED);
        } else if (son < MAXDIST && son){
            motor.stop();
        } else{
            //motor.turnLeft(TURNSPEED);
        }
	delay(BIG);
}
