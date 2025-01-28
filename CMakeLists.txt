include(FetchContent)

cmake_minimum_required(VERSION 3.16)
project(recipe-runner
        VERSION 1.0
        LANGUAGES CXX)

# Compiler settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -pedantic -pg -g")

# Find required packages
find_package(yaml-cpp REQUIRED)

FetchContent_Declare(json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
FetchContent_MakeAvailable(json)

# Source files
file(GLOB_RECURSE SOURCES
    "source/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "source/*.hpp"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} yaml-cpp )
target_link_libraries(${PROJECT_NAME} dw bfd dwarf unwind)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# Set include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)

# Set output directories
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Installation
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

# Service installation target
add_custom_target(install-service
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/recipe-runner.service
            /etc/systemd/system/recipe-runner.service
    DEPENDS ${PROJECT_NAME}
    COMMENT "Installing recipe-runner systemd service"
)

add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME} config/default.yaml
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running ${PROJECT_NAME} with default config"
)

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
    set(CTEST_PARALLEL_LEVEL ${N})
endif()
