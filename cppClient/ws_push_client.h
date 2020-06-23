#pragma once
#include <string>
#include "push.pb.h"
#include "ws_client_boost.h"
#include "ws_handler.h"

enum ClientState
{
	None,
	Connected,
	Ready
};

class ws_push_client: public l3hWS_SOCKET_HANDLER
{
public:
	ws_push_client();
	void Connect(const std::string& userId, const std::string& signature, int generation);
	void Update();
	virtual void OnConnect() override;
	virtual void OnDisconnect() override;
	virtual void OnError(l3hWS_ERROR_CODE code) override;
	virtual void Dispatch(google::protobuf::io::CodedInputStream& input) override;
	ClientState GetState();
	PUSH_TOKEN GetToken();
private:
	std::shared_ptr<l3hWS_CLIENT_BOOST> client_;
	std::string ToBase64(const std::vector<UINT8>& vec);
	ClientState clientState_;
	PUSH_TOKEN tk_;
	std::chrono::time_point<std::chrono::system_clock> tm_;

};

