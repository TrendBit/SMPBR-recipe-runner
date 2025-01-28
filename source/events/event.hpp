/**
 * @file event.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include <string>

namespace Events {
/**
 * @brief   Base class for all events, which can be executed in planner
 */
class Event {
public:
    /**
     * @brief Construct a new Event object
     */
    Event() = default;

    /**
     * @brief Destroy the Event object
     */
    ~Event() = default;

    /**
     * @brief   Execute event, this method should be overriden in derived classes
     *
     * @return std::string  Result of event execution
     */
    virtual std::string Execute() = 0;
};
}
