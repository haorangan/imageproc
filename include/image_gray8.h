//
// Created by Haoran Gan on 9/27/25.
//
#pragma once
#include <vector>
#include <filesystem>

namespace img {

    struct image_gray8 {
        int width; int height;
        std::vector<std::uint8_t> pixels;

        uint8_t& at(const int y, const int x) {
            return pixels[y*width + x];
        }
        [[nodiscard]] const uint8_t& at(const int y, const int x) const {
            return pixels[y*width + x];
        }

    };

    image_gray8 load_ppm_as_gray(const std::filesystem::path& path);
    void save_ppm_as_gray(const std::filesystem::path& path, const image_gray8& img);
}