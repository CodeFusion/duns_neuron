/*
 * Model Neuron
 * Kyle Ramey
 * Created February 2015
 */

#include <elapsedMillis.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

//soma button pins and thresholds
int soma0btn = A0;
int soma0thold = 400;
int soma1btn = A1;
int soma1thold = 400;
int soma2btn = A2;
int soma2thold = 400;

//time to reach threshold input, in ms
int reactionTime = 5000;

//# of LEDs per axon and LED pin
int axonLeds = 4;
int axonPin = 3;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, axonPin, NEO_GRB + NEO_KHZ_800);

//soma light pins
int soma0light = 4;
int soma1light = 5;
int soma2light = 6;

//servo
Servo servo;
int servoPin = 7;
int startPos = 0;
int endPos = 60;
int currPos = 0;

volitle boolean start = false;
int startBtn = 8;


void setup(){
  pinMode(axonPin, OUTPUT);
  pinMode(soma1light, OUTPUT);
  pinMode(soma2light, OUTPUT);
  pinMode(soma2light, OUTPUT);
  pinMode(motor, OUTPUT);
  servo.attach(7);
  servo.write(startPos);
  strip.begin();
  strip.show();
  attachInterrupt(0, startNeuron, RISING); //interrupt 0 is on Digital Pin 2
}

void loop(){
  //wait for start threshold at first soma
  if(analogRead(soma1btn > 100)){
    start = true;
  }
  if(!start){
    waitingAnimation();
  }else{
    if(soma(soma0btn, soma0thold)){
      sendSignal(0);
      if(soma(soma1btn, soma1thold)){
        sendSignal(1);
        if(soma(soma2btn, soma2thold)){
          sendSignal(2);
          fireMotor();
        }
      }
    }
    //YOU DIED. INSERT COIN TO TRY AGAIN.
    for(int i=0; i<3; i++){
      for(int n=0; n<axonLeds*4; n++){
        strip.setPixelColor(n, 255,0,0);
      }
      strip.show();
      delay(1000);
      for(int n=0; n<axonLeds*4; n++){
        strip.setPixelColor(n, 0,0,0);
      }
      strip.show();
    }
  }
}

boolean soma(btn, thold){
  elapsedMillis timeElapsed;
  while(timeElapsed < reactionTime){
    if(analogRead(btn) < thold){
      //threshold reached - go to the next soma
      return true;
    }
  }
  //threshold not reached in time
  return false;
}

void sendSignal(int neuron){
  //neopixel library
  int startLed = neuron*axonLeds;
  int endLed = (neuron+1)*axonLeds;
  for(int i = startLed; i<endLed; i++){
    strip.setPixelColor(i, 0,255,0);
    if(i >= startLed + 2){
      strip.setPixelColor(i-2, 0,0,0);
    }
    strip.show();
    delay(500);
  }
}

void fireMotor(){
  if(currPos == startPos){
    servo.write(endPos);
  }else if(currPos == endPos){
    servo.write(startPos);
  }
}

void startNeuron(){
  start = true;
  detachInterrupt(0);
}

void waitingAnimation(){
  //start at 255,0,0
  int r = 255, g = 0, b = 0;
  elapsedMillis timeElapsed;

  //go to 255,255,0
  for(g=0; g<=255; g++){
    for(int n=0; n<axonLeds*4; n++){
      strip.setPixelColor(n, r,g,b);
    }
    strip.show();
    timeElapsed = 0;
    while(timeElapsed < 100){
      if(start)
        return;
    }
  }
  //go to 0,255,0
  for(r=255; r>=0; r--){
    for(int n=0; n<axonLeds*4; n++){
      strip.setPixelColor(n, r,g,b);
    }
    strip.show();
    timeElapsed = 0;
    while(timeElapsed < 100){
      if(start)
        return;
    }
  }
  //go to 0,255,255
  for(b=0; b<=255; b++){
    for(int n=0; n<axonLeds*4; n++){
      strip.setPixelColor(n, r,g,b);
    }
    strip.show();
    timeElapsed = 0;
    while(timeElapsed < 100){
      if(start)
        return;
    }
  }
  //go to 0,0,255
  for(g=255; g>=0; g--){
    for(int n=0; n<axonLeds*4; n++){
      strip.setPixelColor(n, r,g,b);
    }
    strip.show();
    timeElapsed = 0;
    while(timeElapsed < 100){
      if(start)
        return;
    }
  }
  //go to 255,0,255
  for(r=0; r<=255; r++){
    for(int n=0; n<axonLeds*4; n++){
      strip.setPixelColor(n, r,g,b);
    }
    strip.show();
    timeElapsed = 0;
    while(timeElapsed < 100){
      if(start)
        return;
    }
  }
  //go to 255,0,0
  for(b=255; b>=0; b--){
    for(int n=0; n<axonLeds*4; n++){
      strip.setPixelColor(n, r,g,b);
    }
    strip.show();
    timeElapsed = 0;
    while(timeElapsed < 100){
      if(start)
        return;
    }
  }
}
