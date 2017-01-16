#include "../multiThread.h"

void fiveMinute(uint8_t b){
  Serial.print("another 5 minutes passed!")
}

void tickle(uint8_t b){
  Serial.print("another minute passed!")
}

//Initialize timer
//mThread<int> object(function, PERPETUAL || DO_ONCE || APPLICATION_CONTROL , time_in_ms);

mThread<int> timer1(tickle, PERPETUAL, 60000*1);
mThread<int> timer2(fiveMinute, PERPETUAL, 60000*5);

void setup(){
  Serial.begin(9600);
  //Trigger the timer
  timer1.start();
  timer2.start();
}

void loop(){
  //process
  timer1.process();
  timer2.process();
}
