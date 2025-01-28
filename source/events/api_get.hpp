/**
 * @file api_get.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include "api_call.hpp"
#include "tools/httplib.h"

namespace Events {
/**
 * @brief  Class for GET request to API endpoint
 */
class API_get: public API_call {
public:
    /**
     * @brief Construct a new Event sending GET request to API endpoint
     *
     * @param endpoint  Endpoint of API
     */
    explicit API_get(std::string endpoint) : API_call(endpoint) {}

protected:
    /**
     * @brief   Send GET request to API endpoint
     *
     * @return API_call::Result Result of GET request
     */
    API_call::Result Get(){
        return Receive(client.Get(endpoint+instance));
    }

    /**
     * @brief   Execute GET request to API endpoint
     *
     * @return std::string  Body of response or error message
     */
    virtual std::string Call() override {
        return Get().body;
    }

};
}
