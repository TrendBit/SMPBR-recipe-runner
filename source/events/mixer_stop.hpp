/**
 * @file mixer_stop.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

namespace Events {
/**
 * @brief   API call to stop mixer
 */
class Mixer_stop: public API_post {
public:
    /**
     * @brief Construct a new Mixer_stop event API call
     */
    explicit Mixer_stop() : API_post("/control/mixer/stop") {}

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
