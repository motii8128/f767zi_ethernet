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

#include "interface.hpp"

class UDPHandler{
    public:
        void init_net(const char *base_ip);
        void open_udp(const uint16_t port);
        void set_destination(const char *dest_ip, const uint16_t port);

        template<typename T> void send(T data);
        template<typename T> T receive();
        
    private:
        EthernetInterface net;
        SocketAddress destination, source, base_data;
        UDPSocket udp;
};

#endif