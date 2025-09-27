//
// Created by Haoran Gan on 9/27/25.
//

#pragma once
#include <vector>
namespace img {
    struct FloatImage {
        int width; int height;
        std::vector<float> data;
        FloatImage() : width(0), height(0), data(0) {}
        FloatImage(const int width, const int height) : width(width), height(height), data(0) {}
        float& at(const int i, const int j) {
            return data[i * width + j];
        }
        [[nodiscard]] const float& at(const int i, const int j) const {
            return data[i * width + j];
        }
    };
}
