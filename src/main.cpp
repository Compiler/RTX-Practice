#pragma once
#include <iostream>

int main(){

    constexpr int IMAGE_WIDTH = 256;
    constexpr int IMAGE_HEIGHT = 256;

    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for(int y = IMAGE_HEIGHT - 1; y >= 0; y--){
        for(int x = IMAGE_WIDTH - 1; x >= 0; x--){
            auto r = double(x) / (IMAGE_WIDTH - 1);
            auto g = double(y) / (IMAGE_HEIGHT - 1);
            auto b = 0.25;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    return 0;
}