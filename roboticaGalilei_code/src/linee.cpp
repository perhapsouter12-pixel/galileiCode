#include <Arduino.h>
#include "imu.h"
#include "mov.h"
#include "pins.h"

int pinLine[8] = {l1In, l1Es, l2In, l2Es, l3In, l3Es, l4In, l4Es};
unsigned long t = 0;
bool touchedLine[8];
bool foundline = false;
int photoAngle[4] = {180, -90, 0, 90};
int refColor[8] = {(241 + 25) / 2, (321 + 23) / 2, (279 + 24) / 2, (256 + 20) / 2, (225 + 22) / 2, (262 + 19 ) / 2, (176 + 40) / 2, (322 + 29) / 2};

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
    int direzione = 0;
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
                direzione += photoAngle[0];
                check++;
                break;

                case 1:
                direzione += photoAngle[0];
                check++;
                break;

                case 2:
                direzione += photoAngle[1];
                check++;
                break;

                case 3:
                direzione += photoAngle[1];
                check++;
                break;

                case 4:
                direzione += photoAngle[2];
                check++;
                break;

                case 5:
                direzione += photoAngle[2];
                check++;
                break;

                case 6:
                direzione += photoAngle[3];
                check++;
                break;

                case 7:
                direzione += photoAngle[3];
                check++;
                break;
                
            }
        }
    }
    if(foundline)
    {
        direzione = (check >= 2) ? direzione / 2 : direzione;
        while(millis() - t <= 350) adjustCtrl(direzione, 250);
        t = millis();
        foundline = false;
    }
    
} 