//
// Created by Haoran Gan on 9/27/25.
//
#include "gaussian.hpp"

namespace img {
    void convolve_row(const FloatImage& in, FloatImage& out, const std::vector<float>& k) {
        const int r = static_cast<int>(k.size())/2;
        out = FloatImage(in.width, in.height);
        for(int y = 0; y < in.height; ++y){
            for(int x = 0; x < in.width; ++x){
                float acc=0.f;
                for(int i = -r; i <= r; ++i){
                    const int xi = clampi(x + i,0,in.width-1);
                    acc += in.at(y,xi) * k[i+r];
                }
                out.at(y,x)=acc;
            }
        }
    }

    void convolve_col(const FloatImage& in, FloatImage& out, const std::vector<float>& k) {
        const int r = static_cast<int>(k.size())/2;
        out = FloatImage(in.width, in.height);
        for(int y = 0; y < in.height; ++y){
            for(int x = 0; x < in.width; ++x){
                float acc = 0.f;
                for(int j = -r; j <= r; ++j){
                    const int yj = clampi(y + j,0,in.height-1);
                    acc += in.at(yj,x) * k[j+r];
                }
                out.at(y,x)=acc;
            }
        }
    }

    std::vector<float> gaussian_kernel_1d(const float sigma){
        if (sigma <= 0.f) return {1.f};
        const int radius = static_cast<int>(std::ceil(3.f * sigma));
        const int n = 2 * radius + 1;
        std::vector<float> k(n);
        const float inv2s2 = 1.f/(2.f * sigma * sigma);
        float sum=0.f;
        for(int i=-radius;i<=radius;++i){
            const float v = std::exp(static_cast<float>(-i)*static_cast<float>(i)*inv2s2);
            k[i+radius]=v; sum+=v;
        }
        for(float& v:k) v/=sum;
        return k;
    }

    void gaussian_blur(const FloatImage& in, FloatImage& tmp, FloatImage& out, float sigma) {
        const auto k = gaussian_kernel_1d(sigma);
        convolve_row(in, tmp, k);
        convolve_col(tmp, out, k);
    }
}
