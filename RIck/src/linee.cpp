#include <Arduino.h>
#include <cmath>
#include "imu.h"
#include "mov.h"
#include "pins.h"

int pinLine[8] = {l1In, l1Es, l2In, l2Es, l3In, l3Es, l4In, l4Es};
unsigned long t = 0;
bool touchedLine[8];
bool foundline = false;
int photoAngle[4] = {180, -90, 0, 90};
int refColor[8] = {(113 + 922) / 2, (67 + 750) / 2, (147 + 960) / 2, (93 + 950) / 2, (133 + 903) / 2, (162 + 964) / 2, (175 + 964) / 2, (190 + 964) / 2};

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
    int k;
    for(int i = 0; i < 8; i++)
    {
        touchedLine[i] = (analogRead(pinLine[i]) >= refColor[i]) ? 1 : 0;
        if(touchedLine[i])
        {
            foundline = true;
            k = floor(i / 2);
            direzione += photoAngle[k];
            check++;
        }
    }
    if(foundline)
    {
        direzione = (check >= 2) ? direzione / 2 : direzione;
        if(direzione == 135 && (touchedLine[6] || touchedLine[7])) direzione = direzione * -1;
        while(millis() - t <= 250) adjustCtrl(direzione, 250);
        t = millis();
        foundline = false;
    }
    
} 