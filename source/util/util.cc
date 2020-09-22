//
// Created by stev on 2020-09-17.
//

#include "util/util.hpp"

//template<typename Base, typename T> bool Util::instanceof(const T*) {
//    return std::is_base_of<Base, T>::value;
//}

google::protobuf::util::Status Util::from_json(const std::string &json_string, google::protobuf::Message &m) {
    google::protobuf::util::JsonParseOptions options2;
    return google::protobuf::util::JsonStringToMessage(json_string, &m, options2);
}

std::string Util::to_json(const google::protobuf::Message &message){
    std::string output;
    google::protobuf::util::JsonOptions stOpt;
    stOpt.always_print_enums_as_ints = true;
    stOpt.always_print_primitive_fields = true;
    stOpt.preserve_proto_field_names = true;
    google::protobuf::util::MessageToJsonString(message, &output, stOpt);
    return output;
}