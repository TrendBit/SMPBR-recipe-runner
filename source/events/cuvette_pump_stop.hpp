/**
 * @file cuvette_pump_stop.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

namespace Events {
/**
 * @brief   API call to stop cuvette pump
 */
class Cuvette_pump_stop: public API_post {
public:
    /**
     * @brief Construct a new Cuvette_pump_stop event API call
     */
    explicit Cuvette_pump_stop() : API_post("/control/cuvette_pump/stop") {}

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
