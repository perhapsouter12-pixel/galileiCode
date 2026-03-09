#include <Adafruit_BNO055.h> //header incluso nella libreria Adafruit_BNO055.
#include "imu.h" //header creato da noi che includerà tutte i prototipi di funzione.

Adafruit_BNO055 bno(55, 0x28); //creiamo l'istanza della classe Adafruit_BNO055, ricca di funzioni molto utili per noi.
unsigned long imu_t = 0; //timer che affianca la funzione millis(), utile per evitare il clock stretching e varie chiamate della funzione delay()
int angolo = 0; //angolo che la bussola andrà a leggere.
int angRel; //angolo relativo, il nostro angolo si baserà su quello preso all'inizio

void initImu()
{
    //Aspettiamo fino a quando la bussola non si connette
    while(!(bno.begin(OPERATION_MODE_IMUPLUS))) Serial.println("In attesa della bussola");
    bno.setExtCrystalUse(true); //Attiviamo il cristallo esterno (misura meglio)
    imu_t = millis(); //se sono passati dei secondi in millis(), metta imu_t a millis così da rispettare la condizione che metteremo nell'if più tardi.
    delay(500);
    //prendiamo il primo angolo che mettiamo come angolo 0, che normalmente sarebbe quello dove punta verso la porta
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); 
    angRel = (int) euler.x(); //leggiamo l'angolo che diventerà l'angolo relativo
}

float getAngoloIMU() //misuriamo l'angolo
{
    if(millis() - imu_t >= 20) //ogni 20 millisecondi (tempo che basta per la bussola di preparare i dati che il microcontrollore vuole)
    {
        imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
        /*
            imu:: è un namespace, come std::cout << ...
            Vector<3> è una classe con un template (una specie di parametro che gli si da).
            getVector() funzione che legge il vettore.
            Adafruit_BNO055::VECTOR_EULER legge il vettore della classe (la bussola), che è una variabile statica, cioè il suo valore è per tutte le istanze.
            e quindi accediamo al suo valore con nome_classe::variabile.
        */
        angolo = ((int) euler.x()) - angRel; //leggiamo l'asse x della bussola e la mettiamo dentro angolo
        //confrontiamo il tutto con l'angolo relativo
        angolo = (angolo < 0) ? angolo + 360 : angolo;
        imu_t = millis();
    }
    return angolo; //il valore di angolo viene dato.
}