/**
 * @file aerator_move.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

using json = nlohmann::json;

namespace Events {

/**
 * @brief   Use aerator to move volume of air into the bottle
 */
class Aerator_move : public API_post {
private:

    /**
     * @brief   Volume of air which will be moved into bottle, in milliliters, can be only positive
     */
    float volume;

    /**
     * @brief   Flowrate of air, in milliliters per minite, if zero them max speed is used
     */
    float flowrate;

public:

    /**
     * @brief Construct a new Aerator_move object based on POST request
     *
     * @param volume    Volume of air which will be moved, in milliliters
     * @param flowrate  Flowrate of air, in milliliters per minute
     */
    explicit Aerator_move(float volume, float flowrate = 0)
        : API_post("/control/aerator/move"),
        volume(volume),
        flowrate(flowrate) {}

    /**
     * @brief   Execute POST request to move volume of air into the bottle
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

