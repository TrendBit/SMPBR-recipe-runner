/**
 * @file aerator_stop.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

namespace Events {
/**
 * @brief   API call to stop aerator
 */
class Aerator_stop: public API_post {
public:
    /**
     * @brief Construct a new Aerator_stop event API call
     */
    explicit Aerator_stop() : API_post("/control/aerator/stop") {}

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
