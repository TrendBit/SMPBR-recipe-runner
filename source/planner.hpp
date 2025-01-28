/**
 * @file planner.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include <vector>
#include <memory>

#include "events/event.hpp"

/**
 * @brief   Class responsible for planning and executing events
 *
 *          Events can be added to initialization and will be only executed once at start.
 *          Or can be added to loop and will be executed until program is stopped.
 */
class Planner{
private:
    /**
     * @brief   Events which are executed only once
     */
    std::vector<std::unique_ptr<Events::Event>> events_initialization;

    /**
     * @brief   Events which are executed in loop
     */
    std::vector<std::unique_ptr<Events::Event>> events_loop;

public:
    /**
     * @brief Construct a new Planner
     */
    Planner() = default;

    /**
     * @brief Destroy the Planner
     */
    ~Planner() = default;

    /**
     * @brief   Start execution planned events (initialization and loop)
     */
    void Start();

    /**
     * @brief   Add event to loop
     *
     * @tparam T        Type of event, deduced from passed argument
     * @param event     Event which will be added to loop
     * @return int      Number of events in loop
     */
    template<typename T>
    int Add(T&& event) {
        static_assert(std::is_base_of<Events::Event, std::remove_reference_t<T>>::value,
                     "T must derive from Event");
        events_loop.push_back(
            std::make_unique<std::remove_reference_t<T>>(std::forward<T>(event))
        );
        return events_loop.size();
    }

};
