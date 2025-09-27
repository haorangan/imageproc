//
// Created by Haoran Gan on 9/27/25.
//

#include <image_gray8.h>
#include "iostream"


using namespace img;
int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: imgproc in.ppm out.ppm\n";
        return 1;
    }
    try {
        auto g = load_ppm_as_gray(argv[1]);
        save_ppm_as_gray(argv[2], g);
        std::cout << "OK\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
    return 0;
}