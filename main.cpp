#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>
#include <thread>

#define SAMPLE_SERVICE_ID   0x1234
#define SAMPLE_INSTANCE_ID  0x5678
#define SAMPLE_METHOD_ID    0x0421   // request/response method ID

std::shared_ptr<vsomeip::application> app;

// Callback when detect arrive message (client call request)
void on_message(const std::shared_ptr<vsomeip::message> &_request) {
    auto payload = _request->get_payload();
    std::string recv_str(reinterpret_cast<const char *>(payload->get_data()), payload->get_length());

    std::cout << "[Server] Received request: " << recv_str << std::endl;

    // create a response message
    auto response = vsomeip::runtime::get()->create_response(_request);
    std::string reply = "Hello from server!";
    auto resp_payload = vsomeip::runtime::get()->create_payload();
    resp_payload->set_data(reinterpret_cast<const vsomeip::byte_t *>(reply.data()), reply.size());
    response->set_payload(resp_payload);

    // send response to client
    app->send(response);
    std::cout << "[Server] Sent response.\n";
}

int main() {
    std::cout << "[Server] Starting...\n";

    app = vsomeip::runtime::get()->create_application("ServerApp");

    if (!app->init()) {
        std::cerr << "[Server] init() failed!\n";
        return -1;
    }

    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);

    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    std::cout << "[Server] Offering service 0x" << std::hex << SAMPLE_SERVICE_ID
              << " / instance 0x" << SAMPLE_INSTANCE_ID << std::dec << std::endl;

    app->start();
    return 0;
}