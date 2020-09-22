/**
* @author Steve Sampson (mail@stephensampson.dev)
* @date 2020-09-17
* @brief This file contains dummy tests
*/

#include <benchmark/benchmark.h>
#include "api/subscribe/subscribe.pb.h"
#include "google/protobuf/util/json_util.h"
#include <unistd.h>

#define SUBS_JSON "{\"subscriptions\":[{\"name\":\"neton\",\"interval\":10},{\"name\":\"wifiinfo\",\"interval\":10}]}"
static std::string to_json(const google::protobuf::Message &message);
static google::protobuf::util::Status from_json(const std::string &json_string, api::Subscriptions &s);
static api::Subscriptions subsMessage;
static std::string subsJson;

static void BM_DeserializeJsonToProtobufClass(benchmark::State& state) {
    from_json(SUBS_JSON, subsMessage);
    usleep(1000000);
}

static void BM_SerializeProtobufClassToJson(benchmark::State& state) {
    subsJson = to_json(subsMessage);
}
// Register the function as a benchmark
BENCHMARK(BM_DeserializeJsonToProtobufClass);
BENCHMARK(BM_SerializeProtobufClassToJson);

BENCHMARK_MAIN();

// REGION InternalHelperFunctions

static std::string to_json(const google::protobuf::Message &message){
    std::string output;
    google::protobuf::util::JsonOptions stOpt;
    stOpt.always_print_enums_as_ints = true;
    stOpt.always_print_primitive_fields = true;
    stOpt.preserve_proto_field_names = true;
    google::protobuf::util::MessageToJsonString(message, &output, stOpt);
    return output;
}

static google::protobuf::util::Status from_json(const std::string &json_string, api::Subscriptions &s){
    google::protobuf::util::JsonParseOptions options2;
    return google::protobuf::util::JsonStringToMessage(json_string, &s, options2);
}

// ENDREGION