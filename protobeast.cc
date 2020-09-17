
#include <served/served.hpp>
#include "api/subscribe/subscribe_handler.hpp"

constexpr auto NUM_THREADS = 10;
constexpr auto LISTEN_ADDRESS = "0.0.0.0";
constexpr auto PORT = "8080";

int main(int argc, char const* argv[]) {
    served::multiplexer mux;
    SubscribeHandler::RegisterHandler(mux);
    served::net::server server(LISTEN_ADDRESS, PORT, mux);
    server.run(NUM_THREADS);
    return (EXIT_SUCCESS);
}

