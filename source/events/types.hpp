/**
 * @file types.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once
#include <array>
#include <optional>

namespace Events{
    enum class Type{
        heater_on,
        heater_off,
        illumination_on,
        illumination_off,
        pump,
        air,
        mix,
        wait
    };

    struct Config {  // Renamed from EventConfig
        Type type;
        std::array<std::optional<float>, 4> params = {std::nullopt, std::nullopt, std::nullopt, std::nullopt};
    };
}
