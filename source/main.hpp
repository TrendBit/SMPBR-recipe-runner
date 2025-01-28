/**
 * @file main.hpp
 * @author Petr Malaník (TheColonelYoung(at)gmail(dot)com)
 * @version 0.1
 * @date 23.01.2025
 */

#include <iostream>
#include <string>

#include "planner.hpp"
#include "config.hpp"

#include "events/api_call.hpp"
#include "events/api_get.hpp"
#include "events/api_post.hpp"
#include "events/wait.hpp"
#include "events/print.hpp"
#include "events/bottle_temperature.hpp"
#include "events/heater_intensity.hpp"
#include "events/heater_temperature.hpp"
#include "events/led_panel_intensity.hpp"
#include "events/cuvette_pump_move.hpp"
#include "events/mixer_stir.hpp"
#include "events/aerator_move.hpp"
