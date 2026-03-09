#include <Arduino.h>
#include "ball.h"


int sentDist;
int sentAngle;
byte  m;
byte which;


int getBall()
{
    if(Serial4.available() > 0)
    {
        m = Serial4.read();
        which = m & 1;
    }

    if(which == 0) { sentAngle = m; return sentAngle * 2; }
    else { sentDist = m; return sentDist; }
}