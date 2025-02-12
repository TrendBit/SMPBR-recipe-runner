/**
 * @file heater_target.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 12.02.2025
 */

#pragma once

#include "api_post.hpp"

using json = nlohmann::json;

namespace Events {
/**
 * @brief   API call to get temperature of heater plate
 */
class Heater_target: public API_post {
private:
    /**
     * @brief   Target temperature of device
     */
    float target;

public:
    /**
     * @brief Construct a new Heater_temperature event API call
     */
    explicit Heater_target(float target) : API_post("/control/heater/target_temperature"), target(target) {}

    /**
     * @brief   Execute POST request to set target temperature of bottle
     *
     * @return std::string
     */
    virtual std::string Call() override final {
        return Post().body;
    }

    /**
     * @brief   Create body of POST request
     *
     * @return std::string  Body of POST request
     */
    virtual std::string Body() override final {
        json body;
        body["temperature"] = target;
        return body.dump();
    }
};
}


