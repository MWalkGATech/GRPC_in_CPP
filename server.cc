#include <string>

#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using mathtest::MathTest;
using mathtest::MathRequest;
using mathtest::MathReply;

void Run();
class MathServiceImplementation;

int main(int argc, char** argv) {
    Run();

    return 0;
}

void Run() {
    std::string address("0.0.0.0:5000");
    MathServiceImplementation service;
    
    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

class MathServiceImplementation final : public MathTest::Servce {
    Status sendRequest(
        ServerContex* context,
        const MathRequest* request,
        MathReply* reply
    ) override {
        int a = request->a();
        int b = request->b();

        reply->set_result(a * b);

        return Status::OK;
    }
};
