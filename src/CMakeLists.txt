add_executable(raytracer
        Main.cpp
        Image.cpp
        Sphere.cpp
        HitableList.cpp
        Random.cpp
        Helpers.cpp
        Dielectric.cpp
        Camera.cpp
        Metal.cpp
        Lambertian.cpp
        Worlds.cpp
        Scene.cpp
        Render.cpp)

target_include_directories(raytracer
        PUBLIC
        ${PROJECT_SOURCE_DIR}/deps)
