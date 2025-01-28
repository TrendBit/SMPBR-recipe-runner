/**
 * @file bottle_temperature.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include <iomanip>
#include <sstream>

#include "api_get.hpp"

using json = nlohmann::json;

namespace Events {
/**
 * @brief   API call to get temperature of bottle
 */
class Bottle_temperature: public API_get {
public:
    /**
     * @brief Construct a new Bottle_temperature event
     */
    explicit Bottle_temperature() : API_get("/sensor/bottle/temperature") {}

    /**
     * @brief   Execute GET request to get temperature of bottle
     *
     * @return std::string  Formatted temperature of bottle or error message
     */
    virtual std::string Call() override final {
        auto response = Get();

        if (not response.Valid()) {
            return response.body;
        }

        auto body = json::parse(response.body);

        std::ostringstream oss;
        oss << "Bottle temperature: " << std::fixed << std::setprecision(2)
            << body["temperature"].get<float>() << "°C";
        return oss.str();

    }
};
}


