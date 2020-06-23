protoc -I C:\ws\Proto\ --cpp_out=C:\ws\cppClient\Proto\Push C:\ws\Proto\push.proto
protoc -I C:\ws\Proto\ --cpp_out=C:\ws\cppClient\Proto\Push C:\ws\Proto\PushPresenceService.proto

protoc --grpc_out C:\ws\cppClient\Proto\Presence --cpp_out=C:\ws\cppClient\Proto\Presence -I C:\ws\Proto\  --plugin=protoc-gen-grpc="grpc_cpp_plugin.exe" C:\ws\Proto\PresenceService.proto
