#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include "SocketAddress.h"
#include "UDPSocket.h"
#include "mbed.h"
#include "EthernetInterface.h"
#include "rtos.h"
#include <cstdint>
#include <stdint.h>
#include <vector>
#include <string>

class UDPHandler{
    public:
        void init_net(const char *base_ip);
        void open_udp(const uint16_t port);
        void set_destination(const char *dest_ip, const uint16_t port);
        
    private:
        EthernetInterface net;
        SocketAddress destination, source, base_data;
        UDPSocket udp;
};

#endif