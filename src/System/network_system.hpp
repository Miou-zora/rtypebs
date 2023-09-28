#pragma once

#include <string>
#include <iostream>

#include "registry.hpp"
#include "network_client.hpp"

void network_system(registry &r,
                    sparse_array<component::network_client> const &clients)
{
    (void)r;
    for (auto &client : clients)
    {
        if (!client.has_value())
            continue;
        client.value().m_ioContext->poll();
    }
}
