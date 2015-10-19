/*
  Soundy.h - Piezo library
  thebrentc@gmail.com
*/

// ensure this library description is only included once
#ifndef Soundy_h
#define Soundy_h

#include "Arduino.h"

// library interface description
class Soundy
{
  // user-accessible "public" interface
  public:
    //Soundy();
    Soundy(int);
    void helloworld(void);
    void playTone(int, int);
    boolean isNote(String);
    void playNote(String, int);
    void playABC(String);


  // library-accessible "private" interface
  private:
    int _pin;

};

#endif

