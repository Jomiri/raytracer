add_executable(raytracer main.cpp Image.cpp Sphere.cpp HitableList.cpp
        UnitRandomGenerator.cpp
        Helpers.cpp
        Dielectric.cpp)

target_include_directories(raytracer
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include )
