# Development

This document should help to setup a local environment for development.

## Prepare local setup

-   Download the MNIST-dataset and place them anywhere

    For testing the standard MNIST-dataset is used. Download the 4 files somewhere from the web:

    ```bash
    wget https://storage.googleapis.com/cvdf-datasets/mnist/train-images-idx3-ubyte.gz
    wget https://storage.googleapis.com/cvdf-datasets/mnist/train-labels-idx1-ubyte.gz
    wget https://storage.googleapis.com/cvdf-datasets/mnist/t10k-images-idx3-ubyte.gz
    wget https://storage.googleapis.com/cvdf-datasets/mnist/t10k-labels-idx1-ubyte.gz
    gzip -d train-images-idx3-ubyte.gz
    gzip -d train-labels-idx1-ubyte.gz
    gzip -d t10k-images-idx3-ubyte.gz
    gzip -d t10k-labels-idx1-ubyte.gz
    ```

-   Copy example-config diretory to `/etc/` and make sure, that the current user has access to the
    directory

    ```bash
    sudo cp -r ./Axon/example_configs/Axon

    sudo chown -R $(id -u):$(id -g) /etc/Axon
    ```

-   In file `/etc/Axon/Axon_testing.conf` update the path to the 4 MNIST files, so they
    point to the MNIST-files, which you downloaded eralier.

## Run project locally for testing

-   Build the components of the project with the [build-guide](/repo/build_guide/)

-   For the initial run, environment-variables have to be set to initialize the sqlite-database and
    create the first admin-user:

    ```bash
    export Axon_ADMIN_USER_ID=asdf
    export Axon_ADMIN_USER_=asdf
    export Axon_ADMIN_PASSPHRASE=asdfasdf
    ```

    These are the default testing-configs, to match with the test-confic
    `/etc/Axon/Axon_testing.conf`.

-   Exectute the binary without any flags. It uses by default the config of
    `/etc/Axon/Axon.conf` and the values of the example-config are enough for testing. The
    SQLite-database-file `/etc/Axon/Axon_db` is automatically created by the initial start.

## Testing

Run the compiled `Axon`-binary.

### Python-SDK-Test

There is a python-script, which uses the python-version fo the SDK to run basic tests against the
API.

-   install python and protobuf:

    ```bash
    sudo apt-get install python3 python3-pip python3-venv protobuf-compiler
    ```

-   go into the test-directory

    `cd Axon/testing/python_sdk_api`

-   create and prepare python-env and install packages

    ```bash
    python3 -m venv Axon_env

    source Axon_env/bin/activate

    cd Axon/src/sdk/python/Axon_sdk

    pip3 install -r requirements.txt
    ```

-   build proto-buffer messages

    ```bash
    cd Axon/src/sdk/python/Axon_sdk/Axon_sdk

    protoc --python_out=. --proto_path ../../../../libraries/Axon_messages/protobuffers  Axon_messages.proto3
    ```

-   run tests

    ```bash
    cd Axon/testing/python_sdk_api

    ./sdk_api_test.py
    ```

### Go-CLI-Test

-   install go and protobuffer-compiler

    ```bash
    apt-get install -y wget protobuf-compiler golang-goprotobuf-dev

    wget -c https://go.dev/dl/go1.22.5.linux-amd64.tar.gz

    tar -C /usr/local/ -xzf go1.22.5.linux-amd64.tar.gz
    ```

-   go to the location

    ```
    cd Axon/testing/go_cli_api
    ```

-   export environment-variables

    ```bash
    export Axon_ADDRESS=http://127.0.0.1:11418
    export Axon_USER=asdf
    export Axon_PASSPHRASE=asdfasdf

    export train_inputs=/tmp/train-images-idx3-ubyte
    export train_labels=/tmp/train-labels-idx1-ubyte
    export request_inputs=/tmp/t10k-images-idx3-ubyte
    export request_labels=/tmp/t10k-labels-idx1-ubyte
    ```

    (of course update the values for your specific setup)

-   run script to build the cli and copy it to the current directory

    ```bash
    ./build_and_copy_cli.sh
    ```

-   run test-script

    ```bash
    cli_test.sh
    ```
