# go-sdk

## prepare protobuf-message

```
cd Axon_sdk
protoc --go_out=. --proto_path ../../../libraries/Axon_messages/protobuffers Axon_messages.proto3
sed -i 's/Axon_messages/Axon_sdk/g' Axon_messages.proto3.pb.go
```
