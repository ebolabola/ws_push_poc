#pragma warning(disable: 4530)

#include "ws_client_boost.h"
#include <google\protobuf\io\coded_stream.h>
#include "ws_service.h";
#include "ws_handler.h"

namespace boost
{
#ifdef BOOST_NO_EXCEPTIONS
	void throw_exception(std::exception const& e)
	{
	};
#endif
}


l3hWS_CLIENT_BOOST::l3hWS_CLIENT_BOOST(l3hWS_SOCKET_HANDLER* handler):
	ws_(l3hWS_SERVICE::Context()),
	resolver(l3hWS_SERVICE::Context()),
	handler_(handler)
{
	ws_.binary(true);
}

void l3hWS_CLIENT_BOOST::Connect(const std::string& host, int port, const std::string& userContext)
{
	userContext_ = userContext;
	host_ = host;
	boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
	resolver.async_resolve(query, [this](const boost::system::error_code& ec, tcp::resolver::results_type results) {on_resolve(ec, results); });
}

void l3hWS_CLIENT_BOOST::Disconnect()
{
	handler_ = NULL;
}

void l3hWS_CLIENT_BOOST::Send(const std::vector<UINT8>& data)
{
	auto buff = new UINT8[data.size()];
	memcpy(buff, &data[0], data.size());

	auto buf = boost::asio::buffer(&data[0], data.size());
	ws_.async_write(buf, [&](const boost::system::error_code& ec, std::size_t bytes_transferred)
		{
			//delete []buff;
			on_write(ec, bytes_transferred);
		});
		
}

void l3hWS_CLIENT_BOOST::on_resolve(const boost::system::error_code& ec, tcp::resolver::results_type results)
{
	if (!ec)
	{
		beast::get_lowest_layer(ws_).async_connect(
			results,
			[this](beast::error_code ec, tcp::resolver::results_type::endpoint_type type) {on_connect(ec, type); });
	}
	else if (handler_)
		handler_->OnError(l3hWS_ERROR_CODE::ResolveFailed);
}
void l3hWS_CLIENT_BOOST::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
{
	if (!ec)
	{
		beast::get_lowest_layer(ws_).expires_never();

		ws_.set_option(
			websocket::stream_base::timeout::suggested(
				beast::role_type::client));

		ws_.set_option(websocket::stream_base::decorator(
			[this](websocket::request_type& req)
			{
				req.set(http::field::user_agent, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-async");
				req.set("WSDATA", userContext_);
			}));
		ws_.async_handshake(host_, "/ws",
			beast::bind_front_handler([this](beast::error_code ec) {on_handshake(ec); }));
	}
	else if (handler_)
		handler_->OnError(l3hWS_ERROR_CODE::ConnectFailed);

}
void l3hWS_CLIENT_BOOST::on_handshake(beast::error_code ec)
{
	if (!ec)
	{
		ws_.async_read(
			buffer_,
			[this](beast::error_code ec, std::size_t bytes_transferred) {on_read(ec, bytes_transferred); });

		if (handler_)
			handler_->OnConnect();

	}
	else if (handler_)
		handler_->OnError(l3hWS_ERROR_CODE::HanshakeFailed);

}


void l3hWS_CLIENT_BOOST::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);
	if (!ec)
	{
		static bool usePB = true;
		if (usePB)
		{
			google::protobuf::io::CodedInputStream input(boost::asio::buffer_cast<const unsigned char*>(buffer_.data()), buffer_.size());
			handler_->Dispatch(input);
		}
	
		buffer_.clear();
		ws_.async_read(
			buffer_,
			[this](beast::error_code ec, std::size_t bytes_transferred) {on_read(ec, bytes_transferred); });
	}
	else if (handler_)
		handler_->OnError(l3hWS_ERROR_CODE::ReadFailed);
}

void l3hWS_CLIENT_BOOST::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);
	if (!ec)
	{
	}
	else if (handler_)
		handler_->OnError(l3hWS_ERROR_CODE::WriteFailed);

}