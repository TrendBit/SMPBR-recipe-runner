#include "config.hpp"

Config::Config(const std::string& path){
    auto yaml = YAML::LoadFile(path);

    api_url = yaml["api_server"]["url"].as<std::string>();

    experiment = Load_experiment(yaml["experiment"]);

    components = Load_components(yaml);
}

Config::Experiment Config::Load_experiment(const YAML::Node& yaml) {
    Experiment experiment;

    // Parse initialization process
    for (const auto& event : yaml["init_process"]) {
        auto event_name = event.as<std::string>();
        auto event_type = magic_enum::enum_cast<Events::Type>(event_name);
        if (event_type.has_value()) {
            experiment.init_events.push_back(event_type.value());
            std::cout << "Added event to init: " << event_name << std::endl;
        } else {
            std::cout << "Unknown event type: " << event_name << std::endl;
        }
    }

        // Parse loop process
    for (const auto& event : yaml["loop_process"]) {
        auto event_name = event.as<std::string>();
        auto event_type = magic_enum::enum_cast<Events::Type>(event_name);
        if (event_type.has_value()) {
            experiment.loop_events.push_back(event_type.value());
            std::cout << "Added event to loop: " << event_name << std::endl;
        } else {
            std::cout << "Unknown event type: " << event_name << std::endl;
        }
    }

    return experiment;
}

Config::Components Config::Load_components(const YAML::Node yaml){
    Components components;

    if(yaml["experiment"]["cycle_length"]){
        components.cycle_length = yaml["experiment"]["cycle_length"].as<float>();
    }

    if (yaml["illumination"]) {
        if(yaml["illumination"]["channel_0"]) {
            components.led_panel_channels[0] = yaml["illumination"]["channel_0"].as<float>();
        }
        if(yaml["illumination"]["channel_1"]) {
            components.led_panel_channels[1] = yaml["illumination"]["channel_1"].as<float>();
        }
        if(yaml["illumination"]["channel_2"]) {
            components.led_panel_channels[2] = yaml["illumination"]["channel_2"].as<float>();
        }
        if(yaml["illumination"]["channel_3"]) {
            components.led_panel_channels[3] = yaml["illumination"]["channel_3"].as<float>();
        }
    }

    if (yaml["heater"]["intensity"]) {
        components.heater.intensity = yaml["heater"]["intensity"].as<float>();
    }
    if (yaml["heater"]["temperature"]) {
        components.heater.intensity = yaml["heater"]["temperature"].as<float>();
    }

    if (yaml["pump"]["volume"]) {
        components.cuvette_pump.volume = yaml["pump"]["volume"].as<float>();
    }
    if (yaml["pump"]["flowrate"]) {
        components.cuvette_pump.flowrate = yaml["pump"]["flowrate"].as<float>();
    }

    if (yaml["aerator"]["volume"]) {
        components.aerator.volume = yaml["aerator"]["volume"].as<float>();
    }
    if (yaml["aerator"]["flowrate"]) {
        components.aerator.flowrate = yaml["aerator"]["flowrate"].as<float>();
    }

    if (yaml["mixer"]["rpm"]) {
        components.mixer.rpm = yaml["mixer"]["rpm"].as<float>();
    }
    if (yaml["mixer"]["length"]) {
        components.mixer.length = yaml["mixer"]["length"].as<float>();
    }

    return components;
}
