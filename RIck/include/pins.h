#ifndef PINS_H //se questo header viene incluso in un progetto (inizio di una specie di if)
#define PINS_H //definiamo proprio il tutto (questo va incluso obbligatoriamente insieme a ifndef e endif, insieme formano l'headers guard)

//tutti i pin vengono definiti
//si ricorda che i pin sono basati sul robot Furio.

#define D1pwm 4
#define D1a 12
#define D1b 11

#define D2pwm 5
#define D2a 24
#define D2b 25

#define D3pwm 2
#define D3a 26
#define D3b 27

#define D4pwm 3
#define D4a 29
#define D4b 28

#define l1In A6
#define l1Es A7
#define l2In A9
#define l2Es A8
#define l3In A0
#define l3Es A1
#define l4In A3
#define l4Es A2


#endif //finiamo questa specie di if