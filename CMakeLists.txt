cmake_minimum_required(VERSION 3.12.4)
project("lekis" C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /fp:fast")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "predefined")

add_subdirectory("raymarcher")