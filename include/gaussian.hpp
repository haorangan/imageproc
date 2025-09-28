//
// Created by Haoran Gan on 9/27/25.
//
#pragma once
#include <vector>
#include "float_image.hpp"

namespace img {
    inline int clampi(int v, int lo, int hi){ return v<lo?lo:(v>hi?hi:v); }

    void convolve_row(const FloatImage& in, FloatImage& out, const std::vector<float>& k);
    void convolve_col(const FloatImage& in, FloatImage& out, const std::vector<float>& k);

    std::vector<float> gaussian_kernel_1d(float sigma);
    void gaussian_blur(const FloatImage& in, FloatImage& tmp, FloatImage& out, float sigma);
}
