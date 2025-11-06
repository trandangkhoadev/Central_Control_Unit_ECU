#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>
#include <thread>

#define SAMPLE_SERVICE_ID   0x1234
#define SAMPLE_INSTANCE_ID  0x5678
#define SAMPLE_METHOD_ID    0x0421

std::shared_ptr<vsomeip::application> app;

// Callback when receive the response from server
void on_message(const std::shared_ptr<vsomeip::message> &_response) {
    auto payload = _response->get_payload();
    std::string recv_str(reinterpret_cast<const char *>(payload->get_data()), payload->get_length());
    std::cout << "[Client] Received response: " << recv_str << std::endl;
}

// Thread to send the request
void send_request() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); //waiting for routing stable

    auto req = vsomeip::runtime::get()->create_request();
    req->set_service(SAMPLE_SERVICE_ID);
    req->set_instance(SAMPLE_INSTANCE_ID);
    req->set_method(SAMPLE_METHOD_ID);

    std::string msg = "Hello from client!";
    auto pl = vsomeip::runtime::get()->create_payload();
    pl->set_data(reinterpret_cast<const vsomeip::byte_t*>(msg.data()), msg.size());
    req->set_payload(pl);

    std::cout << "[Client] Sending request...\n";
    app->send(req);
}

int main() {
    std::cout << "[Client] Starting...\n";

    app = vsomeip::runtime::get()->create_application("ClientApp");

    if (!app->init()) {
        std::cerr << "[Client] init() failed!\n";
        return -1;
    }

    // register handle from server's response
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);

    // request service from server
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

    std::thread sender(send_request);

    app->start();
    sender.join();
    return 0;
}