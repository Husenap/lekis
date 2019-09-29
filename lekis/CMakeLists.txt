set(target_name "lekis")

set(rendering_files
    "src/rendering/Image.cpp"
    "src/rendering/Image.h"
    "src/rendering/Window.cpp"
    "src/rendering/Window.h")

set(math_files
    "src/math/MathUtils.cpp"
    "src/math/MathUtils.h"
    "src/math/Vec3.cpp"
    "src/math/Vec3.h"
    "src/math/SDF.h")

set(util_files
    "src/util/FPSCounter.cpp"
    "src/util/FPSCounter.h")

set(src_files
    ${rendering_files}
    ${math_files}
    ${util_files})

source_group("src\\rendering" FILES ${rendering_files})
source_group("src\\math" FILES ${math_files})
source_group("src\\util" FILES ${util_files})

add_library(${target_name} STATIC ${src_files})

target_include_directories(${target_name} INTERFACE "src")