#include "planner.hpp"

void Planner::Start(){
    for (auto &event : events_initialization) {
        event->Execute();
    }

    while (not stop_flag) {
        for (auto &event : events_loop) {
            if (stop_flag) {
                break;
            }
            event->Execute();
        }
    }

    Clean_events();
    std::cout << "Planner finished" << std::endl;
}

uint Planner::Load_init(std::vector<Events::Type> events, Config::Components components_settings){
    uint count = 0;
    for (const auto &event_type : events) {
        try {
            std::cout << "Generating init event: " << magic_enum::enum_name(event_type) << std::endl;
            events_initialization.emplace_back(Generate_event(event_type, components_settings));
            count++;
        } catch (const std::runtime_error &e) {
            std::cerr << "Failed to generate event: " << e.what() << std::endl;
        }
    }
    return count;
}

uint Planner::Load_loop(std::vector<Events::Type> events, Config::Components components_settings){
    uint count = 0;
    for (const auto& event_type : events) {
        try {
            std::cout << "Generating loop event: " << magic_enum::enum_name(event_type) << std::endl;
            events_loop.emplace_back(Generate_event(event_type, components_settings));
            count++;
        } catch (const std::runtime_error& e) {
            std::cerr << "Failed to generate event: " << e.what() << std::endl;
        }
    }
    return count;
}

std::unique_ptr<Events::Event> Planner::Generate_event(Events::Type type, Config::Components components_settings){
    switch (type) {
        case Events::Type::heater_on:
            return std::make_unique<Events::Heater_intensity>(components_settings.heater.intensity);

        case Events::Type::illumination_on: {
            return std::make_unique<Events::LED_panel_intensity>(std::array<float,4>{
                components_settings.led_panel_channels[0],
                components_settings.led_panel_channels[1],
                components_settings.led_panel_channels[2],
                components_settings.led_panel_channels[3]
            });
        }
        case Events::Type::mix:
            return std::make_unique<Events::Mixer_stir>(
                components_settings.mixer.rpm,
                components_settings.mixer.length);

        case Events::Type::air:
            return std::make_unique<Events::Aerator_move>(
                components_settings.aerator.volume);

        case Events::Type::pump:
            return std::make_unique<Events::Cuvette_pump_move>(
                components_settings.cuvette_pump.volume);

        case Events::Type::wait:
            return std::make_unique<Events::Wait>(components_settings.cycle_length);

        default:
            throw std::runtime_error("Unknown event type");
    }
}

void Planner::Clean_events(){
    events_initialization.clear();
    events_loop.clear();
    Events::LED_panel_intensity({0,0,0,0}).Execute();
    Events::Heater_turn_off().Execute();
    Events::Cuvette_pump_stop().Execute();
    Events::Aerator_stop().Execute();
    Events::Mixer_stop().Execute();
}

void Planner::Stop(){
    stop_flag = true;
    Events::Wait::Stop();
}
