/**
 * @file heater_intensity.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include "api_post.hpp"

using json = nlohmann::json;


namespace Events {
/**
 * @brief   Set intensity of heater via POST to API endpoint
 */
class Heater_intensity: public API_post {
private:
    /**
     * @brief   Intensity of heater, value between 0 and 1
     */
    float intensity;

public:
    /**
     * @brief Construct a new Heater_intensity object based on POST request
     *
     * @param intensity Intensity of heater, value between 0 and 1
     */
    explicit Heater_intensity(float intensity) : API_post("/control/heater/intensity"), intensity(intensity) {}

    /**
     * @brief   Execute POST request to set intensity of heater
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
        body["intensity"] = intensity;
        return body.dump();
    }
};
}
