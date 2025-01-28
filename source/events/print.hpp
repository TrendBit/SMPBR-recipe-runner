/**
 * @file print.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */


#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "event.hpp"

namespace Events {
/**
 * @brief   Event executable by planner which print message to stdout or print result of another event
 */
class Print : public Event {
private:
    /**
     * @brief   Message which will be printed
     */
    const std::string message = "";

    /**
     * @brief   Stored event which result will be printed
     */
    std::unique_ptr<Event> stored_event;

public:

    /**
     * @brief   Construct a new Print object for std::string
     *
     * @param msg   Message which will be printed
     */
    explicit Print(const std::string& msg) :
        message(msg),
        stored_event(nullptr) { }

    /**
     * @brief Construct a new Print object for const char*
     *
     * @param msg  Message which will be printed
     */
    explicit Print(const char* msg) :
        message(msg),
        stored_event(nullptr) { }

    /**
     * @brief   Construct a new Print object with embedded event
     *          If another Print event is passed like Print(Print("Hello world"))
     *              then it will be reduce to Print("Hello world") by copy constructor
     *          Enable if is used to disable this constructor for std::string and const char*
     *
     * @tparam T  Deduced type of event
     * @param event     Event of which result will be printed
     */
    template<typename T,
             typename = std::enable_if_t<
                 std::is_base_of_v<Event, std::decay_t<T>> &&
                 !std::is_same_v<std::decay_t<T>, const char*> &&
                 !std::is_same_v<std::decay_t<T>, std::string>>>
    explicit Print(T&& event) :
        message(""),
        stored_event(std::make_unique<std::decay_t<T>>(std::forward<T>(event))) { }

    // Move and copy operations
    Print(Print&& other) noexcept = default;
    Print& operator=(Print&&) noexcept = default;
    Print(const Print&) = delete;
    Print& operator=(const Print&) = delete;

    /**
     * @brief Destroy the Print object
     */
    ~Print() = default;

    /**
     * @brief   Print message or result of stored event which is executed
     *
     * @return std::string  Result of event execution or message which was printed
     */
    virtual std::string Execute() override final {
        if (stored_event) {
            std::string result = stored_event->Execute();
            std::cout << result << std::endl;
            return result;
        }
        std::cout << message << std::endl;
        return message;
    };
};
}
