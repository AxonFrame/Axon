#!/bin/bash

# export Axon_ADDRESS=http://127.0.0.1:11418
# export Axon_USER=asdf
# export Axon_PASSPHRASE=asdfasdf

# export train_inputs=/home/neptune/Schreibtisch/mnist/train-images.idx3-ubyte
# export train_labels=/home/neptune/Schreibtisch/mnist/train-labels.idx1-ubyte
# export request_inputs=/home/neptune/Schreibtisch/mnist/t10k-images.idx3-ubyte
# export request_labels=/home/neptune/Schreibtisch/mnist/t10k-labels.idx1-ubyte


# build protobuffer for go sdk
# pushd ../../src/sdk/go/Axon_sdk
# protoc --go_out=. --proto_path ../../../libraries/Axon_messages/protobuffers Axon_messages.proto3
# popd

# build cli-binarygolangci-lint
# pushd ../../src/cli/Axonctl
# go build .
# popd
# cp ../../src/cli/Axonctl/Axonctl .

# cleanup before running tests
./Axonctl project delete --insecure cli_test_project
./Axonctl user delete --insecure cli_test_user

########################
echo ""
echo "project tests"
./Axonctl project create --insecure -n "cli test project" cli_test_project
./Axonctl project get --insecure cli_test_project
./Axonctl project list --insecure
./Axonctl project delete --insecure cli_test_project

########################
echo ""
echo "user tests"
./Axonctl user create --insecure -n "cli test user" -p "asdfasdf" cli_test_user
./Axonctl user get --insecure cli_test_user
./Axonctl user list --insecure
./Axonctl user delete --insecure cli_test_user

########################
echo ""
echo "dataset tests"
dataset_uuid=$(./Axonctl dataset create mnist --insecure -j -i $train_inputs -l $train_labels cli_test_dataset | jq -r '.uuid')
./Axonctl dataset get --insecure $dataset_uuid
./Axonctl dataset list --insecure
./Axonctl dataset delete --insecure $dataset_uuid

########################
echo ""
echo "cluster tests"
cluster_uuid=$(./Axonctl cluster create --insecure -j -t ./cluster_template cli_test_cluster | jq -r '.uuid')
./Axonctl cluster get --insecure $cluster_uuid
./Axonctl cluster list --insecure
./Axonctl cluster delete --insecure $cluster_uuid


########################
echo ""
echo "workfloat tests"
./Axonctl host list  --insecure

train_dataset_uuid=$(./Axonctl dataset create mnist --insecure -j -i $train_inputs -l $train_labels cli_test_dataset_train | jq -r '.uuid')
echo "Train-Dataset-UUID: $train_dataset_uuid"

request_dataset_uuid=$(./Axonctl dataset create mnist --insecure -j -i $request_inputs -l $request_labels cli_test_dataset_req | jq -r '.uuid')
echo "Request-Dataset-UUID: $request_dataset_uuid"

cluster_uuid=$(./Axonctl cluster create --insecure -j -t ./cluster_template cli_test_cluster | jq -r '.uuid')
echo "Cluster-UUID: $cluster_uuid"


# train test
echo "./Axonctl task create train --insecure -j -i $train_dataset_uuid:picture:picture_hex -o $train_dataset_uuid:label:label_hex -c $cluster_uuid cli_train_test_task"
task_uuid=$(./Axonctl task create train --insecure -j -i $train_dataset_uuid:picture:picture_hex -o $train_dataset_uuid:label:label_hex -c $cluster_uuid cli_train_test_task | jq -r '.uuid')
echo "Train-Task-UUID: $task_uuid"

while true; do
    ./Axonctl task get --insecure -c $cluster_uuid $task_uuid
    state=$(./Axonctl task get --insecure -j -c $cluster_uuid $task_uuid | jq -r '.state')
    if [[ "$state" == *"finished"* ]]; then
        echo "Process finished. Exiting loop."
        break
    fi
    sleep 1
done
./Axonctl task get --insecure -c $cluster_uuid $task_uuid


# save and restore test
./Axonctl cluster save --insecure -n cli_test_checkpoint $cluster_uuid
checkpoint_uuid=$(./Axonctl cluster save --insecure -j -n cli_test_checkpoint $cluster_uuid  | jq -r '.uuid')
sleep 1
echo "Checkpoint-UUID: $checkpoint_uuid"
./Axonctl checkpoint list --insecure

./Axonctl cluster delete --insecure $cluster_uuid
cluster_uuid=$(./Axonctl cluster create --insecure -j -t ./cluster_template cli_test_cluster | jq -r '.uuid')
echo "new Cluster-UUID: $cluster_uuid"
./Axonctl cluster restore --insecure -c $checkpoint_uuid $cluster_uuid

# request test
echo "./Axonctl task create request --insecure -j -i $request_dataset_uuid:picture:picture_hex -r label_hex:cli_test_output -c $cluster_uuid cli_request_test_task"
req_task_uuid=$(./Axonctl task create request --insecure -j -i $request_dataset_uuid:picture:picture_hex -r label_hex:cli_test_output -c $cluster_uuid cli_request_test_task | jq -r '.uuid')
echo "Request-Task-UUID: $req_task_uuid"

./Axonctl task list --insecure -c $cluster_uuid 
echo "$taskUuid"
./Axonctl task delete --insecure -c $cluster_uuid $task_uuid

while true; do
    ./Axonctl task get --insecure -c $cluster_uuid $req_task_uuid
    state=$(./Axonctl task get --insecure -j -c $cluster_uuid $req_task_uuid | jq -r '.state')
    if [[ "$state" == *"finished"* ]]; then
        echo "Process finished. Exiting loop."
        break
    fi
    sleep 1
done
./Axonctl task get --insecure -c $cluster_uuid $req_task_uuid

./Axonctl dataset list --insecure


result_uuid=$(./Axonctl dataset list --insecure -j | jq -r '.body[] | select(.[-1] == "cli_request_test_task") | .[1]')
echo "Result-Dataset-UUID: $result_uuid"

./Axonctl dataset get --insecure $result_uuid

./Axonctl dataset check --insecure -r $request_dataset_uuid $result_uuid

content=$(./Axonctl dataset content --insecure -j -c cli_test_output -o 100 -n 10 $result_uuid | jq -r 'length')
if [[ "$content" != 10 ]]; then
    echo "content as length of $content instead of 10"
fi

# clear all test-resources
./Axonctl checkpoint delete --insecure $checkpoint_uuid
./Axonctl cluster delete --insecure $cluster_uuid
./Axonctl dataset delete --insecure $train_dataset_uuid
./Axonctl dataset delete --insecure $request_dataset_uuid
./Axonctl dataset delete --insecure $result_uuid
