//
// Created by Haoran Gan on 9/27/25.
//
#pragma once
#include <image_gray8.hpp>

namespace img {
    struct CannyParams {
        float sigma      = 1.2f;   // Gaussian blur strength
        float high       = -1.0f;  // if <=0, auto-picked from data
        float low        = -1.0f;  // if <=0, derived from high * low_ratio
        float low_ratio  = 0.5f;   // low = low_ratio * high (when low <= 0)
    };

    image_gray8 canny_edges(const image_gray8& in, const CannyParams& p = {});
}
