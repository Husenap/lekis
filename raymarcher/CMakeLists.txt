set(target_name "raymarcher")

set(src_files
    "src/Vec3.cpp"
    "src/Vec3.h"
    "src/main.cpp")

add_executable(${target_name} ${src_files})