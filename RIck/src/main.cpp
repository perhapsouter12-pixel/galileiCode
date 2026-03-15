#include <Arduino.h>
//includiamo i nostri header creati
#include "pins.h"
#include "mov.h"
#include "linee.h"
#include "imu.h"
#include "ball.h"

//morale n1: FAI TUTTI I TEST
//morale n2: studia
void setup() {
  //varie inizzalizazioni
  Serial.begin(9600);
  Serial4.begin(9600);
  //ora possiamo chiamare le nostre funzioni create nei vari header
  initDriv();
  initImu();
  initCtrl();
  initLinee();
}

void loop() {
  checkLine();  
  adjustCtrl(0, 0);
  
}
