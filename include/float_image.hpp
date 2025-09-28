//
// Created by Haoran Gan on 9/27/25.
//

#pragma once
#include <image_gray8.hpp>
#include <vector>
namespace img {
    struct FloatImage {
        int width{}; int height{};
        std::vector<float> data;
        FloatImage() = default;
        FloatImage(const int width, const int height) : width(width), height(height), data(static_cast<size_t>(width) * static_cast<size_t>(height)) {}
        float& at(const int i, const int j) {
            return data[i * width + j];
        }
        [[nodiscard]] const float& at(const int i, const int j) const {
            return data[i * width + j];
        }
    };
    FloatImage to_float(const image_gray8& gray);
    image_gray8 to_gray8(const FloatImage& image);
}
