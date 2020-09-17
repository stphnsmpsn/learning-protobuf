#################################################################################
#    _____ _______ ________      __     By: Steve Sampson
#   / ____|__   __|  ____\ \    / /     Email: mail@stephensampson.dev
#  | (___    | |  | |__   \ \  / /      Created: 2020-09-16
#   \___ \   | |  |  __|   \ \/ /       Modified: 2020-09-16
#   ____) |  | |  | |____   \  /        Description: TODO:
#  |_____/   |_|  |______|   \/
#################################################################################

FROM ubuntu:latest
MAINTAINER Steve Sampson <mail@stephensampson.dev>

ENV TERM linux
ENV DEBIAN_FRONTEND noninteractive

# Some prerequisite packages easily available through apt
RUN apt-get update && apt-get install -y \
    cmake \
    gcc \
    g++ \
    gcovr \
    lcov \
    git \
    libboost-all-dev \
    protobuf-compiler

# Set working directory to /tmp
WORKDIR /tmp

# Some prerequisite packages that must be built from source
RUN git clone https://github.com/meltwater/served.git
RUN mkdir served.build && \
    cd served.build && \
    cmake ../served && \
    make && \
    make install

# Change working directory back to root
WORKDIR /

ADD ./ /protobeast
RUN cd protobeast && ./build.sh Both

CMD ./protobeast/Debug/protobeast
