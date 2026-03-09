#ifndef MOV_H //in questo header dichiariamo i prototipi di funzione, che verranno creati in un altro programma
#define MOV_H  //creiamo l'header guard come fatto con pins.h

//movimento delle ruote
void initDriv();
void drivMot(int ind, int pwm);
void drivDir(int a, int pwm);
void testRot(int ind, int v);
void diag();

//pid
#define KP 2
#define KI 0
#define KD 0.12
void initCtrl();
void adjustCtrl(int angolo, int v);

#endif