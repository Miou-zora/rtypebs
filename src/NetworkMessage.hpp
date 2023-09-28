#pragma once

#include <string>
#include <ctime>
#include <cstdint>

namespace network {
    #pragma pack(push, 1)
    struct NetworkMessageHeader {
        u_int8_t type;
        u_int64_t id;
        time_t timestamp;
        u_int32_t length;
    };
    #pragma pack(pop)
}
