#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>
#include <mutex>

#include "NetworkEvent.hpp"

using namespace boost::placeholders;

namespace component {
    struct network_client {
        using Message = boost::array<char, network::event::MAX_PACKET_SIZE>;
        using MessageQueue = std::priority_queue<
            Message,
            std::vector<Message>,
            network::event::NetworkMessageHeaderCompare
        >;

        network_client(std::string ip, int port)
        {
            m_ip = ip;
            m_port = port;
            m_ioContext = std::make_shared<boost::asio::io_service>();
            m_resolver = std::make_shared<boost::asio::ip::udp::resolver>(*m_ioContext);
            m_endpoint = std::make_shared<boost::asio::ip::udp::endpoint>(*m_resolver->resolve(boost::asio::ip::udp::v4(), m_ip, std::to_string(m_port)));
            m_socket = std::make_shared<boost::asio::ip::udp::socket>(*m_ioContext);
            m_socket->open(boost::asio::ip::udp::v4());
            m_socket->async_connect(*m_endpoint, boost::bind(&network_client::handle_connect, this, boost::asio::placeholders::error));
            m_inbox = std::make_shared<MessageQueue>();
            m_inboxMutex = std::make_shared<std::mutex>();
            m_thread = std::make_shared<std::thread>([this](){ m_ioContext->run(); });
        }

        ~network_client()
        {
            m_ioContext->stop();
            m_thread->join();
        }

        void handle_connect(const boost::system::error_code& error)
        {
            if (!error) {
                char buffer[sizeof(network::event::out::ConnectMessage)];
                network::event::out::ConnectMessage message = network::event::createEvent<network::event::out::ConnectMessage>();
                network::event::pack<network::event::out::ConnectMessage>(buffer, message);
                m_socket->async_send_to(boost::asio::buffer(buffer), *m_endpoint,
                    boost::bind(&network_client::handle_send, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
            }
        }

        void handle_send(const boost::system::error_code& error, std::size_t bytes_transferred)
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
            std::cout << "handle received bytes: " << bytes_transferred << std::endl;
            if (!error || error == boost::asio::error::message_size) {
                if (bytes_transferred < sizeof(network::event::NetworkMessageHeader)) {
                    std::cout << "network warning: received message is too small" << std::endl;
                } else if (!network::event::checkMagic(m_recvBuffer.data())) {
                    std::cout << "network warning: received message has invalid magic" << std::endl;
                } else {
                    network::event::NetworkMessageHeader *header = reinterpret_cast<network::event::NetworkMessageHeader *>(m_recvBuffer.data());
                    if (header->length != bytes_transferred) {
                        std::cout << "expected length: " << header->length << " actual length: " << bytes_transferred << std::endl;
                        std::cout << "network warning: received malformed message" << std::endl;
                    } else {
                        std::lock_guard<std::mutex> lock(*m_inboxMutex);
                        m_inbox->push(m_recvBuffer);
                    }
                }
            } else {
                std::cout << "network error: " << error.message() << std::endl;
            }
            m_socket->async_receive_from(boost::asio::buffer(m_recvBuffer), *m_endpoint,
                    boost::bind(&network_client::handle_receive, this, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }

        bool has_message()
        {
            std::lock_guard<std::mutex> lock(*m_inboxMutex);
            return !m_inbox->empty();
        }

        Message message_top()
        {
            std::lock_guard<std::mutex> lock(*m_inboxMutex);
            return m_inbox->top();
        }

        void message_pop()
        {
            std::lock_guard<std::mutex> lock(*m_inboxMutex);
            m_inbox->pop();
        }

        std::string m_ip;
        int m_port;
        std::shared_ptr<boost::asio::io_context> m_ioContext;
        std::shared_ptr<boost::asio::ip::udp::resolver> m_resolver;
        std::shared_ptr<boost::asio::ip::udp::endpoint> m_endpoint;
        std::shared_ptr<boost::asio::ip::udp::socket> m_socket;
        boost::array<char, network::event::MAX_PACKET_SIZE> m_recvBuffer;
        std::shared_ptr<MessageQueue> m_inbox;
        std::shared_ptr<std::mutex> m_inboxMutex;
        std::shared_ptr<std::thread> m_thread;
    };
};
