# Basic raytracer
 This project is based on the book [Ray Tracing in One Weekend](https://github.com/petershirley/raytracinginoneweekend) by Peter Shirley. I decided to use the code to generate atom-inspired animations. In this first animation, "core" spheres are metal and reflect light from the "electron" spheres.
More animations below.

![Animation 1](https://github.com/Jomiri/raytracer/blob/master/images/animation_metal.gif)

## Improvements on the original code

* New Scene class using variadic templates for controlling the lifetime of Hitables and Materials.
* Templated vec3 class.
* Simple Image class for writing the output to disk.
* PNG output using 
[stb_image_write.h](https://github.com/nothings/stb/blob/master/stb_image_write.h) library.
* Unit testing using [Catch2](https://github.com/catchorg/Catch2) library (only for vec3 at the moment).
* Parallel rendering with std::async.
* Random number generation with \<random\> header.
* General refactoring and style changes to my own liking.

## Simple performance improvement

Profiling this code on Visual Studio 2017, I realized that the bulk of the computation happens (unsurprisingly) in
the first couple of lines of the Sphere.hit() function. Most of the time, the ray does not hit the sphere, the hit() function returns at
the first if statement and no expensive color computation is needed with that sphere.

I obtained a significant speedup in Visual Studio 15.0 (close to ~100% in a simple scene) by making Ray.origin() and Ray.direction() return const references,
 which avoids multiple copy operations in the critical code section.

## More animations

In the second animation, the "core" spheres are glass with refractive index 1.5.
 The center looks strange because the spheres overlap in the middle and the code cannot handle that properly.

![Animation 2](https://github.com/Jomiri/raytracer/blob/master/images/animation_glass_1.5.gif)


In the third animation, I raised refractive index to 2.0,
 which results in stronger total internal reflection and peculiar symmetrical regions where light passes through the "core".

![Animation 3](https://github.com/Jomiri/raytracer/blob/master/images/animation_glass_2.0.gif)

## License

The book's original code by Peter Shirley is in the public domain. This project is licensed under the MIT license. See also
DEPENDENCY_LICENSES.txt.