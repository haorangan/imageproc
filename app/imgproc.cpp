//
// Created by Haoran Gan on 9/27/25.
//

#include <image_gray8.hpp>

#include "gaussian.hpp"
#include "iostream"
#include "nonmax.hpp"
#include "sobel.hpp"


using namespace img;

// hardcoded constants
constexpr float SIGMA = 1.2;

std::filesystem::path suffix_path(const std::filesystem::path& in, const std::string& suffix) {
    const auto stem = in.stem().string();     // "out"
    const auto ext  = in.extension().string(); // ".ppm"
    const auto parent = in.parent_path();     // "data"
    const std::string newname = stem + "_" + suffix + ext; // "out_blur.ppm"
    return parent / newname;            // "data/out_blur.ppm"
}


int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: imgproc in.ppm out.ppm\n";
        return 1;
    }
    try {
        // convert to grayscale
        const auto g = load_ppm_as_gray(argv[1]);
        save_ppm_as_gray(suffix_path(argv[2], "gray"), g);

        // apply gaussian filter
        const FloatImage f = to_float(g);
        FloatImage tmp, blurred;
        gaussian_blur(f, tmp, blurred, SIGMA);
        const auto& blur_int8 = to_gray8(blurred);
        save_ppm_as_gray(suffix_path(argv[2], "blur"), blur_int8);

        // compute gradients with sobel
        const auto& gradients = sobel_operator(blurred);
        const auto& grads_int8 = to_gray8(gradients.magnitude);
        save_ppm_as_gray(suffix_path(argv[2], "grad"), grads_int8);

        // nonmax suppression
        const auto& mags = gradients.magnitude;
        const auto& dirs = gradients.direction;
        const auto& thin = nonmax_suppression(mags, dirs);
        const auto& thin_int8 = to_gray8(thin);
        save_ppm_as_gray(suffix_path(argv[2], "gradNMS"), thin_int8);



    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
    return 0;
}