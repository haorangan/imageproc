//
// Created by Haoran Gan on 9/27/25.
//
#include "nonmax.hpp"

namespace img {
    FloatImage nonmax_suppression(const FloatImage& mags, const FloatImage& angles) {
        FloatImage thin(mags.width, mags.height);

        auto dir_bin = [](float a){ // map angle to 0,1,2,3 (E/NE/N/NW)
            // normalize to [0,pi)
            if (a < 0) a += static_cast<float>(M_PI);
            // 0: ~0°, 1: ~45°, 2: ~90°, 3: ~135°
            float deg = a * 180.0f / static_cast<float>(M_PI);
            if ((deg >=   0 && deg < 22.5) || (deg >= 157.5 && deg < 180)) return 0;
            if (deg >=  22.5 && deg < 67.5)  return 1;
            if (deg >=  67.5 && deg < 112.5) return 2;
            return 3;
            // 112.5..157.5
        };

        auto clampi = [](int v, int lo, int hi){ return v<lo?lo:(v>hi?hi:v); };

        for (int y=0; y<mags.height; ++y){
            for (int x=0; x<mags.width; ++x){
                const float m = mags.at(y,x);
                const int b = dir_bin(angles.at(y,x));

                // pick neighbor offsets along direction bin
                int dx1=0, dy1=0, dx2=0, dy2=0;
                switch (b){
                    case 0:  dx1=-1; dy1=0;  dx2=+1; dy2=0;  break; // E–W
                    case 1:  dx1=-1; dy1=-1; dx2=+1; dy2=+1; break; // NE–SW
                    case 2:  dx1=0;  dy1=-1; dx2=0;  dy2=+1; break; // N–S
                    case 3:  dx1=+1; dy1=-1; dx2=-1; dy2=+1; break; // NW–SE
                    default: ;
                }

                const int x1 = clampi(x+dx1, 0, mags.width-1);
                const int y1 = clampi(y+dy1, 0, mags.height-1);
                const int x2 = clampi(x+dx2, 0, mags.width-1);
                const int y2 = clampi(y+dy2, 0, mags.height-1);

                const float m1 = mags.at(y1,x1);
                const float m2 = mags.at(y2,x2);

                thin.at(y,x) = (m >= m1 && m > m2) ? m : 0.0f; // keep strict peak
            }
        }
        return thin;
    }
}