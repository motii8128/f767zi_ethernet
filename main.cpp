#include "DigitalOut.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "mbed.h"
#include "stm32f767xx.h"

#include "handler.hpp"
#include "interface.hpp"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

// main() runs in its own thread in the OS
int main()
{
    const char * unity_ip = "127.0.0.1";
    const uint16_t unity_port = 4000;

    const char *board_ip = "127.0.0.11";
    const uint16_t board_port = 5000;

    UDPHandler handler;
    led1 = 0;
    led2 = 0;
    led3 = 0;

    handler.init_net(board_ip, board_port);
    led1 = 1;

    handler.set_destination(unity_ip, unity_port);
    led2 = 1;

    while (1) {
        led3 = 0;
        ThisThread::sleep_for(1s);
        handler.report();
        led3 = 1;
        ThisThread::sleep_for(1s);
    }

    handler.close();
}

