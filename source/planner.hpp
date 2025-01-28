/**
 * @file planner.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#pragma once

#include <vector>
#include <memory>

#include "config.hpp"
#include "events/event.hpp"
#include "events/types.hpp"

#include "events/wait.hpp"
#include "events/print.hpp"
#include "events/bottle_temperature.hpp"
#include "events/heater_intensity.hpp"
#include "events/heater_temperature.hpp"
#include "events/heater_turn_off.hpp"
#include "events/led_panel_intensity.hpp"
#include "events/cuvette_pump_move.hpp"
#include "events/mixer_stir.hpp"
#include "events/aerator_move.hpp"


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

    /**
     * @brief   Signal handler can set this exit processing loop
     */
    std::atomic<bool> stop_flag{false};

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

    uint Load_init(std::vector<Events::Type> events, Config::Components components_settings);

    uint Load_loop(std::vector<Events::Type> events, Config::Components components_settings);

    /**
     * @brief   Add event to loop
     *
     * @tparam T        Type of event, deduced from passed argument
     * @param event     Event which will be added to loop
     * @return int      Number of events in loop
     */
    template<typename T>
    int Add_loop(T&& event) {
        static_assert(std::is_base_of<Events::Event, std::remove_reference_t<T>>::value,
                     "T must derive from Event");
        events_loop.push_back(
            std::make_unique<std::remove_reference_t<T>>(std::forward<T>(event))
        );
        return events_loop.size();
    }

    /**
     * @brief   Add event to initialization
     *
     * @tparam T        Type of event, deduced from passed argument
     * @param event     Event which will be added to initialization
     * @return int      Number of events in initialization
     */
    template<typename T>
    int Add_initialization(T&& event) {
        static_assert(std::is_base_of<Events::Event, std::remove_reference_t<T>>::value,
                     "T must derive from Event");
        events_initialization.push_back(
            std::make_unique<std::remove_reference_t<T>>(std::forward<T>(event))
        );
        return events_initialization.size();
    }

    void Stop();

private:

    std::unique_ptr<Events::Event> Generate_event(Events::Type type, Config::Components components_settings);

    void Clean_events();
};
