/*
  Soundy.h - Piezo library
  thebrentc@gmail.com
*/

#include "Arduino.h"
#include "Soundy.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
Soundy::Soundy(int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    Serial.begin(9600);
}

/*
Soundy::Soundy()
{
    _pin = 9;
    pinMode(_pin, OUTPUT);
    Serial.begin(9600);
}
*/

// Public Methods //////////////////////////////////////////////////////////////


/* @ref
 * http://www.arduino.cc/en/Tutorial/Melody
 */

/* ABC notation stuff */
// http://abcnotation.com/tunePage?a=trillian.mit.edu/~jc/music/abc/mirror/mindspring.com/~thornton.rose/HappyBirthday/0002 etc
int L = 150;

/*
String twinkleABC = "ccggaag2ffeeddc2 4";
String ateam = "cegGC gecG c5e5g5G5fAcFF gdBGG c3E5C5 z e gcegGC ";
*/

void Soundy::playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(_pin, LOW);
    delayMicroseconds(tone);
  }
}

void Soundy::helloworld() {
  Serial.print("Pin is ");
  Serial.println(_pin);
  for (int i = 4000; i > 10; i-= 10) {
    playTone(i,100);
    delay(100);
  }  
}


void Soundy::playNote(String note, int duration) {
  String names[] = { "C", "D", "E", "F", "G", "A", "B", "c", "d", "e", "f", "g", "a", "b"};
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 741, 560, 473, 351, 212, 90 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 14; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

boolean Soundy::isNote(String note) {
  return 
    note == " " 
    || note == "A" || note == "B" || note == "C" || note == "D" || note == "E" || note == "F" || note == "G" 
    || note == "a" || note == "b" || note == "c" || note == "d" || note == "e" || note == "f" || note == "g"
  ; 
}

void Soundy::playABC(String abc) {

  //abc.toLowerCase(); // legacy
  
  Serial.write("L="+L);
  
  for (int n = 0; n < abc.length(); n++) {
    char note = abc.charAt(n);    

    if (!isNote(String(note))) continue;
    Serial.write(note);

    int duration = 1;    
    if (n < abc.length()-1) {
      String next = String(abc.charAt(n+1));
      if (next.toInt() > 0) {
        duration = next.toInt();        
        n++;
      }
    }
    Serial.write(duration);    
        
    if (note == ' ') {
      delay ( duration * L);
    } else {
      playNote(String(note), duration * L);
    }
    delay( L / 2);    
  }
}


