#include "keyscaner.h"
#include <wiringPi.h>
#include <pcf8574.h>
#define PCF8574_Address 0x20
#define EXTEND_BASE 64
#define RIGHT EXTEND_BASE + 0
#define DOWM  EXTEND_BASE + 1
#define UP    EXTEND_BASE + 2
#define LEFT  EXTEND_BASE + 3
#define LED   EXTEND_BASE + 4
#define BEEP  EXTEND_BASE + 7
#define KEYCENTER 28

KeyScaner::KeyScaner()
{
    //wiringPiSetup();
    pinMode (KEYCENTER,INPUT);
    pullUpDnControl(KEYCENTER, PUD_UP);
    pcf8574Setup(EXTEND_BASE,PCF8574_Address);
    pinMode(RIGHT,INPUT);
    pinMode(DOWM,INPUT);
    pinMode(UP,INPUT);
    pinMode(LEFT,INPUT);
    pinMode(LED,OUTPUT);
    digitalWrite(LED,HIGH);
    pinMode(BEEP,OUTPUT);
    digitalWrite(BEEP,HIGH);
}

int KeyScaner::ScanKeys()
{
    int tmp = 0;
    if((digitalRead(UP) == LOW) || (digitalRead(DOWM) == LOW) ||
        (digitalRead(LEFT) == LOW) || (digitalRead(RIGHT) == LOW)||
        (digitalRead(KEYCENTER) == 0))
    {
        digitalWrite(LED,LOW);
        //digitalWrite(BEEP,LOW);
        if(digitalRead(LEFT) == LOW)
            tmp = KEYR;
        else if(digitalRead(UP) == LOW)
            tmp = KEYD;
        else if(digitalRead(DOWM) == LOW)
            tmp = KEYU;
        else if(digitalRead(RIGHT) == LOW)
            tmp = KEYL;
        else if(digitalRead(KEYCENTER) == 0)
            tmp = KEYC;
        while((digitalRead(UP) == LOW) || (digitalRead(DOWM) == LOW) ||
            (digitalRead(LEFT) == LOW) || (digitalRead(RIGHT) == LOW)||
              (digitalRead(KEYCENTER) == 0))
        {
            delay(10);
        }
        digitalWrite(LED,HIGH);
        //digitalWrite(BEEP,HIGH);
    }
    return tmp;
}
