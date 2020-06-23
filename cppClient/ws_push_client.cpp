#include <google\protobuf\io\coded_stream.h>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <sstream>
#include <string>
#include <iostream>


#include "ws_push_client.h"
#include "push.pb.h"
#include <PushPresenceService.pb.h>
using namespace PushPresenceService;

ws_push_client::ws_push_client() :
    clientState_(None),
    tm_(std::chrono::system_clock::now())
{

}


void ws_push_client::Connect(const std::string& userId, const std::string& signature, int generation)
{
	auto host = "localhost";
	auto port = 56566;
	client_ = std::shared_ptr<l3hWS_CLIENT_BOOST>(new l3hWS_CLIENT_BOOST(this));
	WSClientData cl;
    cl.set_generation(generation);
    cl.set_userid(userId);
	cl.set_signature(signature);
	auto size = cl.ByteSizeLong();
	std::vector<UINT8> data(size);
	cl.SerializeToArray(&data[0], size);
    auto str = ToBase64(data);
    client_->Connect(host, port, str);
}

void ws_push_client::Update()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - tm_);
    if (elapsed.count() > 10)
    {
        tm_ = now;
        ClientPing ping;
        ping.set_dummy(1);
        auto size = ping.ByteSizeLong();
        std::vector<UINT8> data(size);
        ping.SerializeToArray(&data[0], size);
        client_->Send(data);
    }
}

void ws_push_client::OnConnect()
{
    clientState_ = Connected;
}

void ws_push_client::OnDisconnect()
{
}

void ws_push_client::OnError(l3hWS_ERROR_CODE code)
{

}



void ws_push_client::Dispatch(google::protobuf::io::CodedInputStream& input)
{
    if (clientState_ == Connected)
    {
        tk_.ParseFromCodedStream(&input);
        clientState_ = Ready;
    }
    else if (clientState_ == Ready)
    {

        unsigned int headerLen = 0;
        input.ReadLittleEndian32(&headerLen);
        auto l = input.PushLimit(headerLen);
        MessageHeader hdr;
        auto result = hdr.ParseFromCodedStream(&input);
        input.PopLimit(l);

        switch (hdr.messagetype())
        {
        case PushMessageType::PresenceService:
            PrescencePushData msg;
             msg.ParseFromCodedStream(&input);
            std::cout << "new messgae (PresenceService) " << msg.version() << " " << msg.dummy() << " " << msg.kuku() <<  std::endl;
            break;
        }
    }
}

ClientState ws_push_client::GetState()
{
    return clientState_;
}

PUSH_TOKEN ws_push_client::GetToken()
{
    return tk_;
}

std::string ws_push_client::ToBase64(const std::vector<UINT8>& vec)
{
    using namespace boost::archive::iterators;
    std::stringstream os;
    typedef
        base64_from_binary<
        transform_width<
        const UINT8*,
        6,
        8
        >
        >
        base64_text;

    std::copy(
        base64_text(&vec[0]),
        base64_text(&vec[0] + vec.size()),
        ostream_iterator<char>(os)
    );
    return os.str();
}
