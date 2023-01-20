#ifndef CONNECTION_HPP
#define CONNECTION_HPP
#include <boost/asio.hpp>
#include <iostream>

namespace Mud {
	namespace Server {
		class Connection {
		public:
			typedef boost::asio::ip::tcp::socket SocketType;
			explicit Connection(boost::asio::io_service& io_service)
				: m_socket(io_service),
				  m_outputStream(&m_outputBuffer)
			{}
			void Start() {
				std::cout << "Connection started" << std::endl;
				async_write(m_socket, m_outputBuffer, [this](boost::system::error_code error, std::size_t size)
					{
						if (!error) {
							std::cout << "Write successfully completed" << std::endl;
						}
					});
			}
			SocketType &Socket() { return m_socket; }
		private:
			boost::asio::streambuf m_outputBuffer;
			std::ostream m_outputStream;
			SocketType m_socket;
		};
	}
}
#endif