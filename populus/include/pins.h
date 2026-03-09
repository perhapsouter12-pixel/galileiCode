#ifndef PINS_H //se questo header viene incluso in un progetto (inizio di una specie di if)
#define PINS_H //definiamo proprio il tutto (questo va incluso obbligatoriamente insieme a ifndef e endif, insieme formano l'headers guard)

//tutti i pin vengono definiti
//si ricorda che i pin sono basati sul robot Furio.

#define D1pwm 4
#define D1a 9
#define D1b 10

#define D2pwm 5
#define D2a 11
#define D2b 12

#define D3pwm 2
#define D3a 29
#define D3b 30

#define D4pwm 3
#define D4a 31
#define D4b 32

#define l1In A7
#define l1Es A6
#define l2In A3
#define l2Es A2
#define l3In A1
#define l3Es A0
#define l4In A9
#define l4Es A8


#endif //finiamo questa specie di if