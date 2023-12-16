#include "mbed.h"
#include "handler.hpp"
#include "interface.hpp"
#include <cstdint>
#include <cstring>
#include <stdint.h>
#include "stm32f767xx.h"

// main() runs in its own thread in the OS
int main()
{
    const char * unity_ip = "127.0.0.1";
    const uint16_t unity_port = 4000;

    const char *board_ip = "127.0.0.1";
    const uint16_t board_port = 5000;

    UDPHandler handler;

    handler.init_net(board_ip);

    handler.open_udp(board_port);

    handler.set_destination(unity_ip, unity_port);

    while (1) {
        auto report = state_msg();
        char msg[100] = "Hello, World";
        report.error = false;
        memcpy(report.message, msg, sizeof(msg));
    }

    handler.close();
}

