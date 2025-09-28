//
// Created by Haoran Gan on 9/27/25.
//
#include "image_gray8.hpp"
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

namespace img {
    std::string next_token(std::ifstream& is) {
        std::string curr; char c;
        while (is.get(c)) {
            const auto uc = static_cast<unsigned char>(c);
            if (std::isspace(uc)) continue;
            if (uc == '#') {
                std::string dummy;
                std::getline(is, dummy);
                continue;
            }
            curr += c; break;
        }
        if (curr.empty()) return curr;
        while (is.get(c)) {
            const auto uc = static_cast<unsigned char>(c);
            if (uc == '#' || std::isspace(uc)) {
                if (uc == '#') {
                    std::string dummy;
                    std::getline(is, dummy);
                }
                break;
            }
            curr += c;
        }
        return curr;
    }

    image_gray8 load_ppm_as_gray(const std::filesystem::path& path) {
        std::ifstream is(path, std::ios::binary);
        if (!is) {
            throw std::runtime_error("Could not open file " + path.string());
        }
        auto magic = next_token(is);
        if (magic != "P6") {
            throw std::runtime_error("Only PPM (P6) supported.");
        }
        const auto w_tok = next_token(is);
        const auto h_tok = next_token(is);
        const auto m_tok = next_token(is);

        const auto width = std::stoi(w_tok);
        const auto height = std::stoi(h_tok);
        const auto maxval = std::stoi(m_tok);

        if (width <= 0 || height <= 0)  throw std::runtime_error("Invalid PPM dimensions");
        if (maxval <= 0 || maxval > 255) throw std::runtime_error("Only maxval 1..255 supported");


        if (w_tok.empty() || h_tok.empty() || m_tok.empty()) {
            throw std::runtime_error("Malformed PPM header");
        }

        is >> std::ws;
        std::size_t count = static_cast<std::size_t>(width) * static_cast<std::size_t>(height);

        std::vector<uint8_t> rgb(count * 3);
        is.read(reinterpret_cast<char*>(rgb.data()), static_cast<std::streamsize>(rgb.size()));

        if (is.gcount() != static_cast<std::streamsize>(rgb.size())) {
            throw std::runtime_error("Short read on P6 pixel data");
        }

        image_gray8 out;
        out.width = width; out.height = height; out.pixels.resize(count);

        // Convert RGB -> Gray using luma approx; scale if maxval != 255
        const float scale = 255.0f / static_cast<float>(maxval);
        for (size_t i = 0, p = 0; p < count; ++p, i += 3) {
            const float r = static_cast<float>(rgb[i+0]) * scale;
            const float g = static_cast<float>(rgb[i+1]) * scale;
            const float b = static_cast<float>(rgb[i+2]) * scale;
            long y = lround(0.299f*r + 0.587f*g + 0.114f*b + 0.5f);
            if (y < 0) y = 0; else if (y > 255) y = 255;
            out.pixels[p] = static_cast<uint8_t>(y);
        }
        return out;

    }

    void save_ppm_as_gray(const std::filesystem::path& path, const image_gray8& img) {
        if (img.width <= 0 || img.height <= 0) throw std::runtime_error("Invalid image dimensions");
        if (img.pixels.size() != img.width * img.height) throw std::runtime_error("Invalid image dimensions");
        std::ofstream os(path, std::ios::binary);
        if (!os) {
            throw std::runtime_error("Could not open file " + path.string() + " for writing");
        }

        // P6 header
        os << "P6\n" << img.width << ' ' << img.height << "\n255\n";

        // write rows: R=G=B=gray
        std::vector<std::uint8_t> row(static_cast<std::size_t>(img.width) * 3);
        for (int y = 0; y < img.height; ++y) {
            const std::uint8_t* src = &img.pixels[static_cast<std::size_t>(y) * img.width];
            for (int x = 0, j = 0; x < img.width; ++x, j += 3) {
                const std::uint8_t g = src[x];
                row[j + 0] = g; row[j + 1] = g; row[j + 2] = g;
            }
            os.write(reinterpret_cast<const char*>(row.data()),
                     static_cast<std::streamsize>(row.size()));
            if (!os) throw std::runtime_error("Failed writing PPM row");
        }

    }
}


