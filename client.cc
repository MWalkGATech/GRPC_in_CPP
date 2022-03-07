#include <string>

#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using mathtest::MathTest;
using mathtest::MathRequest;
using mathtest::MathReply;

void Run();

int main(int argc, char** argv) {
    Run();

    return 0;
}

void Run() {
    std::string address("0.0.0.0:5000");
    MathTestClient client(
        grpc::CreateChannel(
            address,
            grpc::InsecureChannelCredentials()
        )
    );

    int response;

    int a = 5; 
    int b = 10;

    response = client.sendRequest(a, b);

    std::cout << "Answer received: " << a << " * " << b << " = " << response << std::endl;
}
