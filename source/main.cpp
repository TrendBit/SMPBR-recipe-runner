#include "main.hpp"

Planner planner;

void signal_handler(int){
    std::cout << "\nReceived shutdown signal..." << std::endl;
    planner.Stop();
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config.yaml>" << std::endl;
        return 1;
    }

    std::signal(SIGTERM, signal_handler); // systemctl stop
    std::signal(SIGHUP, signal_handler);  // service reload
    std::signal(SIGQUIT, signal_handler); // graceful quit
    std::signal(SIGINT, signal_handler);  // ctrl+c

    Config config(argv[1]);

    Events::API_call::Set_client(config.Server_URL());

    planner.Load_init(config.Init_events(), config.Components_config());
    planner.Load_loop(config.Loop_events(), config.Components_config());

    planner.Start();

    return 0;
}
