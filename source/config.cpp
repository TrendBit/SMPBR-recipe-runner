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
        try {
            auto event_config = Parse_event(event);
            experiment.init_events.push_back(event_config);
            Print_event(event_config);
        } catch (const std::exception& e) {
            std::cout << "Error parsing event: " << e.what() << std::endl;
        }
    }

    // Parse loop process
    for (const auto& event : yaml["loop_process"]) {
        try {
            auto event_config = Parse_event(event);
            experiment.loop_events.push_back(event_config);
            Print_event(event_config);
        } catch (const std::exception& e) {
            std::cout << "Error parsing event: " << e.what() << std::endl;
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
        components.heater.temperature = yaml["heater"]["temperature"].as<float>();
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

Events::Config Config::Parse_event(const YAML::Node& event_node) {
    Events::Config config;
    std::string event_str = event_node.as<std::string>();

    // Find first space to separate event name
    size_t pos = event_str.find_first_of(' ');
    std::string event_name = (pos == std::string::npos) ?
        event_str : event_str.substr(0, pos);

    // Parse event type
    auto event_type = magic_enum::enum_cast<Events::Type>(event_name);
    if (!event_type.has_value()) {
        throw std::runtime_error("Unknown event type: " + event_name);
    }
    config.type = event_type.value();

    // Parse parameters if any exist
    size_t param_index = 0;
    while (pos != std::string::npos && param_index < 4) {
        size_t next_pos = event_str.find_first_of(' ', pos + 1);
        std::string param = event_str.substr(pos + 1,
            next_pos == std::string::npos ? next_pos : next_pos - pos - 1);

        try {
            config.params[param_index++] = std::stof(param);
        } catch (...) {
            break;
        }
        pos = next_pos;
    }

    return config;
}

// Update the print code in Load_experiment to handle std::optional
void Config::Print_event(const Events::Config& event_config) {
    std::cout << "Added event: " << magic_enum::enum_name(event_config.type);
    for (const auto& param : event_config.params) {
        if (param.has_value()) {
            std::cout << " " << param.value();
        }
    }
    std::cout << std::endl;
}
