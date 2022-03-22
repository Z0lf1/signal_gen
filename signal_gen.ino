//////////////////////
//*signal gen v0.7* //
// atmega2560       //
#include "libsignals.h"

////signals
/*https://upload.wikimedia.org/wikipedia/commons/0/09/ECG-PQRST%2Bpopis.svg
 *https://www.cvphysiology.com/Arrhythmias/A009
 * 
 * p wave       0.25    mV
 * r wave       1.6     mV
 * q wave       25%     R
 * t wave       0.1- 0.5mV
 * 
 * pr           120 - 220 ms
 * qrs          60  - 120 ms
 * qt           350 - 440 ms
 * st           5   - 150 ms    80ms typ
 * p            <120      ms
 * r peak       35  - 45  ms
 * 
 */


////////////////////////////////////////////
//vars
char sgSwitch='5';
float mmmg;     //
byte a;         //amp
int  f;         //freq
int aPot  = A0; //amp pot value
int fPot  = A1; //freq pot value

////////////////////////////////////////////

void setup() {
  Serial.begin(9600)   ;
  DDRC=B11111111       ;  //pins 30 to 37 - 30  to output
//DDRA=B11111111       ;  //pins 22 to 29 - ..+ to input
  pinMode(aPot, INPUT) ;
  pinMode(fPot, INPUT) ;
  Serial.println("que contá ura");
  Serial.println("1 = square   ");
  Serial.println("2 = sawtooth ");
  Serial.println("3 = triangle ");
  Serial.println("4 = sinewave ");
  Serial.println("5 = ECG      ");
}

////////////////////////////////////////////

void loop(){
  f=1000;
  
  if (Serial.available() > 0){
    sgSwitch=Serial.read();
  }

      switch(sgSwitch){
      case('1'):
        square(f);
      break;
      case('2'):
        sawtooth(f);
      break;
      case('3'):
        triangle(f);
      break;
      case('4'):
        sine(f);
      break;
      case('5'):
        pqrst();
      break;
      default:
        triangle(f);
      break;
    }
    
  Serial.println(PORTC, DEC);

}
