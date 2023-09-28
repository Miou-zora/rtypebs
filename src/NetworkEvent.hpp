#pragma once

#include <map>
#include <string>
#include <iostream>

#include "EventManager.hpp"
#include "NetworkMessage.hpp"

namespace network {
    class NetworkEvent {
        public:
            NetworkEvent() {};
            virtual ~NetworkEvent() = default;

            virtual u_int8_t getType() = 0;
            virtual u_int32_t getLength() = 0;
            virtual std::string serialize() = 0;

            template<typename T>
            T deserialize(char *buffer)
            {
                return T::deserialize(buffer);
            };
    };

    class ClientConnectedEvent : public NetworkEvent {
        public:
            ClientConnectedEvent() {};
            ~ClientConnectedEvent() = default;

            u_int8_t getType() override
            {
                return 0;
            };

            u_int32_t getLength() override
            {
                return 0;
            };

            std::string serialize() override
            {
                return "";
            };

            static ClientConnectedEvent deserialize(char *)
            {
                return ClientConnectedEvent();
            };
    };

    class ClientMovedEvent : public NetworkEvent {
        private:
            u_int32_t m_x;
            u_int32_t m_y;
    
        public:
            ClientMovedEvent(u_int32_t x, u_int32_t y) : m_x(x), m_y(y) {};
            ~ClientMovedEvent() = default;

            u_int8_t getType() override
            {
                return 1;
            }

            u_int32_t getLength() override
            {
                return sizeof(m_x) + sizeof(m_y);
            }

            std::string serialize() override
            {
                std::string buffer;
                buffer.append(reinterpret_cast<char *>(&m_x), sizeof(m_x));
                buffer.append(reinterpret_cast<char *>(&m_y), sizeof(m_y));
                return buffer;
            }

            static ClientMovedEvent deserialize(char *buffer)
            {
                u_int32_t x = *reinterpret_cast<u_int32_t *>(buffer);
                u_int32_t y = *reinterpret_cast<u_int32_t *>(buffer + sizeof(m_x));
                return ClientMovedEvent(x, y);
            };

            u_int32_t getX() const
            {
                return m_x;
            }

            u_int32_t getY() const
            {
                return m_y;
            }
    };

    void emitMatchingEvent(char *data)
    {
        network::NetworkMessageHeader *header = reinterpret_cast<network::NetworkMessageHeader *>(data);
        char *buffer = data + sizeof(network::NetworkMessageHeader);
        std::cout << "type: " << static_cast<int>(header->type) << std::endl;
        switch (header->type) {
            case 0:
                ecs::EventManager::getInstance().emit<network::ClientConnectedEvent>(network::ClientConnectedEvent::deserialize(buffer));
                break;
            case 1:
                ecs::EventManager::getInstance().emit<network::ClientMovedEvent>(network::ClientMovedEvent::deserialize(buffer));
                break;
            default:
                break;
        }
    }
}