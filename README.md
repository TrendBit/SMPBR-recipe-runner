# SMPBR-recipe-runner
Service which can be used to control experiment based on the configuration file.

# How to Use it

### Dependencies
```
sudo apt-get install libyaml-cpp-dev binutils-dev libdw-dev libunwind-dev
```

### Compile
```  
git clone https://github.com/TrendBit/SMPBR-recipe-runner.git --recursive  
cd SMPBR-recipe-runner  
mkdir -p build && cd build  
cmake ..  
make  
```  
### Run
1. Edit api-server location in `config/default.yaml`
    - If recipe-runner is on same device as api-server then can be set to: `"base_url: localhost:8089"`
2. Start with `make run`
    - It will execute binary with default config `config/default.yaml`

# Libraries
- [yaml-cpp](https://github.com/jbeder/yaml-cpp) - MIT license
- [nlohmann/json](https://github.com/nlohmann/json) - MIT license
- [backward-cpp](https://github.com/bombela/backward-cpp) - MIT license
- [cpp-httplib](https://github.com/yhirose/cpp-httplib) - MIT license
