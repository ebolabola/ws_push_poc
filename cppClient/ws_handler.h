#pragma once
#include <map>
#include <google\protobuf\io\coded_stream.h>


enum l3hWS_ERROR_CODE
{
	ResolveFailed,
	ConnectFailed,
	HanshakeFailed,
	ReadFailed,
	WriteFailed,
};


class l3hWS_SOCKET_HANDLER
{
public:
	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnError(l3hWS_ERROR_CODE code) = 0;
	virtual void Dispatch(google::protobuf::io::CodedInputStream& input) =0;
};
