/**
 * @file api_post.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include <optional>

#include "api_call.hpp"
#include "tools/httplib.h"

using json = nlohmann::json;

namespace Events {
/**
 * @brief   Class for POST request to API endpoint
 */
class API_post: public API_call {
private:
    /**
     * @brief   Body of POST request, fixed variant can be dynamicly generated
     */
    std::optional<std::string> body = std::nullopt;

protected:
    /**
     * @brief Construct a new api post object, dynamicly generated body of POST request
     *
     * @param endpoint  Endpoint of API
     */
    explicit API_post(std::string endpoint) : API_call(endpoint) {}

    /**
     * @brief Construct a new api post object, dynamicly generated body of POST request
     *
     * @param endpoint  Endpoint of API
     */
    explicit API_post(std::string endpoint, std::string instance) : API_call(endpoint, instance) {}

    /**
     * @brief   Send POST request to API endpoint
     *
     * @return API_call::Result Result of POST request
     */
    API_call::Result Post(){
        return Receive(client.Post(endpoint+instance, Body(), "application/json"));
    }

    /**
     * @brief   Execute POST request to API endpoint
     *
     * @return std::string  Body of response or error message
     */
    virtual std::string Call() override {
        return Post().body;
    }

    /**
     * @brief   Create body of POST request, can be overriden in derived classes to generate dynamic body
     *
     * @return std::string  Body of POST request, fixed variant
     */
    virtual std::string Body() {
        if (body.has_value()) {
            return body.value();
        } else {
            return "";
        }
    }

};
}
