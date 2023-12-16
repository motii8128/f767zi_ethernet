#include "handler.hpp"
#include "SocketAddress.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

UDPHandler::UDPHandler()
{
    close();
}

void UDPHandler::init_net(const char *base_ip)
{
    net.set_dhcp(false);

    net.set_network(base_ip, "255.255.255.0", "");

    printf("Start connection\n");


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
    destination.set_ip_address(dest_ip);
    destination.set_port(port);
}

void UDPHandler::close()
{
    udp.close();
    net.disconnect();
}

template<typename T>
void UDPHandler::send(T data)
{
    char send_data[100];
    send_data = serialize<T>(data);
    if(const int result = udp.sendto(destination, send_data, sizeof(send_data)) < 0)
    {
        printf("[ERROR]Failed to send\n");
    }
    else
    {
        printf("[UDPHandler]send data\n");
    }
}

template <typename T>
T UDPHandler::receive()
{
    SocketAddress source;

    char buf[256];

    memset(buf, 0, sizeof(buf));
    if(const int result = udp.recvfrom(&source, buf, sizeof(buf)) < 0)
    {
        printf("[ERROR]Failed to receive\n");
        auto report = state_msg();
        report.message = std::string("[MicroController] Failed to get data");
        report.error = true;
        send<state_msg>(report);

    }
    else
    {
        printf("[UDPHandler]receive data\n");
        
        auto report = state_msg();
        report.message = std::string("[MicroController] Get data");
        report.error = false;
        send<state_msg>(report);

        return deserialize<T>(buf);
    }
}