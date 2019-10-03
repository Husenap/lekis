set(target_name "raycaster")

set(src_files
    "src/Map.h"
    "src/Map.cpp"
    "src/main.cpp"
    "src/Player.h"
    "src/Bitmap.cpp"
    "src/Bitmap.h")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name} "lekis")

set_target_properties(${target_name} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin )