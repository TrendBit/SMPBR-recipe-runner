/**
 * @file cuvette_pump_move.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

using json = nlohmann::json;

namespace Events {

/**
 * @brief   Use cuvette pump to move volume of liquid into or out of the cuvette
 */
class Cuvette_pump_move : public API_post {
private:

    /**
     * @brief   Volume of liquid which will be moved, in milliliters, can be negative to move liquid out of cuvette
     */
    float volume;

    /**
     * @brief   Flowrate of liquid, in milliliters per second, if zero them max speed is used
     */
    float flowrate;

public:

    /**
     * @brief Construct a new Cuvette_pump_move object based on POST request
     *
     * @param volume    Volume of liquid which will be moved, in milliliters
     * @param flowrate  Flowrate of liquid, in milliliters per second
     */
    explicit Cuvette_pump_move(float volume, float flowrate = 0)
        : API_post("/control/cuvette_pump/move"),
        volume(volume),
        flowrate(flowrate) {}

    /**
     * @brief   Execute POST request to move volume of liquid into or out of the cuvette
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
        body["volume"] = volume;
        body["flowrate"] = flowrate;
        return body.dump();
    }
};

}
