#include "../multiThread.h"


void tickle(uint8_t b){
  Serial.print("another minute passed!")
}

//Initialize timer
mThread<int> timer1(tickle, PERPETUAL, 60000*1);

void setup(){
  Serial.begin(9600);
}

void loop(){
  //timer1 process
  timer1.process();
}
