#pragma warning(disable: 4530)

#include "ws_service.h"

net::io_context *l3hWS_SERVICE::ioc_;
void l3hWS_SERVICE::Init()
{
}

void l3hWS_SERVICE::Term()
{

}

void l3hWS_SERVICE::Update()
{
	if (ioc_)
	ioc_->poll_one();
}
net::io_context& l3hWS_SERVICE::Context()
{
	if (ioc_ == NULL)
	{
		ioc_ = new net::io_context();
	}
	return *ioc_;
}
