//
// Created by Haoran Gan on 9/27/25.
//
#pragma once
#include "float_image.hpp"

namespace img {
    FloatImage nonmax_suppression(const FloatImage& mags, const FloatImage& angles);
}
