/**
 * @file someip.hpp
 * @brief Brief description of the file.
 *
 * @version 1.0
 * @date 2025-11-07
 * @author Tran Dang Khoa
 * @copyright Copyright (c) 2025 K-Project
 */

#pragma once
#include <vsomeip/vsomeip.hpp>
#include <atomic>
#include <iostream>
#include <thread>

class SomeIPMgr
{
private:
    /**
     * @brief Short description of the function.
     *
     * @param param1 Description of param1.
     * @param param2 Description of param2.
     * @return Return description.
     * @retval Optional specific return value.
     */
    SomeIPMgr() {};
    SomeIPMgr(const SomeIPMgr&) = delete; 
    SomeIPMgr& operator=(const SomeIPMgr&) = delete;
    SomeIPMgr& operator=(const SomeIPMgr&&) = delete;

    std::atomic<bool> running_;
    std::thread event_thread_;
    std::shared_ptr<vsomeip::application> app;
    void on_request(const std::shared_ptr<vsomeip::message> &_request);
    void on_client_availability(vsomeip::service_t service,
                            vsomeip::instance_t instance,
                            bool is_available);
    std::shared_ptr<vsomeip::payload> create_payload(const std::string &text);
    void publish_events();
public:
    static SomeIPMgr& getInstance();

    /**
     * @brief Short description of the function.
     *
     * @param param1 None
     * @return Return status of initialize someip
     */
    bool init();
    void stop();
};
