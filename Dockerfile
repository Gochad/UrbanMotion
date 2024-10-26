FROM ubuntu:22.04

LABEL Description="Basic C++ Docker Build Environment"

ENV HOME=/root
SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    gdb \
    wget \
    libssl-dev \
    cmake

WORKDIR /app

COPY . /app

RUN mkdir -p build && cd build && cmake .. && make

CMD ["./build/HelloWorld"]
