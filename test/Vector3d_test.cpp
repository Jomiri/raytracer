//
// Created by Joona on 11/10/2018.
//

#include "../include/catch/catch.hpp"
#include "../include/raytracer/vector3d.h"

TEST_CASE( "Vector default initialization", "[default_init]" ) {
    vec3 v;
    REQUIRE(v == vec3{1, 0, 0});
}

TEST_CASE( "Vector general initialization", "[general_init]") {
    vec3 v {2, 3, 4};
    REQUIRE(v.x == 2);
    REQUIRE(v.y == 3);
    REQUIRE(v.z == 4);

    vec3 v2 {-1.5, 0, 0.6};
    REQUIRE(v2.x == -1.5);
    REQUIRE(v2.y == 0);
    REQUIRE(v2.z == 0.6);
}

TEST_CASE( "Vector plus" "[operators]") {
    vec3 v1 {1, 2, 3};
    vec3 v2 {1, 1, 1};
    vec3 v3 = v1 + v2;
    v1 += v2;

    REQUIRE( v1 == vec3{2, 3, 4} );
    REQUIRE( v3 == vec3{2, 3, 4} );
}

TEST_CASE( "Vector minus" "[operators]") {
    vec3 v1 {1, 2, 3};
    vec3 v2 {1, 1, 1};
    vec3 v3 = v1 - v2;
    v1 -= v2;

    REQUIRE( v1 == vec3{0, 1, 2} );
    REQUIRE( v3 == vec3{0, 1, 2} );
}

TEST_CASE( "Vector multiplication" "[operators]") {
    vec3 v1 {1, 2, 3};
    vec3 v2 {1, 0.5, 2};
    vec3 v3 = v1 * v2;
    vec3 v4 = v2 * 2.0;
    v1 *= v2;
    v2 *= 2.0;

    REQUIRE( v1 == vec3{1, 1, 6} );
    REQUIRE( v3 == vec3{1, 1, 6} );
    REQUIRE( v2 == vec3{2, 1, 4} );
    REQUIRE( v4 == vec3{2, 1, 4} );
}

TEST_CASE( "Vector division" "[operators]") {
    vec3 v1 {1, 2, 3};
    vec3 v2 {1, 0.5, 2};
    vec3 v3 = v1 / v2;
    vec3 v4 = v2 / 2.0;
    v1 /= v2;
    v2 /= 2;

    REQUIRE( v1 == vec3{1, 4, 1.5} );
    REQUIRE( v3 == vec3{1, 4, 1.5} );
    REQUIRE( v2 == vec3{0.5, 0.25, 1} );
    REQUIRE( v4 == vec3{0.5, 0.25, 1} );
}

TEST_CASE( "Vector length squared", "[length squared]") {
    vec3 v1 {0, 0 ,0};
    vec3 v2 {1, 0 ,0};
    vec3 v3 {0, 1 ,0};
    vec3 v4 {0, 0 ,1};
    vec3 v5 {1, 1 ,1};
    vec3 v6 {2, 2 ,2};

    REQUIRE( v1.len_squared() == 0 );
    REQUIRE( v2.len_squared() == 1 );
    REQUIRE( v3.len_squared() == 1 );
    REQUIRE( v4.len_squared() == 1 );
    REQUIRE( v5.len_squared() == 3 );
    REQUIRE( v6.len_squared() == 12 );
}

TEST_CASE( "Vector length", "[length squared]") {
    vec3 v1 {0, 0 ,0};
    vec3 v2 {1, 0 ,0};
    vec3 v3 {0, 1 ,0};
    vec3 v4 {0, 0 ,1};
    vec3 v5 {2, 0 ,0};
    vec3 v6 {2, 2 ,2};

    REQUIRE( v1.len() == 0 );
    REQUIRE( v2.len() == 1 );
    REQUIRE( v3.len() == 1 );
    REQUIRE( v4.len() == 1 );
    REQUIRE( v5.len() == 2 );
    REQUIRE( v6.len() == sqrt(12) );
}

TEST_CASE( "Vector normalize", "[normalize]") {
    vec3 v {1, 2, 3};
    REQUIRE( v.len_squared() == 14 );

    v.normalize();
    REQUIRE( v.len() == 1 );
}

TEST_CASE( "Vector unit_vector", "[unit_vector]") {
    vec3 v {1, 2, 3};
    vec3 v_unit = unit_vector(v);
    v.normalize();
    REQUIRE( v_unit.len() == 1 );
    REQUIRE( v == v_unit );
}

TEST_CASE( "Vector dot product", "[dot]") {
    vec3 v1 {1, 2, 3};
    vec3 v2 {2, 3, 4};
    REQUIRE( dot(v1, v2) == 2 + 6 + 12 );
}

TEST_CASE( "Vector cross product", "[cross]") {
    vec3 v1 {1, 0, 0};
    vec3 v2 {0, 1, 0};
    vec3 v3 {0, 0, 1};
    REQUIRE( cross(v1, v1) == vec3{0, 0, 0} );
    REQUIRE( cross(v1, v2) == v3 );
    REQUIRE( cross(v2, v3) == v1 );
    REQUIRE( cross(v3, v1) == v2 );
    REQUIRE( cross(v2, v1) == -v3 );
    REQUIRE( cross(v3, v2) == -v1 );
    REQUIRE( cross(v1, v3) == -v2 );


    vec3 v4 {1, 1, 1};
    REQUIRE( cross(v3, v4) == vec3{-1, 1, 0} );
}
