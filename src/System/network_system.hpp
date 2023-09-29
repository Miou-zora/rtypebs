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

void network_read_system(registry &r,
                    sparse_array<component::network_client> &clients)
{
    (void)r;
    for (auto &&[i, client] : indexed_zipper(clients)) {
        while (!client.value().get_inbox().empty()) {
            auto message = client.value().get_inbox().top();
            network::event::NetworkMessageHeader *header = reinterpret_cast<network::event::NetworkMessageHeader *>(message.data());
            client.value().get_inbox().pop();
            std::cout << "Received message magic: " << header->magic[0] + header->magic[1] + header->magic[2] << std::endl;
            std::cout << "Received message type: " << (int)header->type << std::endl;
            std::cout << "Received message length: " << header->length << std::endl;
            std::cout << "Received message id: " << header->id << std::endl;
            std::cout << "Received message timestamp: "<< header->timestamp << std::endl;
            printHexBytes(reinterpret_cast<const unsigned char *>(message.data()), message.size());
        }
    }
}

void network_write_system(registry &r,
                    sparse_array<component::network_client> &clients)
{
    (void)r;
    for (auto &&[i, client] : indexed_zipper(clients)) {
        while (!client.value().get_outbox().empty()) {
            auto message = client.value().get_outbox().top();
            client.value().get_outbox().pop();
            client.value().socket_send(message);
        }
    }
}

void network_control_system(registry &r,
                    sparse_array<component::controllable> const &controls,
                    sparse_array<component::network_client> &clients)
{
    (void)r;
    for (auto &&[i, control, client] : indexed_zipper(controls, clients)) {
        if (!client.has_value() || !control.has_value()) {
            continue;
        }
        int x_vel = control.value().is_key_right_pressed() - control.value().is_key_left_pressed();
        int y_vel = control.value().is_key_down_pressed() - control.value().is_key_up_pressed();
        if (x_vel != 0 || y_vel != 0) {
            network::event::out::MoveMessage message = network::event::createEvent<network::event::out::MoveMessage>(x_vel, y_vel);
            boost::array<char, 128> packed = network::event::pack<network::event::out::MoveMessage>(message);
            client.value().get_outbox().push(packed);
        }
    }
}