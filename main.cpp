#include "mbed.h" //p1
#include "uLCD_4DGL.h"

using namespace std::chrono;

Ticker Countdown;
InterruptIn button(BUTTON1);

Thread t;

EventQueue queue;

//int i = 0;
//int state = 1;

uLCD_4DGL uLCD(D1, D0, D2);

void qreset()
{
    uLCD.reset();
    uLCD.printf("0:00:0.");
}

void qclock()
{
    static int i = 0;
    uLCD.locate(0, 1);
    int sec = i / 10;
    int minsec = i - sec * 10;
    int min = sec / 60;
    uLCD.printf("%2d", min);
    uLCD.printf(":");
    uLCD.printf("%2d", sec);
    uLCD.printf(":");
    uLCD.printf("%2d.", minsec);
    i++;
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
    static int state = 1;
    if (state % 3 == 1)
    {
        Countdown.attach(&Clock,10ms);
        state++;
    }
    else if (state % 3 == 2)
    {
        Countdown.detach();
        state++;
    }
    else 
    {
        reset();
        state++;
    }
}

int main() {
    t.start(callback(&queue, &EventQueue::dispatch_forever));
  uLCD.background_color(WHITE);
  uLCD.color(BLUE);
  uLCD.text_width(2); // 4X size text
  uLCD.text_height(2);
  button.rise(&Change);
  while(1);
}

