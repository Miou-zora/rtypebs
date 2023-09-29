#pragma once

#include <string>
#include <ctime>
#include <cstdint>
#include <cstring>
#include <stdexcept>

#include <boost/array.hpp>

namespace network {
    namespace event {
        static const u_int32_t MAX_PACKET_SIZE = 128;
        static const char MAGIC[3] = {'B', 'T', 'C'};
        static u_int64_t g_packetId = 0;

        #pragma pack(push, 1)
        struct NetworkMessageHeader {
            char magic[3];
            u_int8_t type;
            u_int64_t id;
            time_t timestamp;
            u_int32_t length;
        };
        #pragma pack(pop)

        // comparator for priority queue _Compare
        struct NetworkMessageHeaderCompare {
            bool operator()(const NetworkMessageHeader &lhs, const NetworkMessageHeader &rhs) const
            {
                return (lhs.id > rhs.id || (lhs.id == rhs.id && lhs.timestamp > rhs.timestamp));
            }

            bool operator()(const NetworkMessageHeader &lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(lhs, *header));
            }

            bool operator()(const char *lhs, const NetworkMessageHeader &rhs) const
            {
                const NetworkMessageHeader *header = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                return (this->operator()(*header, rhs));
            }

            bool operator()(const char *lhs, const char *rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs);
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs);
                return (this->operator()(*header_lhs, *header_rhs));
            }

            bool operator()(const boost::array<char, MAX_PACKET_SIZE> &lhs, const boost::array<char, MAX_PACKET_SIZE> &rhs) const
            {
                const NetworkMessageHeader *header_lhs = reinterpret_cast<const NetworkMessageHeader *>(lhs.data());
                const NetworkMessageHeader *header_rhs = reinterpret_cast<const NetworkMessageHeader *>(rhs.data());
                return (this->operator()(*header_lhs, *header_rhs));
            }
        };

        bool checkMagic(char *buffer)
        {
            return std::memcmp(buffer, MAGIC, sizeof(MAGIC)) == 0;
        }

        namespace in {
            #pragma pack(push, 1)
            struct WelcomeMessage {
                WelcomeMessage() = default;

                NetworkMessageHeader header;
                static const u_int8_t type = 0;
            };

            struct MoveMessage {
                MoveMessage(u_int32_t _x, u_int32_t _y)
                    : x(_x), y(_y) {}

                NetworkMessageHeader header;
                static const u_int8_t type = 1;
                float x;
                float y;
            };
            #pragma pack(pop)
        }

        namespace out {
            #pragma pack(push, 1)
            struct ConnectMessage {
                ConnectMessage() = default;

                NetworkMessageHeader header;
                static const u_int8_t type = 0;
            };

            struct MoveMessage {
                MoveMessage(u_int32_t _x, u_int32_t _y)
                    : x(_x), y(_y) {}

                NetworkMessageHeader header;
                int32_t x;
                int32_t y;
                static const u_int8_t type = 1;
            };
            #pragma pack(pop)
        }

        template<typename T, class ...Args>
        T createEvent(Args &&...args)
        {
            T message(std::forward<Args>(args)...);
            std::memcpy(message.header.magic, MAGIC, 3);
            message.header.type = T::type;
            message.header.id = g_packetId++;
            message.header.timestamp = std::time(nullptr);
            message.header.length = sizeof(T);
            return (message);
        }

        template<typename T>
        void pack(char *buffer, T &message)
        {
            std::memcpy(buffer, &message, sizeof(T));
        }

        template<typename T>
        boost::array<char, MAX_PACKET_SIZE> pack(T &message)
        {
            boost::array<char, MAX_PACKET_SIZE> buffer;
            std::memcpy(buffer.data(), &message, sizeof(T));
            return (buffer);
        }

        template<typename T>
        T unpack(char *buffer)
        {
            return (*reinterpret_cast<T *>(buffer));
        }
    }
}
