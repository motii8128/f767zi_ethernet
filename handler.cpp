#include "handler.hpp"
#include "SocketAddress.h"
#include "stm32_hal_legacy.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

UDPHandler::UDPHandler():msg("[MicroController]safe callback")
{
    close();
}

void UDPHandler::init_net(const char *base_ip)
{
    net.set_dhcp(false);

    net.set_network(base_ip, "255.255.255.0", "");

    printf("[UDPHandler]Start connection\n");


    while(net.connect() != 0)
    {
        printf(".");
    }

    printf("[UDPHandler]connection success\n");
}

void UDPHandler::open_udp(const uint16_t port)
{
    udp.open(&net);
    udp.bind(port);
}

void UDPHandler::set_destination(const char *dest_ip, const uint16_t port)
{
    printf("set destination ip address and port\n");
    destination.set_ip_address(dest_ip);
    destination.set_port(port);
}

void UDPHandler::close()
{
    printf("[UDPHandler]close UDP\n");
    udp.close();
    printf("[UDPHandler]disconnect net\n");
    net.disconnect();
}


void UDPHandler::report()
{
    if(const int result = udp.sendto(destination, msg, sizeof(msg)) < 0)
    {
        printf("[ERROR]Failed to send\n");
    }
    else
    {
        
    }
}

template <typename U>
U UDPHandler::receive()
{
    SocketAddress source;

    char buf[256];

    memset(buf, 0, sizeof(buf));
    if(const int result = udp.recvfrom(&source, buf, sizeof(buf)) < 0)
    {
        printf("[ERROR]Failed to receive\n");
    }
    else
    {
        printf("[UDPHandler]receive data\n");
        report();

        return deserialize<U>(buf);
    }
}