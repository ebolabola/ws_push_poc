// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: PresenceService.proto
#ifndef GRPC_PresenceService_2eproto__INCLUDED
#define GRPC_PresenceService_2eproto__INCLUDED

#include "PresenceService.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace interfaces {

// The greeting service definition.
class IPresenceService final {
 public:
  static constexpr char const* service_full_name() {
    return "interfaces.IPresenceService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Sends a greeting
    virtual ::grpc::Status PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::interfaces::PresenceState* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>> AsyncPresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>>(AsyncPresenceConnectRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>> PrepareAsyncPresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>>(PrepareAsyncPresenceConnectRaw(context, request, cq));
    }
    virtual ::grpc::Status PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::interfaces::PresenceState* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>> AsyncPresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>>(AsyncPresenceGetStateAndSubRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>> PrepareAsyncPresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>>(PrepareAsyncPresenceGetStateAndSubRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      // Sends a greeting
      virtual void PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) = 0;
      virtual void PresenceConnect(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void PresenceConnect(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void PresenceConnect(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      virtual void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) = 0;
      virtual void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>* AsyncPresenceConnectRaw(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>* PrepareAsyncPresenceConnectRaw(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>* AsyncPresenceGetStateAndSubRaw(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::interfaces::PresenceState>* PrepareAsyncPresenceGetStateAndSubRaw(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::interfaces::PresenceState* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>> AsyncPresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>>(AsyncPresenceConnectRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>> PrepareAsyncPresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>>(PrepareAsyncPresenceConnectRaw(context, request, cq));
    }
    ::grpc::Status PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::interfaces::PresenceState* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>> AsyncPresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>>(AsyncPresenceGetStateAndSubRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>> PrepareAsyncPresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>>(PrepareAsyncPresenceGetStateAndSubRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) override;
      void PresenceConnect(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void PresenceConnect(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void PresenceConnect(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void PresenceConnect(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) override;
      void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void PresenceGetStateAndSub(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::interfaces::PresenceState* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>* AsyncPresenceConnectRaw(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>* PrepareAsyncPresenceConnectRaw(::grpc::ClientContext* context, const ::interfaces::PresenceConnectRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>* AsyncPresenceGetStateAndSubRaw(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::interfaces::PresenceState>* PrepareAsyncPresenceGetStateAndSubRaw(::grpc::ClientContext* context, const ::interfaces::PresenceGetStateAndSubRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_PresenceConnect_;
    const ::grpc::internal::RpcMethod rpcmethod_PresenceGetStateAndSub_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Sends a greeting
    virtual ::grpc::Status PresenceConnect(::grpc::ServerContext* context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response);
    virtual ::grpc::Status PresenceGetStateAndSub(::grpc::ServerContext* context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_PresenceConnect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_PresenceConnect() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_PresenceConnect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceConnect(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPresenceConnect(::grpc::ServerContext* context, ::interfaces::PresenceConnectRequest* request, ::grpc::ServerAsyncResponseWriter< ::interfaces::PresenceState>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_PresenceGetStateAndSub : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_PresenceGetStateAndSub() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_PresenceGetStateAndSub() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceGetStateAndSub(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPresenceGetStateAndSub(::grpc::ServerContext* context, ::interfaces::PresenceGetStateAndSubRequest* request, ::grpc::ServerAsyncResponseWriter< ::interfaces::PresenceState>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_PresenceConnect<WithAsyncMethod_PresenceGetStateAndSub<Service > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_PresenceConnect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_PresenceConnect() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::interfaces::PresenceConnectRequest, ::interfaces::PresenceState>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::interfaces::PresenceConnectRequest* request, ::interfaces::PresenceState* response) { return this->PresenceConnect(context, request, response); }));}
    void SetMessageAllocatorFor_PresenceConnect(
        ::grpc::experimental::MessageAllocator< ::interfaces::PresenceConnectRequest, ::interfaces::PresenceState>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::interfaces::PresenceConnectRequest, ::interfaces::PresenceState>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_PresenceConnect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceConnect(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* PresenceConnect(
      ::grpc::CallbackServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* PresenceConnect(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_PresenceGetStateAndSub : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_PresenceGetStateAndSub() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(1,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::interfaces::PresenceGetStateAndSubRequest, ::interfaces::PresenceState>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::interfaces::PresenceGetStateAndSubRequest* request, ::interfaces::PresenceState* response) { return this->PresenceGetStateAndSub(context, request, response); }));}
    void SetMessageAllocatorFor_PresenceGetStateAndSub(
        ::grpc::experimental::MessageAllocator< ::interfaces::PresenceGetStateAndSubRequest, ::interfaces::PresenceState>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(1);
    #endif
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::interfaces::PresenceGetStateAndSubRequest, ::interfaces::PresenceState>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_PresenceGetStateAndSub() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceGetStateAndSub(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* PresenceGetStateAndSub(
      ::grpc::CallbackServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* PresenceGetStateAndSub(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_PresenceConnect<ExperimentalWithCallbackMethod_PresenceGetStateAndSub<Service > > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_PresenceConnect<ExperimentalWithCallbackMethod_PresenceGetStateAndSub<Service > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_PresenceConnect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_PresenceConnect() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_PresenceConnect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceConnect(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_PresenceGetStateAndSub : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_PresenceGetStateAndSub() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_PresenceGetStateAndSub() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceGetStateAndSub(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_PresenceConnect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_PresenceConnect() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_PresenceConnect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceConnect(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPresenceConnect(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_PresenceGetStateAndSub : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_PresenceGetStateAndSub() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_PresenceGetStateAndSub() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceGetStateAndSub(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPresenceGetStateAndSub(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_PresenceConnect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_PresenceConnect() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->PresenceConnect(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_PresenceConnect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceConnect(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* PresenceConnect(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* PresenceConnect(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_PresenceGetStateAndSub : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_PresenceGetStateAndSub() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(1,
          new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->PresenceGetStateAndSub(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_PresenceGetStateAndSub() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PresenceGetStateAndSub(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* PresenceGetStateAndSub(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* PresenceGetStateAndSub(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_PresenceConnect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_PresenceConnect() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::interfaces::PresenceConnectRequest, ::interfaces::PresenceState>(std::bind(&WithStreamedUnaryMethod_PresenceConnect<BaseClass>::StreamedPresenceConnect, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_PresenceConnect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status PresenceConnect(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceConnectRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPresenceConnect(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::interfaces::PresenceConnectRequest,::interfaces::PresenceState>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_PresenceGetStateAndSub : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_PresenceGetStateAndSub() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::interfaces::PresenceGetStateAndSubRequest, ::interfaces::PresenceState>(std::bind(&WithStreamedUnaryMethod_PresenceGetStateAndSub<BaseClass>::StreamedPresenceGetStateAndSub, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_PresenceGetStateAndSub() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status PresenceGetStateAndSub(::grpc::ServerContext* /*context*/, const ::interfaces::PresenceGetStateAndSubRequest* /*request*/, ::interfaces::PresenceState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPresenceGetStateAndSub(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::interfaces::PresenceGetStateAndSubRequest,::interfaces::PresenceState>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_PresenceConnect<WithStreamedUnaryMethod_PresenceGetStateAndSub<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_PresenceConnect<WithStreamedUnaryMethod_PresenceGetStateAndSub<Service > > StreamedService;
};

}  // namespace interfaces


#endif  // GRPC_PresenceService_2eproto__INCLUDED
