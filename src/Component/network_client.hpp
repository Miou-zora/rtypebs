#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "NetworkMessage.hpp"
#include "EventManager.hpp"

using namespace boost::placeholders;

namespace component {
    struct network_client {
        network_client(std::string ip, int port) 
        {
            m_ip = ip;
            m_port = port;
            m_ioContext = std::make_unique<boost::asio::io_service>();
            m_resolver = std::make_shared<boost::asio::ip::udp::resolver>(*m_ioContext);
            m_endpoint = std::make_shared<boost::asio::ip::udp::endpoint>(*m_resolver->resolve(boost::asio::ip::udp::v4(), m_ip, std::to_string(m_port)));
            m_socket = std::make_shared<boost::asio::ip::udp::socket>(*m_ioContext);
            m_socket->open(boost::asio::ip::udp::v4());
            m_socket->async_connect(*m_endpoint, boost::bind(&network_client::handle_connect, this, boost::asio::placeholders::error));
        }

        void handle_connect(const boost::system::error_code& error)
        {
            if (!error) {
                m_socket->async_send_to(boost::asio::buffer("Hello", 5), *m_endpoint,
                    boost::bind(&network_client::handle_first_send, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
                ecs::EventManager::getInstance().emit<network::ClientConnectedEvent>(network::ClientConnectedEvent());
            }
        }

        void handle_first_send(const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            (void)bytes_transferred;
            if (!error) {
                m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint,
                    boost::bind(&network_client::handle_receive, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
            }
        }

        void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
        {
            std::cout << "handle received start bytes: " << bytes_transferred << std::endl;
            std::cout << "needs to be: " << sizeof(network::NetworkMessageHeader) << std::endl;
            if (!error || error == boost::asio::error::message_size)
            {
                if (bytes_transferred >= sizeof(network::NetworkMessageHeader)) {
                    network::emitMatchingEvent(m_recvBuffer.data());
                }
            }
            m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint,
                    boost::bind(&network_client::handle_receive, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }

        std::string m_ip;
        int m_port;
        std::shared_ptr<boost::asio::io_context> m_ioContext;
        std::shared_ptr<boost::asio::ip::udp::resolver> m_resolver;
        std::shared_ptr<boost::asio::ip::udp::endpoint> m_endpoint;
        std::shared_ptr<boost::asio::ip::udp::socket> m_socket;
        boost::array<char, 4096> m_recvBuffer;
    };
};
