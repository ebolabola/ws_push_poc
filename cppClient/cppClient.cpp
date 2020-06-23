#define _WIN32_WINNT 0x600
#define WIN32_LEAN_AND_MEAN


#include <iostream>
#include <fstream>
#include <sstream>



#include "ws_push_client.h"
#include "ws_service.h"
#include "PresenceService.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp\impl\codegen\channel_interface.h>
#include "cppClient.h"
using namespace interfaces;

//#pragma comment( lib, "libprotobufd.lib" )
//#pragma comment( lib, "grpc.lib" )
//#pragma comment( lib, "grpc++.lib" )
//#pragma comment( lib, "cares.lib" )


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;


std::vector<char>  LoadFile(const std::string& path)
{
    std::streampos fileSize;
    std::ifstream file(path, std::ios::binary);

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> fileData(fileSize);
    file.read((char*)&fileData[0], fileSize);
    fileData.push_back(0);
    return fileData;
}



int main()
{
    l3hWS_SERVICE::Init();
    ws_push_client client;
    std::string userId = "userId";
    std::string signature = "signature";
    int generation = 1;
    client.Connect(userId, signature, generation);
    while (true)
    {
        l3hWS_SERVICE::Update();
        if (client.GetState() == Ready)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    auto cert = LoadFile("C:\\Libs\\grpc\\certificate.pem");
    grpc::SslCredentialsOptions opts;
    opts.pem_root_certs = &cert[0];

    auto channel_creds = grpc::SslCredentials(opts);
    std::unique_ptr<interfaces::IPresenceService::Stub> stub_(interfaces::IPresenceService::NewStub(grpc::CreateChannel("localhost:5001", channel_creds)));
    

    {
        ClientContext context;
        PresenceConnectRequest req;
        PresenceState st;
        req.set_userid(userId);
        auto result = stub_->PresenceConnect(&context, req, &st);

    }
    {
        ClientContext context;
        PresenceGetStateAndSubRequest req;
        PresenceState st;
        req.set_userid(userId);
        req.set_allocated_token(new PUSH_TOKEN( client.GetToken()));
        auto result = stub_->PresenceGetStateAndSub(&context, req, &st);
    }

    while (true)
    {
        l3hWS_SERVICE::Update();
        client.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    l3hWS_SERVICE::Term();
}
