#include <Arduino.h>
#include <math.h>

float ballAngle[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5};
int ballPin[16] = {A3, A2, A1, A0, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
float readVals[16];
float compX = 0;
float compY = 0;
float dist;
float angle;
char sendDist, sendAngle;
#define k 350

void setup() {
  Serial.begin(4800);
  for(int i = 0; i < 16; i++)
  {
    pinMode(ballPin[i], INPUT);
  }
}

void loop() {
  for(int b = 0; b < 16; b++)
  {
    for(int i = 0; i < k; i++)
    {
      readVals[b] = analogRead(ballPin[b]);
    }
    Serial.println(b + 1);
    Serial.println(readVals[b]);
    delay(7000);
    /*
    Serial.println(b + 1);
    Serial.println(readVal);
    delay(3000); */
    //if(readVal == 0) readVal = 1;
    compX += readVals[b] * cos(radians(ballAngle[b]));
    compY += readVals[b] * sin(radians(ballAngle[b]));
  }
  dist = sqrt(pow(compX * (180 / 3.14), 2) + pow(compY * (180 / 3.14), 2));
  angle = atan((compY / compX)) * (180 / 3.14);
  sendAngle = angle / 2;
  sendDist = dist;
  //Serial.println(angle);
  //delay(5000);
  //angleSend = angle;
  //Serial.write(angle/*Send*/);
  if(sendAngle % 2 == 1) sendAngle++;
  if(sendDist % 2 == 0) sendDist++;
  Serial.write(sendAngle);
  compX = 0;
  compY = 0;
  //Serial.write(dist);
  //possibile: delay(200);
  //Serial.write(angle / 2);
}