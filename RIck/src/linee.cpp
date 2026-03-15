#include <Arduino.h>
#include <cmath>
#include "imu.h"
#include "mov.h"
#include "pins.h"

bool touchedLine[8];
bool foundline = false;
int pinLine[] = {l1In, l1Es, l2In, l2Es, l3In, l3Es, l4In, l4Es};
unsigned long t = 0;
int photoAngle[] = {180, -90, 0, 90};
int refColor[] = {(113 + 922) / 2, (67 + 750) / 2, (147 + 960) / 2, (93 + 950) / 2, (133 + 903) / 2, (162 + 964) / 2, (175 + 964) / 2, (190 + 964) / 2};

void initLinee()
{
    for(int i = 0; i < 8; i++) pinMode(pinLine[i], INPUT);
}

void readLine()
{
    for(int i = 0; i < 8; i++)
    {
        Serial.print("Line n.");
        Serial.print(i);
        Serial.print(" = ");
        Serial.println(analogRead(pinLine[i]));
        delay(2000);
    }
}

void readSpecLine(int ind)
{
    Serial.print("Line n.");
        Serial.print(ind + 1);
        Serial.print(" = ");
        Serial.println(analogRead(pinLine[ind]));
        delay(2000);
}

void checkLine()
{
    int direzione[] = {0, 0, 0, 0};
    int escDir = 0;
    int check = 0;

    for(int i = 0; i < 8; i++)
    {
        touchedLine[i] = (analogRead(pinLine[i]) >= refColor[i]) ? 1 : 0;
        if(touchedLine[i])
        {
            foundline = true;  
            switch(i)
            {
                case 0:
                direzione[0] = photoAngle[0];
                break;

                case 1:
                direzione[0] = photoAngle[0];
                break;

                case 2:
                direzione[1] = photoAngle[1];
                break;

                case 3:
                direzione[1] = photoAngle[1];
                break;

                case 4:
                direzione[2] = photoAngle[2];
                break;

                case 5:
                direzione[2] = photoAngle[2];
                break;

                case 6:
                direzione[3] = photoAngle[3];
                break;

                case 7:
                direzione[3] = photoAngle[3];
                break;
            }
            check++;
        }
    }
    if(foundline)
    {
        for(int i = 0; i < 4; i++)
        {
            escDir += direzione[i];
        }
        escDir = (check == 2) ? escDir / 2 : escDir;
        if(escDir == 135 && (touchedLine[6] || touchedLine[7])) escDir = escDir * -1;
        while(millis() - t <= 250) { adjustCtrl(escDir, 250); }
        t = millis();
        foundline = false;
    }
    
} 