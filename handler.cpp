#include "handler.hpp"
#include "SocketAddress.h"
#include "nsapi_types.h"
#include "stm32_hal_legacy.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

UDPHandler::UDPHandler()
{
    close();
}

void UDPHandler::init_net()
{
    net.set_dhcp(true);
    net.set_blocking(1500);
    
    printf("[UDPHandler]Start connection... \n");

    net.connect();

    printf("[UDPHandler] Successed to connect net .\n");
}

void UDPHandler::open_udp_server(const uint16_t base_port)
{
    SocketAddress address;
    nsapi_error_t error = net.get_ip_address(&address);
    udp.open(&net);
    udp.bind(base_port);
    printf("[UDPHandler]open UDP(%s:%d).\n", address.get_ip_address(), base_port);
}

void UDPHandler::set_destination(const char *dest_ip, const uint16_t port)
{
    destination.set_ip_address(dest_ip);
    destination.set_port(port);
    printf("[UDPHandler]set destination (%s:%d)\n", dest_ip, port);
}

void UDPHandler::close()
{
    printf("[UDPHandler]close UDP\n");
    udp.close();
    printf("[UDPHandler]disconnect net\n");
    net.disconnect();
}


void UDPHandler::pub(const char *data)
{
    if(const int result = udp.sendto(destination, data, sizeof(data)) < 0)
    {
        printf("[ERROR]Failed to send\n");
    }
}

void UDPHandler::sub(char *buf[256])
{
    SocketAddress source;

    memset(buf, 0, sizeof(*buf));
    const int result = udp.recvfrom(&source, buf, sizeof(*buf));
    if(result < 0)
    {
        printf("[ERROR]Failed to receive\n");
    }
    else
    {
        printf("[UDPHandler]receive data\n");
        *buf[result] = '\0';
    }
}