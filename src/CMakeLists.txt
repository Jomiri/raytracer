add_executable(raytracer main.cpp Image.cpp Sphere.cpp HitableList.cpp
        Random.cpp
        Helpers.cpp
        Dielectric.cpp
        Camera.cpp
        Metal.cpp
        Lambertian.cpp)

target_include_directories(raytracer
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include )
