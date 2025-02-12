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

uint Planner::Load_init(std::vector<Events::Config> events, Config::Components components_settings){
    uint count = 0;
    for (const auto &event_config : events) {
        try {
            events_initialization.emplace_back(Generate_event(event_config, components_settings));
            count++;
        } catch (const std::runtime_error &e) {
            std::cerr << "Failed to generate event: " << e.what() << std::endl;
        }
    }
    return count;
}

uint Planner::Load_loop(std::vector<Events::Config> events, Config::Components components_settings){
    uint count = 0;
    for (const auto& event_config : events) {
        try {
            events_loop.emplace_back(Generate_event(event_config, components_settings));
            count++;
        } catch (const std::runtime_error& e) {
            std::cerr << "Failed to generate event: " << e.what() << std::endl;
        }
    }
    return count;
}

std::unique_ptr<Events::Event> Planner::Generate_event(const Events::Config& config, Config::Components components_settings){
    switch (config.type) {
        case Events::Type::heater_on:
            return std::make_unique<Events::Heater_target>(
                config.params[0].value_or(components_settings.heater.temperature));

        case Events::Type::illumination_on: {
            std::array<float,4> intensities = {
                config.params[0].value_or(components_settings.led_panel_channels[0]),
                config.params[1].value_or(components_settings.led_panel_channels[1]),
                config.params[2].value_or(components_settings.led_panel_channels[2]),
                config.params[3].value_or(components_settings.led_panel_channels[3])
            };
            return std::make_unique<Events::LED_panel_intensity>(intensities);
        }

        case Events::Type::mix:
            return std::make_unique<Events::Mixer_stir>(
                config.params[0].value_or(components_settings.mixer.rpm),
                config.params[1].value_or(components_settings.mixer.length));

        case Events::Type::air:
            return std::make_unique<Events::Aerator_move>(
                config.params[0].value_or(components_settings.aerator.volume));

        case Events::Type::pump:
            return std::make_unique<Events::Cuvette_pump_move>(
                config.params[0].value_or(components_settings.cuvette_pump.volume));

        case Events::Type::wait:
            return std::make_unique<Events::Wait>(
                config.params[0].value_or(components_settings.cycle_length));

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
