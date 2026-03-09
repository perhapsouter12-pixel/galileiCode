#include <Arduino.h>
#include <math.h>
#include <QuickPID.h>
#include "pins.h" //includiamo l'header che abbiamo creato
#include "mov.h" //dichiariamo anche i nostri prototipi di funzione, che qui dentro diventeranno vere e proprie funzioni.
#include "imu.h"

//dichiariamo degli array contenenti i nostri pin
int DriA[4] = {D1a, D2a, D3a, D4a};
int DriB[4] = {D1b, D2b, D3b, D4b};
int DriPWM[4] = {D1pwm, D2pwm, D3pwm, D4pwm};
float vs[4];
int theta[4] = {45, 135, 225, 315};//{315, 225, 135, 45};//{45, 135, 225, 315};
float orient = 0; //Come sta andando il robot.(input)
float adj = 0; //(output) //Quanto bisogna aggiungere per modificare l'orient in modo tale da essere uguale ad adj.
float ref = 0; //Come deve andare il robot (setpoint)
QuickPID adj_Or(&orient, &adj, &ref, KP, KI, KD,adj_Or.pMode::pOnError, adj_Or.dMode::dOnMeas, adj_Or.iAwMode::iAwCondition, adj_Or.Action::reverse); 

//ora possiamo dichiarare le nostre funzioni, ed esse verranno usate nel nostro file principale (main.cpp)
void initDriv()
{
    for(int i = 0; i < 4; i++)
    {
        //impostiamo i pin in OUTPUT
        pinMode(DriA[i], OUTPUT);
        pinMode(DriB[i], OUTPUT);
        pinMode(DriPWM[i], OUTPUT);
    }
}

void drivMot(int ind, int pwm)
{
    if(pwm > 0)
    {
        digitalWrite(DriA[ind], HIGH);
        digitalWrite(DriB[ind], LOW);
        analogWrite(DriPWM[ind], abs(pwm));
    }
    else
    {
        digitalWrite(DriA[ind], LOW);
        digitalWrite(DriB[ind], HIGH);
        analogWrite(DriPWM[ind], abs(pwm));
    }
}

void testRot(int ind, int v)
{
    if(v < 0) v = v * -1;
    drivMot(ind, v);
    delay(500);
    drivMot(ind, v * -1);
    delay(500);
    drivMot(ind, 0);
    delay(500);
}

void diag()
{
    unsigned long t = 0;
    while(millis() - t < 1000) adjustCtrl(45, 75);
    t = millis();
    while(millis() - t < 1000) adjustCtrl(-45, 75);
    t = millis();
    while(millis() - t < 1000) adjustCtrl(135, 75);
    t = millis();
    while(millis() - t < 1000) adjustCtrl(-135, 75);
    t = millis();
}
/* Sezione PID */

//Creiamo una classe QuickPID con i seguenti parametri nel costruttore.
//Gli indirizzi delle variabili dichiarate in precedenza, date a dei puntatori all'interno della classe.
//I 3 parametri aggiustatori dichiarati nel nostro header pid.h.
//Le varie modalità (date come valori di enumaratori) che sono rispettivamente:
//L'aggiustamento proporzionale è sull'errore orient-ref.
//L'aggiustamento derivativo è solo su orient, così da evitare "esplosioni" quando si cambia ref.
//L'aggiustamento integrativo non ha "wind-up".
//Segno dell'output (adj). è negativo, cioè reverse 



void initCtrl() //inizzaliziamo il pid
{
    adj_Or.SetSampleTimeUs(20 * 1e3); //mette quanto tempo deve impiegare per fare i calcoli (20ms).
    //NB: è lo stesso tempo di quanto l'angolo ci mette per essere letto e mandato.
    adj_Or.SetOutputLimits(-255, 255); //mettiamo che valore ci deve restituire (di default è 0,255. Noi lo mettiamo a -255 e 255).
    adj_Or.SetMode(1); //mettiamo il fatto che il calcolo dell'aggiustamento è automatico.
}

void adjustCtrl(int angolo, int v) //ora aggiustiamo l'angolo (funzione che va chiamata ad ogni loop)
{
    orient = getAngoloIMU(); //leggiamo come stiamo andando
    if(orient >= 180) orient -= 360; //diamo come stiamo andando in [-180; 180s]
    ref = 0;//angolo; //diamo dove vogliamo andare
    //prendiamo le componenti della velocità secondo l'angolo letto
    int vx = v * cos(radians(angolo));
    int vy = v * sin(radians(angolo));
    
   // Serial.printf("Vx = %d \n Vy = %d \n", vx, vy);
    if(adj_Or.Compute()) //se ha cambiato qualcosa
    {
        for(int i = 0; i < 4; i++)
        {
            
                /*Formula che prende conto il fatto che le ruote del robot sono messe a theta gradi dall'origine 0.
                Adj è la variabile che aggiustare dove il robot sta andando */
        
            vs[i] = (vx * sin(radians(theta[i]))) + (-1 * vy * cos(radians(theta[i]))) + adj;
        }
        
        /*
        vs[0] = cos(radians(angolo - 45));
        vs[1] = -1 * sin(radians(angolo - 45));
        vs[2] = -1 * cos(radians(angolo - 45));
        vs[3] = sin(radians(angolo - 45));
        */

        //for(int i = 0; i < 4; i++) Serial.println(vs[i]);
        for(int i = 0; i < 4; i++)
        {
            drivMot(i, vs[i] /* * 70 */); //attiviamo i motori a seconda della velocità regolata
        } 
    }
}
