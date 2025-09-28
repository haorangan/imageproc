//
// Created by Haoran Gan on 9/27/25.
//
#pragma once
#include "float_image.hpp"

namespace img {
    struct Gradients {
        FloatImage magnitude;
        FloatImage direction; // angle in radians

        Gradients(const int w, const int h) : magnitude(w,h), direction(w,h) {}

    };
    Gradients sobel_operator(const FloatImage& img);
}
