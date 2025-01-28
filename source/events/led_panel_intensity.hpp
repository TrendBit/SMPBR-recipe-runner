/**
 * @file led_panel_intensity.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

using json = nlohmann::json;

namespace Events {
/**
 * @brief   Set intensity of LED via POST to API endpoint
 */

class LED_panel_intensity : public API_post {
private:

    /**
     * @brief   Intensity of LED, value between 0 and 1
     */
    float intensity;

public:

    /**
     * @brief Construct a new LED_intensity object based on POST request
     *
     * @param intensity Intensity of LED, value between 0 and 1
     */
    explicit LED_panel_intensity(uint channel, float intensity)
        : API_post("/control/led_intensity", "channel" + std::to_string(channel)),
        intensity(intensity){ }

    /**
     * @brief   Create body of POST request
     *
     * @return std::string  Body of POST request
     */
    virtual std::string Body() override final {
        json body;
        body["intensity"] = intensity;
        return body.dump();
    }
};
}
