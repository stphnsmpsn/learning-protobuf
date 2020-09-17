//
// Created by stev on 2020-09-16.
//

#ifndef learningprotobuf_API_SUBSCRIBE_SUBSCRIBE_HANDLER_HPP_
#define learningprotobuf_API_SUBSCRIBE_SUBSCRIBE_HANDLER_HPP_

#include <served/served.hpp>
#include <memory>

class SubscribeHandler {

  public:

    static void RegisterHandler(served::multiplexer &mux);

};

#endif //learningprotobuf_API_SUBSCRIBE_SUBSCRIBE_HANDLER_HPP_
