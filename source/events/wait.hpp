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
#include <condition_variable>
#include <mutex>

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

    static inline std::condition_variable cv;
    static inline std::mutex mtx;

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

    static void Stop(){
        cv.notify_all();
    }

    /**
     * @brief   Perform sleep
     *
     * @return std::string "Wait" string
     */
    virtual std::string Execute() override final {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, wait_time);
        return "Wait";
    }

};
}
