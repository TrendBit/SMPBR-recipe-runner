/**
 * @file heater_turn_off.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

namespace Events {
/**
 * @brief   API call to stop heater
 */
class Heater_turn_off: public API_post {
public:
    /**
     * @brief Construct a new Heater_stop event API call
     */
    explicit Heater_turn_off() : API_post("/control/heater/turn_off") {}

    /**
     * @brief   Create body of POST request
     *
     * @return std::string  Body of POST request
     */
    virtual std::string Body() override final {
        return "";
    }
};

}
