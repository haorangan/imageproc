//
// Created by Haoran Gan on 9/27/25.
//

#include "hysteresis.hpp"
#include "queue"

namespace img {
    EdgeMap double_threshold(const FloatImage& thin, float low, float high) {
        EdgeMap em(thin.width, thin.height);
        for (int y = 0; y < thin.height; ++y) {
            for (int x = 0; x < thin.width; ++x) {
                const float m = thin.at(y, x);
                em.at(y, x) = (m >= high) ? EDGE_STRONG
                             : (m >= low)  ? EDGE_WEAK
                                           : EDGE_NONE;
            }
        }
        return em;
    }

    void hysteresis(EdgeMap& em) {
        auto inside = [&](const int y, const int x) { return 0 <= y && y < em.h && 0 <= x && x < em.w; };

        std::queue<std::pair<int, int>> q;

        // Seed the queue with existing strong edges
        for (int y = 0; y < em.h; ++y) {
            for (int x = 0; x < em.w; ++x) {
                if (em.at(y, x) == EDGE_STRONG) {
                    q.emplace(y, x);
                }
            }
        }

        // 8-connected neighbor offsets
        constexpr int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        constexpr int dy[8] = {-1,-1,-1,  0, 0,  1, 1, 1};

        // Flood fill
        while (!q.empty()) {
            auto [y, x] = q.front(); q.pop();
            for (int k = 0; k < 8; ++k) {
                int yy = y + dy[k], xx = x + dx[k];
                if (inside(yy, xx) && em.at(yy, xx) == EDGE_WEAK) {
                    em.at(yy, xx) = EDGE_STRONG;
                    q.emplace(yy, xx);
                }
            }
        }

        // Clear any weak pixels that were never connected
        for (auto& v : em.lab) {
            if (v == EDGE_WEAK) v = EDGE_NONE;
        }
    }
}
