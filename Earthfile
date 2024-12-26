VERSION 0.8
FROM ubuntu:22.04

# configure apt to be noninteractive
ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN true

WORKDIR /code

local-setup:
    LOCALLY
    RUN git config --local core.hooksPath .githooks


cppcheck:
    RUN apt-get update && \
        apt-get install -y cppcheck
    COPY src src
    RUN rm -rf \
          src/libraries/Axon_messages/protobuffers/Axon_messages.proto3.pb.h
    RUN cppcheck --error-exitcode=1 src/Axon
    RUN cppcheck --error-exitcode=1 src/libraries


clang-format:
    RUN apt-get update && \
        apt-get install -y clang-format-15
    COPY src src
    RUN rm -rf \
          src/sdk/python \
          src/third-party-libs \
          src/libraries/Axon_messages/protobuffers/Axon_messages.proto3.pb.h
    COPY .clang-format .
    RUN find . -regex '.*\.\(h$\|c$\|hpp$\|cpp$\)' | while read f; do \
              clang-format-15 -style=file:.clang-format --dry-run --Werror $f; \
              if [ $? -ne 0 ]; then \
                  exit 1; \
              fi; done


flake8:
    RUN apt-get update && \
        apt-get install -y python3 python3-pip
    RUN pip3 install flake8
    COPY src src
    COPY testing testing
    COPY .flake8 .flake8
    RUN rm -rf src/sdk/python/Axon_sdk/Axon_sdk/Axon_messages/proto3_pb2.py src/sdk/python/Axon_sdk/Axon_env src/sdk/python/Axon_sdk/build
    RUN flake8 testing/python_sdk_api/sdk_api_test.py
    RUN flake8 src/sdk/python


ansible-lint:
    RUN apt-get update && \
        apt-get install -y python3 python3-pip
    RUN pip3 install ansible-lint
    COPY deploy deploy
    COPY .ansible-lint .ansible-lint
    RUN ansible-lint deploy/ansible/Axon


secret-scan:
    RUN apt-get update && \
        apt-get install -y python3 python3-pip git
    RUN pip3 install detect-secrets
    COPY . .
    RUN git ls-files -z | xargs -0 detect-secrets-hook --baseline .secrets.baseline


prepare-build-dependencies:
    RUN apt-get update && \
        apt-get install -y clang-15 \
                           make \
                           cmake \
                           bison \
                           flex \
                           git \
                           ssh \
                           libssl-dev \
                           libcrypto++-dev \
                           libboost-dev \
                           nlohmann-json3-dev \
                           uuid-dev  \
                           libsqlite3-dev \
                           protobuf-compiler \
                           # TODO:enable gpu init here again
                           # related issue: https://github.com/AxonFrame/Axon/issues/325
                           # nvidia-cuda-toolkit \
                           nano && \
        ln -s /usr/bin/clang++-15 /usr/bin/clang++ && \
        ln -s /usr/bin/clang-15 /usr/bin/clang
    COPY . .


compile-cli:
    RUN apt-get update && \
        apt-get install -y wget protobuf-compiler golang-goprotobuf-dev && \
        wget -c https://go.dev/dl/go1.22.5.linux-amd64.tar.gz && \
        tar -C /usr/local/ -xzf go1.22.5.linux-amd64.tar.gz
    COPY src src
    RUN cd ./src/sdk/go/Axon_sdk && \
        protoc --go_out=. --proto_path ../../../libraries/Axon_messages/protobuffers Axon_messages.proto3
    RUN cd src/cli/Axonctl && \
        /usr/local/go/bin/go build .
    SAVE ARTIFACT ./src/cli/Axonctl/Axonctl /tmp/Axonctl


compile-code:
    FROM +prepare-build-dependencies
    RUN cmake -DCMAKE_BUILD_TYPE=Release -Drun_tests=ON  .
    RUN make -j8
    RUN mkdir /tmp/Axon && \
        find src -type f -executable -exec cp {} /tmp/Axon \;
    SAVE ARTIFACT /tmp/Axon /tmp/Axon
    SAVE ARTIFACT /tmp/Axon AS LOCAL Axon

compile-code-debug:
    FROM +prepare-build-dependencies
    RUN cmake -DCMAKE_BUILD_TYPE=Debug -Drun_tests=ON  .
    RUN make -j8
    RUN mkdir /tmp/Axon && \
        find src -type f -executable -exec cp {} /tmp/Axon \;
    SAVE ARTIFACT /tmp/Axon /tmp/Axon
    SAVE ARTIFACT /tmp/Axon AS LOCAL Axon

build-image:
    ARG image_

    RUN apt-get update && \
        apt-get install -y openssl libuuid1 libcrypto++8 libsqlite3-0 libprotobuf23 libboost1.74 && \
        apt-get clean autoclean && \
        apt-get autoremove --yes && \
        chmod +x /usr/bin/Axon

    COPY +compile-code/Axon/Axon /usr/bin/

    # run Axon
    ENTRYPOINT ["/usr/bin/Axon"]

    SAVE IMAGE "$image_"


generate-docs:
    COPY +compile-code/Axon/Axon /tmp/

    RUN apt-get update && \
        apt-get install -y openssl libuuid1 libcrypto++8 libsqlite3-0 libprotobuf23 libboost1.74 libgbm-dev libasound2 xvfb dbus
    RUN chmod +x /tmp/Axon
    RUN /tmp/Axon --generate_docu

    RUN apt-get update && \
        apt-get install -y python3 \
                           python3-pip \
                           wget \
                           curl && \
        pip3 install mkdocs \
                     mkdocs-material \
                     mkdocs-swagger-ui-tag \
                     # pin mkdocs-drawio-exporter because 0.10.x is broken
                     mkdocs-drawio-exporter==0.9.1 && \
        curl -s https://api.github.com/repos/jgraph/drawio-desktop/releases/latest | grep browser_download_url | grep "amd64"  | grep "deb" | cut -d "\"" -f 4 | wget -i - && \ 
        apt -f -y install ./drawio-amd64-*.deb

    COPY mkdocs.yml .
    COPY CHANGELOG.md .
    COPY ROADMAP.md .
    COPY LICENSE .
    COPY docs docs
    RUN cp ./db.md docs/backend/
    RUN cp ./config.md docs/backend/
    RUN cp ./open_api_docu.json docs/frontend/

    # the `xvfb-run -a` comes from the following trouble-shooting for a headless execution in github actions:
    # https://github.com/LukeCarrier/mkdocs-drawio-exporter?tab=readme-ov-file#headless-usage
    RUN xvfb-run -a mkdocs build --clean

    SAVE ARTIFACT site AS LOCAL site


build-docs:
    ARG image_

    RUN apt-get update && \
        apt-get install -y python3

    COPY +generate-docs/site /Axon_docs

    WORKDIR /Axon_docs

    RUN useradd -m ubuntu
    RUN chown -R ubuntu:ubuntu .
    USER ubuntu

    CMD python3 -m http.server 8000

    SAVE IMAGE "$image_"
