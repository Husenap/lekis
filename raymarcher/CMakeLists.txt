set(target_name "raymarcher")

set(src_files
    "src/Raymarcher.cpp"
    "src/Raymarcher.h"
    "src/main.cpp")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name} "lekis")