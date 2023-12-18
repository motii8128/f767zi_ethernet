#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include "SocketAddress.h"
#include "UDPSocket.h"
#include "EthernetInterface.h"
#include "mbed.h"
#include "rtos.h"
#include <cstdint>
#include <stdint.h>
#include <vector>


class UDPHandler{
    public:
        UDPHandler();
        void init_net();
        void open_udp_server(const uint16_t base_port);
        void set_destination(const char *dest_ip, const uint16_t port);
        void close();

        void pub(const char *data);
        void sub(char *buf[256]);
        
    private:
        EthernetInterface net;
        SocketAddress destination, source, base_data;
        UDPSocket udp;
};

#endif