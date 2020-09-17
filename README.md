# protobeast

Protobeast uses Served (built on Boost.ASIO) to create a simple webserver and expose an API. 

This project's purpose is to serve as a testing grounds for me to begin learning Protocol Buffers (as well as to practice my CMake project skills). 

All internal communications will be using Protocol buffers but actual request/response with an endpoint will be in JSON currently (for legacy compatibility) 

## Prerequisites

1. CMake
2. GCC / G++
3. gcovr / lcov
4. git
5. Boost 
6. Protobuf
7. Served

Most of these can all easily be obtained from apt on ubuntu using the following: 
```
apt update && apt install -y \
    cmake \
    gcc \
    g++ \
    gcovr \
    lcov \
    git \
    libboost-all-dev \
    protobuf-compiler
```

Then we just need to get 7. Served:
```
cd /tmp && \
    git clone https://github.com/meltwater/served.git && \
    mkdir served.build && \
    cd served.build && \
    cmake ../served && \
    make && \
    sudo make install
```

## Build

To build, simply run `./build.sh $BUILD_TYPE`, where `$BUILD_TYPE`, is either "Debug", "Release", or "Both".

### Debug
Debug builds will be built with debug symbols and run unit tests + code coverage reports.
### Release
Release builds will be optimized and run Google Benchmarks
