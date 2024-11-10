FROM ubuntu:22.04

LABEL Description="UrbanMotion"

ENV HOME=/root
SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y install --no-install-recommends \
    build-essential \
    clang \
    gdb \
    wget \
    libssl-dev \
    git \
    cmake \
    libgl1-mesa-dev \
    xorg-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libglfw3-dev \
    mesa-common-dev \
    libglu1-mesa-dev \
    ca-certificates \
    python3 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN mkdir -p build && cd build && cmake .. && make

CMD ["bash", "-c", "./build/UrbanMotion || echo 'App exited with error'; sleep 3600"]
