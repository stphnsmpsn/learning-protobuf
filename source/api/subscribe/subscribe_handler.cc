//
// Created by stev on 2020-09-16.
//

#include "api/subscribe/subscribe_handler.hpp"
#include "api/subscribe/subscribe.pb.h"
#include "google/protobuf/util/json_util.h"
#include "util/util.hpp"

static std::string response_ok_json();
//static std::string to_json(const google::protobuf::Message &m);
//static google::protobuf::util::Status from_json(const std::string &json_string, api::Subscriptions &s);

void SubscribeHandler::RegisterHandler(served::multiplexer &mux) {

    mux.handle("/api/subscribe")
        .post([](served::response & res, const served::request & req) {
            google::protobuf::util::Status status;

            if (req.header("Content-Type") != "application/json") {
                served::response::stock_reply(400, res);
                return;
            }

            api::Subscriptions subsMessage;
            status = Util::from_json(req.body(), subsMessage);
            google::protobuf::RepeatedPtrField<api::Subscription> subs = subsMessage.subscriptions();

            if(!status.ok()){
                served::response::stock_reply(400, res);
                return;
            } else {
                for (auto it = subs.begin(); it != subs.end(); ++it) {
                    std::cout << "Received sub for: " << it->name() << std::endl;
                }
            }
            res << response_ok_json();
        });

}

//static std::string to_json(const google::protobuf::Message &message){
//    std::string output;
//    google::protobuf::util::JsonOptions stOpt;
//    stOpt.always_print_enums_as_ints = true;
//    stOpt.always_print_primitive_fields = true;
//    stOpt.preserve_proto_field_names = true;
//    google::protobuf::util::MessageToJsonString(message, &output, stOpt);
//    return output;
//}
//
//static google::protobuf::util::Status from_json(const std::string &json_string, api::Subscriptions &s){
//    google::protobuf::util::JsonParseOptions options2;
//    return google::protobuf::util::JsonStringToMessage(json_string, &s, options2);
//}

static std::string response_ok_json(){
    return "{\"status\":\"OK\"}";
}