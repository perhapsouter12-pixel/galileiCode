#ifndef PINS_H //se questo header viene incluso in un progetto (inizio di una specie di if)
#define PINS_H //definiamo proprio il tutto (questo va incluso obbligatoriamente insieme a ifndef e endif, insieme formano l'headers guard)

//tutti i pin vengono definiti
//si ricorda che i pin sono basati sul robot Furio.

#define D1pwm 2
#define D1a 11
#define D1b 12

#define D2pwm 5
#define D2a 25
#define D2b 24

#define D3pwm 6
#define D3a 26
#define D3b 27

#define D4pwm 23
#define D4a 21
#define D4b 22

#define l1In A14
#define l1Es A15
#define l2In A16
#define l2Es A17
#define l3In A20
#define l3Es A0
#define l4In A1
#define l4Es A2


#endif //finiamo questa specie di if