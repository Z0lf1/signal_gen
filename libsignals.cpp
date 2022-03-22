/*
 * signal generator 0.4
 * square, sawtooth, triangle, sine waves
 * not really sure of f to frequency ratio; will update
 * todo:  amplitude control
 *        figure out frequency control
 */

#include <Arduino.h>
#include "libsignals.h"

int square(int f) {
  PORTC=B11111111;
  delay(f)       ;
  PORTC=B00000000;
  delay(f)       ;
}

int sawtooth(int f){
  int counter=0  ;
  for(counter=255; counter > -1; counter--){
    PORTC=byte (counter);
    delay(f)            ;
  }
}

int triangle(int f){
  int counter=0  ;
  for(counter=255; counter > -1; counter--){
    PORTC=byte (counter);
    delay(f)     ;
  }
  for(counter=0  ; counter < 256; counter++){
    PORTC=byte (counter);
    delay(f)     ;
  }
}

float sine(int f){
  float pi=3.141516, angle;
  int   step, counter=0   ;
  for(counter=0; counter < 256; counter++){
    angle=(2 * pi * counter) / 255;
    step =sin  (angle) * 64 + 64  ;
    PORTC=byte (step)             ;
    delay(f)                      ;
  }
}

float hsine(int f){
  float pi=3.141516, angle;
  int   step, counter=0   ;
  for(counter=0; counter < 128; counter++){
    angle=(2 * pi * counter) / 255;
    step =sin  (angle) * 64 + 64  ;
    PORTC=byte (step)             ;
    delay(f)                      ;
  }
}

float pqrst(){
  float pi=3.141516, angle;
  int   step, counter=0   ;
//p wave
  for(counter=0; counter < 128; counter++){   //128=half sine
    angle=(2 * pi * counter) / 255;         
    step =sin  (angle) * 32 + 64  ;         
    PORTC=byte (step)             ;         
    delayMicroseconds(650)        ;           //p wave freq
  }
//pr segment
  delay(75);
//q wave
  for(counter=64; counter > 32; counter--){  //64=0v
    PORTC=byte (counter);
    delayMicroseconds(800);  //q wave freq
  }
//r wave
  for(counter=32 ; counter < 256; counter++){
    PORTC=byte (counter);
    delayMicroseconds(100)     ;
  }
  for(counter=255; counter > -1; counter--){
    PORTC=byte (counter);
    delayMicroseconds(100)     ;
  }
//s wave
  for(counter=-1  ; counter < 64; counter++){
    PORTC=byte (counter);
    delayMicroseconds(500);
  }
//st segment
  delay(80);
//t wave
  for(counter=0; counter < 128; counter++){   //128=half sine
    angle=(2 * pi * counter) / 255;
    step =sin  (angle) * 64 + 64  ;
    PORTC=byte (step)             ;
    delayMicroseconds(1500)       ;
  }
//bpm
  delay(400);
}
