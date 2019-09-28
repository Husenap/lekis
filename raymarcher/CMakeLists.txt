set(target_name "raymarcher")

set(src_files
    "src/SDF.h"
    "src/FPSCounter.cpp"
    "src/FPSCounter.h"
    "src/Raymarcher.cpp"
    "src/Raymarcher.h"
    "src/Image.cpp"
    "src/Image.h"
    "src/Window.cpp"
    "src/Window.h"
    "src/Vec3.cpp"
    "src/Vec3.h"
    "src/main.cpp")

add_executable(${target_name} ${src_files})