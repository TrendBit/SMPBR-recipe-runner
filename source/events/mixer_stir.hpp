/**
 * @file mixer_stir.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include "api_post.hpp"

using json = nlohmann::json;

namespace Events {

/**
 * @brief   Start mixer inside of bottle
 */

class Mixer_stir : public API_post {
private:

    /**
     * @brief   Speed of mixer in rpm
     */
    float rpm;

    /**
     * @brief   Time for which mixer will be active in seconds
     */
    float time;

public:

    /**
     * @brief Construct a new Mixer_stir object based on POST request
     *
     * @param rpm   Speed of mixer in rpm
     * @param time  Time for which mixer will be active in seconds
     */
    explicit Mixer_stir(float rpm, float time)
        : API_post("/control/mixer/stir"),
        rpm(rpm),
        time(time) {}

    /**
     * @brief   Execute POST request to start mixer
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
        body["rpm"] = rpm;
        body["time"] = time;
        return body.dump();
    }
};

}
