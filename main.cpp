#include "mbed.h" //p1
#include "uLCD_4DGL.h"

using namespace std::chrono;

Ticker Countdown;
InterruptIn button(BUTTON1);
int i = 0;
int state = 0;
Thread t;

EventQueue queue;

//int i = 0;
//int state = 1;

uLCD_4DGL uLCD(D1, D0, D2);

void qclock()
{
    uLCD.locate(0, 1);
    int sec = i / 10;
    int Sec = sec % 60;
    int minsec = i - sec * 10;
    int min = i / 600;
    uLCD.printf("%2d", min);
    uLCD.printf(":");
    uLCD.printf("%2d", Sec);
    uLCD.printf(":");
    uLCD.printf("%2d.", minsec);
    i++;
}

void qreset()
{
    i = 0;
    qclock();
}


void Clock()
{
    queue.call(qclock);
}

void reset()
{
    queue.call(qreset);
}

void Change()
{
    state++;
    if (state % 3 == 1)
    {
        Countdown.attach(&Clock,1000us);
    }
    else if (state % 3 == 2)
    {
        Countdown.detach();
    }
    else 
    {
        reset();
    }
}

int main() {
    t.start(callback(&queue, &EventQueue::dispatch_forever));
  button.rise(&Change);
  while(1)
{
    ThisThread::sleep_for(10ms);
}
}

