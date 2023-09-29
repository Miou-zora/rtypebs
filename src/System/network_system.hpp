#pragma once

#include <string>
#include <iostream>
#include <iomanip>

#include "registry.hpp"
#include "network_client.hpp"
#include "controllable.hpp"


static void printHexBytes(const unsigned char* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << ' ';
    }
    std::cout << std::endl;
}

void network_system(registry &r,
                    sparse_array<component::controllable> const &controls,
                    sparse_array<component::network_client> &clients)
{
    (void)r;
    for (auto &&[i, control, client] : indexed_zipper(controls, clients)) {
        while (client.value().has_message()) {
            auto message = client.value().message_top();
            network::event::NetworkMessageHeader *header = reinterpret_cast<network::event::NetworkMessageHeader *>(message.data());
            client.value().message_pop();
            std::cout << "Received message magic: " << header->magic[0] + header->magic[1] + header->magic[2] << std::endl;
            std::cout << "Received message type: " << (int)header->type << std::endl;
            std::cout << "Received message length: " << header->length << std::endl;
            std::cout << "Received message id: " << header->id << std::endl;
            std::cout << "Received message timestamp: "<< header->timestamp << std::endl;
            printHexBytes(reinterpret_cast<const unsigned char *>(message.data()), message.size());
        }
    }
}
