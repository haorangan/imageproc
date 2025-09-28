//
// Created by Haoran Gan on 9/27/25.
//

#include "canny.hpp"

#include "float_image.hpp"
#include "gaussian.hpp"
#include "hysteresis.hpp"
#include "nonmax.hpp"
#include "sobel.hpp"

namespace img {
    static float max_value(const FloatImage& img) {
        float m = 0.f;
        for (float v : img.data) if (v > m) m = v;
        return m;
    }

    image_gray8 canny_edges(const image_gray8& in, const CannyParams& p) {
        // 1) to float
        FloatImage f = to_float(in);

        // 2) Gaussian blur
        FloatImage tmp, blurred;
        gaussian_blur(f, tmp, blurred, p.sigma);

        // 3) Sobel gradients → magnitude + direction (radians)
        auto grads = sobel_operator(blurred);  // grads.magnitude, grads.direction

        // 4) Non-maximum suppression (thin)
        FloatImage thin = nonmax_suppression(grads.magnitude, grads.direction);

        // 5) Choose thresholds (auto if not provided)
        float high = p.high;
        float low  = p.low;
        if (high <= 0.0f) {
            float maxMag = max_value(thin);
            // Heuristic: 20% of max as high
            high = 0.20f * maxMag;
        }
        if (low <= 0.0f) {
            low = p.low_ratio * high; // default 0.5 * high
        }

        // 6) Double threshold → hysteresis
        EdgeMap em = double_threshold(thin, low, high);
        hysteresis(em);

        // 7) Pack to Gray8 (255 = edge, 0 = non-edge)
        image_gray8 out;
        out.width = em.w;
        out.height = em.h;
        out.pixels.resize(static_cast<size_t>(em.w) * em.h);
        for (size_t i = 0; i < em.lab.size(); ++i) {
            out.pixels[i] = (em.lab[i] == EDGE_STRONG) ? 255u : 0u;
        }
        return out;
    }
}
