FROM ubuntu:22.04

LABEL Description="UrbanMotion"

ENV HOME=/root
SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    gdb \
    wget \
    libssl-dev \
    git \
    cmake \
    libgl1-mesa-dev \
    xorg-dev \
    ca-certificates \
    python3 

WORKDIR /app

COPY . /app

RUN mkdir -p build && cd build && cmake .. && make

CMD ["bash", "-c", "./build/UrbanMotion; sleep 3600"]

