cmake_minimum_required(VERSION 3.19.2)

project(MathTest C CXX)

set (CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Proto file
get_filename_component(mt_proto "./mathtest.proto" ABSOLUTE)
get_filename_component(mt_proto_path "${mt_proto}" PATH)

# Generated Sources
set(mt_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.pb.cc")
set(mt_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.pb.h")
set(mt_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.grpc.pb.cc")
set(mt_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.grpc.pb.h")
add_custom_command(
    OUTPUT "${mt_proto_srcs}" "${mt_proto_hdrs}" "${mt_grpc_srcs}" "${mt_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
         --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
         -I "${mt_proto_path}"
         --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
         "${mt_proto}"
)

# inclide generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# mt_grpc_proto
add_library(mt_grpc_proto
    ${mt_grpc_srcs}
    ${mt_grpc_hdrs}
    ${mt_proto_srcs}
    ${mt_proto_hdrs}
)
target_link_libraries(mt_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)

# Targets mathtest
foreach(_target
    client server)
    add_executable(${_target} "${_target}.cc")
    target_link_libraries(${_target}
        mt_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
    )
endforeach()