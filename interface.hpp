#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <vector>

struct wheel_msg{
    float motor_fl;
    float motor_fr;
    float motor_rl;
    float motor_rr;
};



template <typename T>
T deserialize(std::vector<uint8_t>& bytes) {
    static_assert(std::is_trivially_copyable<T>::value, "Data type is not trivially copyable");

    T data;
    std::memcpy(&data, bytes.data(), sizeof(data));
    return data;
}

template<typename T>
std::vector<uint8_t> serialize(const T& send_data)
{
    std::vector<uint8_t> bytes(sizeof(send_data));
    std::memcpy(bytes.data(), &send_data, sizeof(send_data));
    return bytes;
}


#endif