#################################################################################
#    _____ _______ ________      __     By: Steve Sampson
#   / ____|__   __|  ____\ \    / /     Email: mail@stephensampson.dev
#  | (___    | |  | |__   \ \  / /      Created: 2020-09-16
#   \___ \   | |  |  __|   \ \/ /       Modified: 2020-09-16
#   ____) |  | |  | |____   \  /        Description: TODO:
#  |_____/   |_|  |______|   \/
#################################################################################

cmake_minimum_required(VERSION 3.16)
PROJECT(learningprotobuf VERSION 0.1.0)
STRING(TIMESTAMP COMMENT_DATE "%Y-%m-%d")
STRING(TIMESTAMP TODAY "%Y%m%d%H%M%S")
CONFIGURE_FILE(config/version.h.in version.h)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/config")
INCLUDE(code-coverage)
SET(CMAKE_CXX_STANDARD 17)

######################################################################################
#              Configure Stage: Download Gtest and add to our project
######################################################################################
# Download and unpack googletest at configure time
CONFIGURE_FILE(config/google-test.in Google_test/googletest-download/CMakeLists.txt)
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Google_test/googletest-download )
if(result)
    MESSAGE(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Google_test/googletest-download )
if(result)
    MESSAGE(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
ADD_SUBDIRECTORY(${CMAKE_CURRENT_BINARY_DIR}/Google_test/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/Google_test/googletest-build
    EXCLUDE_FROM_ALL)

######################################################################################
#          Configure Stage: Download Google Benchmark and add to our project
######################################################################################
# Download and unpack googlebench at configure time
CONFIGURE_FILE(config/google-bench.in Google_bench/googlebench-download/CMakeLists.txt)
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Google_bench/googlebench-download )
if(result)
    MESSAGE(FATAL_ERROR "CMake step for googlebench failed: ${result}")
endif()
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Google_bench/googlebench-download )
if(result)
    MESSAGE(FATAL_ERROR "Build step for googlebench failed: ${result}")
endif()

# Add googlebench directly to our build.
ADD_SUBDIRECTORY(${CMAKE_CURRENT_BINARY_DIR}/Google_bench/googlebench-src
    ${CMAKE_CURRENT_BINARY_DIR}/Google_bench/googlebench-build
    EXCLUDE_FROM_ALL)

######################################################################################
#                    Configure Stage: Compile Protocol Buffers
######################################################################################

EXECUTE_PROCESS(COMMAND protoc
    -I=${CMAKE_SOURCE_DIR}/api/subscribe
    --cpp_out=${CMAKE_SOURCE_DIR}/api/subscribe
    ${CMAKE_SOURCE_DIR}/api/subscribe/subscribe.proto
)

######################################################################################

INCLUDE_DIRECTORIES(
    /usr/local/include
    ./
)

SET(COMMON_SRCS
    api/subscribe/subscribe_handler.cc
    api/subscribe/subscribe.pb.cc
)

SET(PROD_ONLY_SRCS
    learningprotobuf.cc
)

SET(TEST_ONLY_SRCS
    tests/dummy_test.cc
)

SET(BENCH_ONLY_SRCS
    benchmarks/dummy_benchmark.cc
)

SET(LIBS
    pthread
    served
    protobuf
)


FOREACH(L ${LIBS})
    FIND_LIBRARY(${L}_FOUND ${L})
    SET(FOUND_LIBRARIES ${FOUND_LIBRARIES} ${${L}_FOUND})
ENDFOREACH()

######################################################################################

ADD_EXECUTABLE(learningprotobuf
    ${COMMON_SRCS}
    ${PROD_ONLY_SRCS}
)

TARGET_LINK_LIBRARIES(learningprotobuf ${FOUND_LIBRARIES})
SET_TARGET_PROPERTIES(learningprotobuf PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} OUTPUT_NAME learningprotobuf)

######################################################################################

if(CMAKE_BUILD_TYPE MATCHES Debug)
    ADD_EXECUTABLE(learningprotobuf_test
        ${COMMON_SRCS}
        ${TEST_ONLY_SRCS}
    )

    TARGET_LINK_LIBRARIES(learningprotobuf_test
        gtest
        gtest_main
        ${FOUND_LIBRARIES}
    )

    append_coverage_compiler_flags()
    SET(COVERAGE_EXCLUDES "cmake-build-debug" "build" "tests" "Debug" "Release" "benchmarks")

    setup_target_for_coverage_gcovr_html(
        NAME CoverageHtml
        EXECUTABLE learningprotobuf_test -j ${PROCESSOR_COUNT}
        DEPENDENCIES learningprotobuf_test
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/"
    )

    setup_target_for_coverage_gcovr_xml(
        NAME CoverageXml
        EXECUTABLE learningprotobuf_test -j ${PROCESSOR_COUNT}
        DEPENDENCIES learningprotobuf_test
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/"
    )
    setup_target_for_coverage_lcov(
        NAME CoverageLcov
        EXECUTABLE learningprotobuf_test -j ${PROCESSOR_COUNT}
        DEPENDENCIES learningprotobuf_test
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/"
    )

    setup_target_for_coverage_sonarqube_xml(
        NAME CoverageSonarqube
        EXECUTABLE learningprotobuf_test -j ${PROCESSOR_COUNT}
        DEPENDENCIES learningprotobuf_test
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/"
    )
endif()

######################################################################################

if(CMAKE_BUILD_TYPE MATCHES Release)
    ADD_EXECUTABLE(learningprotobuf_bench
        ${COMMON_SRCS}
        ${BENCH_ONLY_SRCS}
    )

    TARGET_LINK_LIBRARIES(learningprotobuf_bench
        gtest
        gtest_main
        benchmark::benchmark
        benchmark::benchmark_main
        ${FOUND_LIBRARIES}
    )
endif()

######################################################################################