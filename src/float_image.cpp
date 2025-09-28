#include "float_image.hpp"
#include <image_gray8.hpp>
#include <iostream>
//
// Created by Haoran Gan on 9/27/25.
//
namespace img {
    // helpers
    FloatImage to_float(const image_gray8& gray) {
        FloatImage result(gray.width, gray.height);
        const auto count = gray.width * gray.height;
        for (int i = 0; i < count; i++) {
            result.data[i] = static_cast<float>(gray.pixels[i]);
        }
        return result;
    }
    image_gray8 to_gray8(const FloatImage& image) {
        const auto count = image.width * image.height;
        image_gray8 result(image.width, image.height);
        result.pixels.resize(count);
        for (int i = 0; i < count; i++) {
            int v = static_cast<int>(std::lround(image.data[i]));
            if(v < 0) v = 0;
            if(v > 255) v = 255;
            result.pixels[i]=static_cast<uint8_t>(v);
        }
        return result;
    }
}
