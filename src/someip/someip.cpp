#include "someip/someip.hpp"


#define SAMPLE_SERVICE_ID       0x1234
#define SAMPLE_INSTANCE_ID      0x5678
#define SAMPLE_METHOD_ID        0x0421
#define SAMPLE_EVENT_ID         0x8001   // ID for event
#define SAMPLE_EVENTGROUP_ID    0x0001


// Handle client request
void SomeIPMgr::on_request(const std::shared_ptr<vsomeip::message> &_request) {
    auto payload = _request->get_payload();
    std::string recv_str(reinterpret_cast<const char *>(payload->get_data()), payload->get_length());
    std::cout << "[Server] Received request: " << recv_str << std::endl;

    // Build response
    std::string reply = "Server received: " + recv_str;
    auto response = vsomeip::runtime::get()->create_response(_request);
    response->set_payload(create_payload(reply));
    app->send(response);
    std::cout << "[Server] Sent response.\n";
}

// Create payload helper
std::shared_ptr<vsomeip::payload> SomeIPMgr::create_payload(const std::string &text) {
    auto p = vsomeip::runtime::get()->create_payload();
    p->set_data(reinterpret_cast<const vsomeip::byte_t *>(text.data()), text.size());
    return p;
}

// Periodically publish events
void SomeIPMgr::publish_events() {
    int counter = 0;
    while (running_) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::string msg = "Event #" + std::to_string(++counter);
        app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, create_payload(msg));
        std::cout << "[Server] Published event: " << msg << std::endl;
    }
}

// Handle client availability (connect/disconnect)
void SomeIPMgr::on_client_availability(vsomeip::service_t service,
                            vsomeip::instance_t instance,
                            bool is_available) {
    std::cout << "[Server] Client " << (is_available ? "connected" : "disconnected")
                << " to service 0x" << std::hex << service << " / 0x" << instance << std::dec << std::endl;
}


SomeIPMgr& SomeIPMgr::getInstance()
{
    static SomeIPMgr instance; 
    return instance;
}

bool SomeIPMgr::init()
{
    std::cout << "[Server] Starting...\n";
    app = vsomeip::runtime::get()->create_application("ServerApp");

    if (!app->init()) {
        std::cerr << "[Server] init() failed!\n";
        return -1;
    }

    // Register request handler
    app->register_message_handler(SAMPLE_SERVICE_ID,
                                    SAMPLE_INSTANCE_ID,
                                    SAMPLE_METHOD_ID,
                                    std::bind(&SomeIPMgr::on_request, this, std::placeholders::_1));

    // Register availability handler
    app->register_availability_handler(SAMPLE_SERVICE_ID,
                                        SAMPLE_INSTANCE_ID,
                                        std::bind(&SomeIPMgr::on_client_availability, this,
                                                    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

    app->offer_event(
        SAMPLE_SERVICE_ID,
        SAMPLE_INSTANCE_ID,
        SAMPLE_EVENT_ID,
        { SAMPLE_EVENTGROUP_ID },
        vsomeip_v3::event_type_e::ET_EVENT,              // _type
        std::chrono::milliseconds(0),                    // _cycle = 0ms (no auto-cycle)
        false,                                           // _change_resets_cycle
        false,                                           // _update_on_change
        vsomeip_v3::epsilon_change_func_t(),             // _epsilon_change_func (default-constructed)
        vsomeip_v3::reliability_type_e::RT_RELIABLE      // _reliability (TCP)
        );

    app->start();

    std::this_thread::sleep_for(std::chrono::seconds(1)); // đợi routing ổn định
    app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID,
                create_payload("Initial event"));
}

void SomeIPMgr::stop() 
{
    running_ = false;
    if (event_thread_.joinable()) event_thread_.join();
    app->stop_offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->stop();
}