# Specify the minimum CMAKE version required
cmake_minimum_required(VERSION 2.8)

# Your project's name
project(Zombie-Shooter)

# Add all files from the source/ folder to CMake
file(GLOB_RECURSE SRC
    "src/*.cpp"
<<<<<<< HEAD
    "src/*.h"
    "src/*.hpp"
=======
>>>>>>> 9990422359331f2330abfad091c9c755b5d21515
)

# Define the executable
add_executable(${PROJECT_NAME} ${SRC})

# Copy res folder to executable on build
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

<<<<<<< HEAD
=======
# JSON library
include_directories(deps/json)

>>>>>>> 9990422359331f2330abfad091c9c755b5d21515
# SFML
add_definitions(-DSFML_STATIC)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(deps/SFML)
include_directories(deps/SFML/include)
target_link_libraries(${PROJECT_NAME} sfml-network sfml-graphics sfml-window sfml-system sfml-audio)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
