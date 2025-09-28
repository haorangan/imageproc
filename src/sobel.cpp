//
// Created by Haoran Gan on 9/27/25.
//
#include "sobel.hpp"

#include "gaussian.hpp"


namespace img {
    Gradients sobel_operator(const FloatImage& img) {

        constexpr int sx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
        };
        constexpr int sy[3][3] = {
            { 1,  2,  1},
            { 0,  0,  0},
            {-1, -2, -1}
        };

        Gradients grads(img.width, img.height);

        for (int y = 0; y < img.height; ++y) {
            for (int x = 0; x < img.width; ++x) {
                float gx = 0.0f, gy = 0.0f;

                // Apply 3x3 Sobel kernels with clamp-to-edge
                for (int j = -1; j <= 1; ++j) {
                    for (int i = -1; i <= 1; ++i) {
                        const int yy = clampi(y + j, 0, img.height - 1);
                        const int xx = clampi(x + i, 0, img.width - 1);
                        const float pixel = img.at(yy, xx);

                        gx += pixel * static_cast<float>(sx[j+1][i+1]);
                        gy += pixel * static_cast<float>(sy[j+1][i+1]);
                    }
                }

                // Gradient magnitude & direction
                const float mag = std::sqrt(gx*gx + gy*gy);
                const float theta = std::atan2(gy, gx); // radians, range [-pi, pi]

                grads.magnitude.at(y, x) = mag;
                grads.direction.at(y, x) = theta;
            }
        }
        return grads;
    }
}
