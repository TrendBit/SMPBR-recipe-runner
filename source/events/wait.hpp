/**
 * @file wait.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include <chrono>
#include <thread>
#include <string>

#include "event.hpp"

namespace Events {
/**
 * @brief   Event which wait for specified time and effectively pause planner
 */
class Wait : public Event {
private:
    /**
     * @brief   Time for which event will sleep
     */
    std::chrono::seconds wait_time;

public:
    /**
     * @brief Construct a new Wait event
     *
     * @param wait_time Time for which event pause planner in seconds
     */
    explicit Wait(int wait_time){
        this->wait_time = std::chrono::seconds(wait_time);
    }

    /**
     * @brief Destroy the Wait event
     */
    ~Wait() = default;

    /**
     * @brief   Perform sleep
     *
     * @return std::string "Wait" string
     */
    virtual std::string Execute() override final {
        std::this_thread::sleep_for(wait_time);
        return "Wait";
    }
};
}
