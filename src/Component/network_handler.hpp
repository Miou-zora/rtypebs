#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "NetworkEvent.hpp"

using namespace boost::placeholders;

namespace component {
    struct network_handler {
        network_handler();
    };
};
