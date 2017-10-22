# Specify the minimum CMAKE version required
cmake_minimum_required(VERSION 2.8)

# Your project's name
project(Zombie-Shooter)

# Add all files from the source/ folder to CMake
file(GLOB_RECURSE SRC
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
)

file(GLOB_RECURSE SRC_GAMEOBJECT
    "src/gameobject/*.cpp"
    "src/gameobject/*.h"
    "src/gameobject/*.hpp"
)

file(GLOB_RECURSE SRC_RESOURCE
    "src/resource/*.cpp"
    "src/resource/*.h"
    "src/resouce/*.hpp"
)

file(GLOB_RECURSE SRC_STATE
    "src/state/*.cpp"
    "src/state/*.h"
    "src/state/*.hpp"
)

file(GLOB_RECURSE SRC_SYSTEMS
    "src/systems/*.cpp"
    "src/systems/*.h"
    "src/systems/*.hpp"
)

file(GLOB_RECURSE SRC_UTIL
    "src/util/*.cpp"
    "src/util/*.h"
    "src/util/*.hpp"
)

# Define the executable
add_executable(${PROJECT_NAME} ${SRC} ${SRC_GAMEOBJECT} ${SRC_RESOURCE} ${SRC_STATE} ${SRC_SYSTEMS} ${SRC_UTIL})

#Define the filters
source_group("gameobject" FILES ${SRC_GAMEOBJECT})
source_group("resources" FILES ${SRC_RESOURCE})
source_group("state" FILES ${SRC_STATE})
source_group("system" FILES ${SRC_SYSTEMS})
source_group("util" FILES ${SRC_UTIL})

# Copy res folder to executable on build
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

# JSON library
include_directories(deps/json)

# SFML
add_definitions(-DSFML_STATIC)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(deps/SFML)
include_directories(deps/SFML/include)
target_link_libraries(${PROJECT_NAME} sfml-network sfml-graphics sfml-window sfml-system sfml-audio)

# GCC Arguments 
if(CMAKE_COMPILER_IS_GNUXX)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-pmf-conversions")
elseif(CMAKE_COMPILER_IS_MSVC)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wno-pmf-conversions")
endif(CMAKE_COMPILER_IS_GNUXX)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
