#include "planner.hpp"

void Planner::Start() {
    for (auto &event : events_initialization) {
        event->Execute();
    }

    while (true) {
        for (auto &event : events_loop) {
            event->Execute();
        }
    }
}
