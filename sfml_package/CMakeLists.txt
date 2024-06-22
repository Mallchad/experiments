cmake_minimum_required(VERSION 3.0)
project(Poomismang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(GIT_SHALLOW TRUE)
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_NETWORK OFF)

set(SFML_BUILD_AUDIO ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)

FetchContent_MakeAvailable(SFML)

set(Poomismang_Libs
        sfml-graphics
        sfml-audio
        sfml-system
        sfml-window
)



add_executable(Poomismang main.cpp)
target_link_libraries(Poomismang ${Poomismang_Libs})

# target_link_libraries(Poomismang PUBLIC ${Poomismang_Libs})
# cmake_minimum_required(VERSION 2.7)
# project(test)

# set(CMAKE_CXX_STANDARD 17)
# set(SFML_STATIC_LIBRARIES TRUE)

# set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/home/mallchad/tmp/SFML-2.6.1/lib/cmake/SFML")
# set(SFML_DIR "/home/mallchad/tmp/SFML-2.6.1/lib/cmake/SFML")
# find_package(SFML)
# add_executable(test main.cpp)
# target_link_libraries(test sfml-system sfml-window sfml-graphics sfml-audio)
