#include "handler.hpp"
#include "SocketAddress.h"
#include <cstdint>
#include <cstdio>
#include <cstring>

void UDPHandler::init_net(const char *base_ip)
{
    net.set_dhcp(false);

    net.set_network(base_ip, "255.255.255.0", "");

    printf("Start connection\n");

    if(net.connect() != 0)
    {
        printf("[ERROR]Failed to connect network");
    }
    else
    {
        printf("[UDPHandler]network connection success\n");
    }
}

void UDPHandler::open_udp(const uint16_t port)
{
    udp.open(&net);
    udp.bind(port);
}

void UDPHandler::set_destination(const char *dest_ip, const uint16_t port)
{
    destination.set_ip_address(dest_ip);
    destination.set_port(port);
}

template<typename T>
T UDPHandler::send()
{
    
}

template <typename T>
T UDPHandler::receive()
{
    SocketAddress source;

    char buf[256];

    while(1)
    {
        memset(buf, 0, sizeof(buf));
        if(const int result = udp.recvfrom(&source, buf, sizeof(buf)) < 0)
        {
            printf("[ERROR]Failed to receive ");
        }
        else
        {
            return deserialize<T>(buf);
        }
    }
}