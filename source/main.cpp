#include "main.hpp"

// Struct to store configuration
struct Config {
    std::string baseUrl;
    std::string endpoint;
    int interval;
};

// Function to load configuration from YAML
Config loadConfig(const std::string& filepath) {
    YAML::Node config = YAML::LoadFile(filepath);
    Config cfg;
    cfg.baseUrl = config["rest_api"]["base_url"].as<std::string>();
    cfg.endpoint = config["endpoints"][0]["name"].as<std::string>();
    cfg.interval = config["endpoints"][0]["interval"].as<int>();
    return cfg;
}

// Function to call the REST API at regular intervals
void runService(const Config& cfg) {
    httplib::Client client(cfg.baseUrl.c_str());

    while (true) {
        auto response = client.Get(cfg.endpoint.c_str());
        if (response && response->status == 200) {
            json temp_json = json::parse(response->body);
            float temp = temp_json["temperature"];
            std::cout << "Temperature: " << std::fixed << std::setprecision(2) << temp << "°C" << std::endl;
        } else {
            std::cerr << "Error: "
                      << (response ? std::to_string(response->status) : "No response")
                      << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(cfg.interval));
    }
}

// Function to send a POST request
void Start_mixer(const std::string& baseUrl) {
    httplib::Client client(baseUrl.c_str());
    client.set_default_headers({{"Content-Type", "application/json"}});

    std::string endpoint = "/control/heater/intensity";

    // JSON payload
    json payload = {
        {"intensity", 0.7}
    };

    auto response = client.Post(endpoint.c_str(), payload.dump(), "application/json");

    if (response && response->status == 200) {
        std::cout << "POST Successful: " << response->body << std::endl;
    } else {
        std::cerr << "POST Failed: "
                  << (response ? std::to_string(response->status) : "No response")
                  << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Load configuration file
    std::string configFile = argc > 1 ? argv[1] : "config.yaml";
    Config cfg;

    try {
        cfg = loadConfig(configFile);
    } catch (const std::exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
        return 1;
    }

    Start_mixer(cfg.baseUrl);

    std::cout << "Service started with config:" << std::endl;
    std::cout << "Base URL: " << cfg.baseUrl << std::endl;
    std::cout << "Endpoint: " << cfg.endpoint << std::endl;
    std::cout << "Interval: " << cfg.interval << " seconds" << std::endl;

    runService(cfg);

    return 0;
}
