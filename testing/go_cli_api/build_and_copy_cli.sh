#!/bin/bash

# build protobuffer for go sdk
pushd ../../src/sdk/go/Axon_sdk
protoc --go_out=. --proto_path ../../../libraries/Axon_messages/protobuffers Axon_messages.proto3
popd

# build cli-binarygolangci-lint
pushd ../../src/cli/Axonctl
go build .
popd
cp ../../src/cli/Axonctl/Axonctl .

