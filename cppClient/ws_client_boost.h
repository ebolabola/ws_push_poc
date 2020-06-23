#pragma once

#ifndef _L3H_WS_CLIENT_BOOST_H_ 
#define _L3H_WS_CLIENT_BOOST_H_
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class l3hWS_SOCKET_HANDLER;

class l3hWS_CLIENT_BOOST
{
public:
	l3hWS_CLIENT_BOOST(l3hWS_SOCKET_HANDLER* handler);
	void Connect(const std::string& host, int port, const std::string& userContext);
	void Disconnect();
	void Send(const std::vector<UINT8>& data);
private:
	void on_resolve(const boost::system::error_code& ec, tcp::resolver::results_type results);
	void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);
	void on_handshake(beast::error_code ec);
	void on_read(beast::error_code ec, std::size_t bytes_transferred);
	void on_write(beast::error_code ec, std::size_t bytes_transferred);

	net::io_context ioc_;
	tcp::resolver resolver;
	websocket::stream<beast::tcp_stream> ws_;
	std::string host_;
	beast::flat_buffer buffer_;
	std::string userContext_;
	l3hWS_SOCKET_HANDLER* handler_;
};

#endif // _L3H_WS_CLIENT_BOOST_H_
