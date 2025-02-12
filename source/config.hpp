/**
 * @file config.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

#include <string>
#include <array>
#include <vector>
#include <iostream>

#include "events/types.hpp"
#include <yaml-cpp/yaml.h>
#include "tools/magic_enum.hpp"

/**
 * @brief   Class for loading configuration from yaml file
 */
class Config {
public:
    struct Components{
        float cycle_length = 60;

        std::array<float, 4> led_panel_channels = {0, 0, 0, 0};

        struct heater{
            float intensity = 0;
            float temperature = 0;
        } heater;

        struct cuvette_pump{
            float volume = 0;
            float flowrate = 0;
        } cuvette_pump;

        struct aerator{
            float volume = 0;
            float flowrate = 0;
        } aerator;

        struct mixer{
            float rpm = 0;
            float length = 0;
        } mixer;
    };

private:
    struct Experiment {
        std::vector<Events::Config> init_events;
        std::vector<Events::Config> loop_events;
    };

private:
    std::string api_url;

    Experiment experiment;

    Components components;

public:

    explicit Config(const std::string& path);

    std::string Server_URL() const { return api_url; }

    std::vector<Events::Config> Loop_events() const { return experiment.loop_events; }

    std::vector<Events::Config> Init_events() const { return experiment.init_events; }

    Components Components_config() const { return components; }

private:
    static Config::Experiment Load_experiment(const YAML::Node& yaml);

    static Config::Components Load_components(const YAML::Node yaml);

    static Events::Config Parse_event(const YAML::Node& event_node);

    static void Print_event(const Events::Config& event);
};
