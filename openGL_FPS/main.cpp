#include <iostream>
#include "vector3d.h"


int main()
{
    vector3d vec1;
    vector3d vec2(1 , 2 , 3);
    vector3d vec3(6 , 5 , 4);

    std::cout << vec1 << vec2 << std::endl;
    std::cout << vec2.length() << std::endl;

    vec2.normalize();

    std::cout << vec2 << std::endl;

    vector3d vec4 = vec2 + vec3;
    std::cout << vec4 << std::endl;

    vec4 += vec2;
    std::cout << vec4 << std::endl;

    return 0;
}