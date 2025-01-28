/**
 * @file types.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 28.01.2025
 */

#pragma once

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
}
