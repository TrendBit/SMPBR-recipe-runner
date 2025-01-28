#include "main.hpp"

int main(int argc, char* argv[]) {

    Events::API_call::Set_client("192.168.1.241:8089");

    Planner planner;

    planner.Add(Events::Print("Starting new cycle"));
    planner.Add(Events::Heater_intensity(0.0));
    planner.Add(Events::Wait(2.5));
    planner.Add(Events::Heater_intensity(0.0));
    planner.Add(Events::Wait(2.5));
    planner.Add(Events::Print(Events::Heater_temperature()));
    planner.Add(Events::Wait(1));
    planner.Add(Events::Print(Events::Bottle_temperature()));
    planner.Add(Events::Wait(5));

    planner.Start();

    return 0;
}

