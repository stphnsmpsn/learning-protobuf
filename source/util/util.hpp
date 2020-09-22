//
// Created by stev on 2020-09-17.
//

#ifndef LEARNINGPROTOBUF_UTIL_UTIL_HPP_
#define LEARNINGPROTOBUF_UTIL_UTIL_HPP_

#include "google/protobuf/util/json_util.h"

class Util {

  private:


  public:
    template<typename Base, typename T> static inline bool instanceof(const T*) {
        return std::is_base_of<Base, T>::value;
    }
    static std::string to_json(const google::protobuf::Message &message);
    static google::protobuf::util::Status from_json(const std::string &json_string, google::protobuf::Message &m);

};

#endif //LEARNINGPROTOBUF_UTIL_UTIL_HPP_
