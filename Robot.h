#ifndef __ROBOT__
#define __ROBOT__

#include "Motor.h"

#define L 20

struct Robot
{
    double dl, dr;
    Motor right = Motor(6, 5);    
    Motor left = Motor(7, 8);   

    //vc: Target linear velocity of the robot (cm/sec)
    //wc: Target angular velocity of the robot (rad/sec)
    //The function uses inverse kinematics to set the desired angular velocities of the two motors
    void setTarget(double vc, double wc)
    {
        right.setTargetSpeed((2*vc+wc*L) / (2.0*R));
        left.setTargetSpeed((2*vc-wc*L) / (2.0*R));
    }

    //Modifies the PWM of the left and right motors to track the desired linear and angular velocities.
    void update(long deltaTicks1, long deltaTicks2)
    {
        dr = right.update(deltaTicks1);
        dl = left.update(deltaTicks2);
    }
};

#endif
