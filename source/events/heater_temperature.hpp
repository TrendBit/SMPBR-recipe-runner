/**
 * @file heater_temperature.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#include <iomanip>
#include <sstream>

#include "api_get.hpp"

using json = nlohmann::json;

namespace Events {
/**
 * @brief   API call to get temperature of heater plate
 */
class Heater_temperature: public API_get {
public:
    /**
     * @brief Construct a new Heater_temperature event API call
     */
    explicit Heater_temperature() : API_get("/control/heater/plate_temperature") {}

    /**
     * @brief   Execute GET request to get temperature of heater plate
     *
     * @return std::string  Formatted temperature of heater plate or error message
     */
    virtual std::string Call() override final {
        auto response = Get();

        if (not response.Valid()) {
            return response.body;
        }

        auto body = json::parse(response.body);

        std::ostringstream oss;
        oss << "Heater temperature: " << std::fixed << std::setprecision(2)
            << body["temperature"].get<float>() << "°C";
        return oss.str();

    }
};
}


