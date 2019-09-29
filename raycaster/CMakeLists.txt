set(target_name "raycaster")

set(src_files
    "src/Map.h"
    "src/Map.cpp"
    "src/main.cpp"
    "src/Player.h")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name} "lekis")