/**
 * @file api_call.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include "event.hpp"
#include "tools/httplib.h"
#include <nlohmann/json.hpp>

namespace Events{
/**
 * @brief   Generic request to API endpoint, from which other API calls are derived
 */
class API_call: public Event {
public:
    /**
     * @brief   Structure simplifying return of API call
     */
    struct Result {
        /**
         * @brief   Status of response, 200 is OK
         */
        int status;

        /**
         * @brief   Body of response, can be error message or data (status == 200)
         */
        std::string body;

        /**
         * @brief   Check if response is valid, status == 200
         *
         * @return true     If response is valid
         * @return false    If response is not valid
         */
        bool Valid() {
            return status == 200;
        }
    };

protected:
    /**
     * @brief   Client for HTTP requests shared between all API calls
     */
    static inline httplib::Client client{""};

    /**
     * @brief   Endpoint to which request is sent
     */
    std::string endpoint;

public:
    /**
     * @brief Construct a new api call object
     *
     * @param endpoint  Endpoint of API
     */
    explicit API_call(std::string endpoint) : endpoint(endpoint) {}

    /**
     * @brief   Set client for all API calls (API server IP address and port)
     *
     * @param host_url  URL of host, where API is running, example: "192.168.1.241:8089"
     */
    static void Set_client(const std::string &host_url) {
        client = httplib::Client(host_url);
        client.set_default_headers({{"Content-Type", "application/json"}});
    }

    /**
     * @brief   Execute API call, call Call() method, derived from Event
     *
     * @return std::string  Body of response or error message
     */
    virtual std::string Execute() override final {
        return Call();
    }

protected:
    /**
     * @brief   Method for sending request to API endpoint, implemented in derived classes
     *
     * @return std::string
     */
    virtual std::string Call() = 0;

    /**
     * @brief   Method for creating body of POST request, implemented in derived classes
     *          Reduce complexity of HTTP response
     *
     * @param received_result   Result of HTTP request from httplib
     * @return Result           Simplified result of HTTP request
     */
    static Result Receive(httplib::Result received_result) {
        Result result;
        result.status = received_result->status;
        if (received_result) {
            if (received_result->status == 200) {
                result.body = received_result->body;
            } else {
                result.body = "Error: " + std::to_string(received_result->status);
            }
        } else {
            result.body = "Error: " + httplib::to_string(received_result.error());
        }
        return result;
    }

};
}
