#ifndef multiThread_h
#define multiThread_h
#include <Arduino.h>

#define APPLICATION_CONTROL   0
#define DO_ONCE               1
#define PERPETUAL             2

template <class T>
class mThread
{
  public:
    mThread<T>();
    mThread<T>(T* t, void (*f)(T*, uint8_t) = NULL, uint8_t _mode = 0, unsigned long timer = 0);
    mThread<T>(void (*f)(uint8_t) = NULL, uint8_t _mode = 0, unsigned long timer = 0);
    void process();
    void addToQueue(uint8_t b);
    void rmFromQueue(uint8_t index);
    void forcedAddToQueue(uint8_t b, uint8_t index);
    unsigned long timeout = 0;
    unsigned long _timer;
    uint8_t onQueue = 0;
    uint8_t mode = 0;
  private:
    T* _t;
    void start();
    uint8_t queue[20];
    void (*_f)(uint8_t);
    void (*__f)(T*, uint8_t);
};

template <class T>
mThread<T>::mThread(T* t, void (*f)(T* _this, uint8_t), uint8_t _mode, unsigned long timer)
: _t(t){

        if (f != NULL) __f = f;
        _f = NULL;
        mode = _mode;
        _timer = timer;
        if (mode == 1){
          start();
        }
        else if (mode == 2){
          start();
        }

}

template <class T>
mThread<T>::mThread(void (*f)(uint8_t), uint8_t _mode, unsigned long timer)
:_t(){

        if (f != NULL) _f = f;
        __f = NULL;
        mode = _mode;
        _timer = timer;
        if (mode == 1){
          start();
        }
        else if (mode == 2){
          start();
        }

}

template <class T>
void mThread<T>::process(){
        if (onQueue>0 && millis()>timeout) {
                if (__f != NULL) __f(_t, queue[0]);
                else if (_f != NULL) _f(queue[0]);
                rmFromQueue(0);
                timeout = millis() + _timer;
                if (mode == 2) addToQueue(1);
                if (onQueue == 0)
                        timeout = 0;
        }
}


template <class T>
void mThread<T>::start(){
  timeout = millis() + _timer;
  addToQueue(1);
}

template <class T>
void mThread<T>::forcedAddToQueue(uint8_t b, uint8_t index){
        if (onQueue<=9) {
                if(onQueue == 0)
                        queue[0] = b;
                else{
                        for(int i=onQueue; i>index; i--)
                                queue[i]=queue[i-1];
                        queue[index]=b;
                }
                onQueue++;
        }
}

template <class T>
void mThread<T>::rmFromQueue(uint8_t index){
        if (onQueue > 0) {
                for (int i=index; i<onQueue; i++) {
                        queue[i] = queue[i+1];
                }
                queue[onQueue-1] = 0;
                onQueue--;
        }
}

template <class T>
void mThread<T>::addToQueue(uint8_t b){
        int index = -1;
        for (int i=0; i<onQueue; i++) {
                if (queue[i] == b)
                        index = i;
        }
        if (index>-1)
                rmFromQueue(index);
        forcedAddToQueue(b, onQueue);
}


#endif
