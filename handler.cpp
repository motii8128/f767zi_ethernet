#include "handler.hpp"
#include "nsapi_types.h"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <vector>

UDPHandler::UDPHandler()
{
    close();
}

void UDPHandler::init_net()
{
    if(net.set_dhcp(true) != NSAPI_ERROR_OK)
    {
        printf("[ERROR] Failed to set mode(dhcp)");
    }
    if(net.set_blocking(1500) != NSAPI_ERROR_OK)
    {
        printf("[ERROR]Failed to set timeout\n");
    }
    
    printf("[UDPHandler]Start connection... \n");

    if(net.connect() != NSAPI_ERROR_OK)
    {
        printf("[ERROR] Failed to connect net.\n");
        close();
    }

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


void UDPHandler::send_data(vector<uint8_t> data)
{
    uint8_t array[data.size()];
    std::copy(data.begin(), data.end(), array);
    if(const int result = udp.sendto(destination, array, data.size() < 0))
    {
        printf("[ERROR]Failed to send\n");
    }
}

vector<uint8_t> UDPHandler::recv_data()
{
    SocketAddress source;
    vector<uint8_t> data;
    uint8_t buf[128] = {0};
    int result = udp.recvfrom(&source, buf, sizeof(buf));
    if(result < 0)
    {
        printf("[ERROR]Failed to receive\n");
    }
    else
    {
        printf("[UDPHandler]receive data\n");
        for(int i = 0; i < result; i++)
        {
            data.push_back(buf[i]);
        }

        data.erase(data.begin());
        data.pop_back();
    }

    return data;
}