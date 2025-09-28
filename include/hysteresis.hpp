//
// Created by Haoran Gan on 9/27/25.
//

#pragma once
#include "float_image.hpp"

namespace img {
    enum : uint8_t { EDGE_NONE = 0, EDGE_WEAK = 1, EDGE_STRONG = 2 };

    struct EdgeMap {
        int w, h;
        std::vector<uint8_t> lab;

        EdgeMap(const int W, const int H) : w(W), h(H), lab(static_cast<size_t>(W) * H, EDGE_NONE) {}

        uint8_t& at(const int y, const int x)       { return lab[static_cast<size_t>(y) * w + x]; }
        [[nodiscard]] const uint8_t& at(const int y, const int x) const { return lab[static_cast<size_t>(y) * w + x]; }
    };

    EdgeMap double_threshold(const FloatImage& thin, float low, float high);

    void hysteresis(EdgeMap& em);
}
