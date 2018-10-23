# Simple raytracer
 This project is based on the book Ray Tracing in One Weekend by Peter Shirley.
 
I decided to use to the code to generate atom-inspired animations.

In the first animation, "core" spheres are metal and reflect light from the "electron" spheres.

![Animation 1](https://github.com/Jomiri/raytracer/blob/master/images/animation_metal.gif)


In the second animation, the "core" spheres are glass with refractive index 1.5.
 The center looks strange because the spheres overlap in the middle and the code cannot handle that properly.

![Animation 2](https://github.com/Jomiri/raytracer/blob/master/images/animation_glass_1.5.gif)


In the third animation, I raised refractive index to 2.0,
 which results in stronger total internal reflection and peculiar symmetrical regions where light passes through the "core".

![Animation 3](https://github.com/Jomiri/raytracer/blob/master/images/animation_glass_2.0.gif)

