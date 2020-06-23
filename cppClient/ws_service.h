#pragma once
#define BOOST_NO_EXCEPTIONS
#include <boost/beast/core.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>

class l3hWS_SERVICE {
public:
	static void Init();
	static void Term();
	static void Update();
	static net::io_context& Context();
private:
	static net::io_context *ioc_;
};

#pragma once
