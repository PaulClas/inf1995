#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifndef _SON_H_
#define _SON_H_

//valeurs du OCR0A selon la note

#define note45 142
#define note46 134
#define note47 127
#define note48 119
#define note49 113
#define note50 106
#define note51 100
#define note52 95
#define note53 89
#define note54 84
#define note55 80
#define note56 75
#define note57 71
#define note58 67
#define note59 63
#define note60 60
#define note61 56
#define note62 53
#define note63 50
#define note64 47
#define note65 45
#define note66 42
#define note67 40
#define note68 38
#define note69 36
#define note70 34
#define note71 32
#define note72 30
#define note73 28
#define note74 27
#define note75 25
#define note76 24
#define note77 22
#define note78 21
#define note79 20
#define note80 19
#define note81 18


class Son{
public:
    Son();
    void initialisation();
    void son();
    void arret();
    void chansonDeFin();
    void jouerSon(uint8_t operande);
    void chansonPoteau();

//private:
    //uint8_t tableau[36];
};

#endif /* _SON_H_ */
