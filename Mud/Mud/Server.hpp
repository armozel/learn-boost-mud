#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <list>
#include <boost/asio.hpp>
#include "Connection.hpp"

namespace Mud {
	namespace Server {
		class Server {
		public:
			typedef boost::asio::ip::tcp::socket SocketType;

			Server(int port) : m_signal_set(m_io_service, SIGINT, SIGTERM),
								m_acceptor(m_io_service,
											boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), port))
			{
				m_signal_set.async_wait(
					[this](boost::system::error_code error, int signal) {
						std::cout << "Server received signal(" << signal << ")"
						          << " requesting shutdown." << std::endl;
						m_acceptor.cancel();
					});
			}
			void Run()
			{
				Accept();
				std::cout << "Server now running." << std::endl;
				m_io_service.run();
			}
		private:
			void Accept() {
				m_connections.emplace_back(Connection(m_io_service));
				Connection* connection = m_connections.back();

				m_acceptor.async_accept(connection->Socket(),
					[this, &connection](boost::system::error_code error) {
						if (!error) {
							std::cout << "Connection accepted." << std::endl;
							connection->Start();
							Accept();
						}
					});
			}

			boost::asio::io_service m_io_service;
			boost::asio::signal_set m_signal_set;
			boost::asio::ip::tcp::acceptor m_acceptor;
			std::list<Connection*> m_connections;
		};
	}
}
#endif