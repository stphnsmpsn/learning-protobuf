//
// Created by stev on 2020-09-16.
//

#ifndef PROTOBEAST_API_SUBSCRIBE_SUBSCRIBE_HANDLER_HPP_
#define PROTOBEAST_API_SUBSCRIBE_SUBSCRIBE_HANDLER_HPP_

#include <served/served.hpp>
#include <memory>

class SubscribeHandler {

  public:

    static void RegisterHandler(served::multiplexer &mux);

};

#endif //PROTOBEAST_API_SUBSCRIBE_SUBSCRIBE_HANDLER_HPP_
