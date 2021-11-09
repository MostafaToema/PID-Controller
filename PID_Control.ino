#include <Encoder.h>
#include "Robot.h"

#define T 50

Robot robot;

Encoder encoder1 = Encoder(18, 19);
Encoder encoder2 = Encoder(2, 3);
long newPos1 = 0, oldPos1 = 0, ticks1 = 0;  //1 -----> right  
long newPos2 = 0, oldPos2 = 0, ticks2 = 0;  //2 -----> left

long oldt;
double targetV = 0, targetW = 0;

void setup()
{
    Serial.begin(9600);
    oldt = millis();
}

void loop() 
{
    
    if(Serial.available())
    {
        String s = Serial.readStringUntil(' ');
        targetV = s.toInt();    //(cm/sec)

        s = Serial.readStringUntil('\n');
        targetW = s.toInt();    //(milli rad/sec)
        targetW /= 1000;        //(rad/sec)
    }
    
	robot.setTarget(targetV, targetW);
    
    while(millis()-oldt < T){}
    oldt = millis();
   
    newPos1 = encoder1.read();
    newPos2 = encoder2.read();
    ticks1 = newPos1 - oldPos1;
    ticks2 = newPos2 - oldPos2;
    oldPos1 = newPos1;
    oldPos2 = newPos2;
    
    robot.update(ticks1, ticks2);
    
    Serial.print(robot.right.targetSpeed);
    Serial.print(" ");
    Serial.print(robot.left.targetSpeed);
    Serial.print(" ");
    
    Serial.print(robot.right.pwm);   
    Serial.print(" ");
    Serial.println(robot.left.pwm);
}
