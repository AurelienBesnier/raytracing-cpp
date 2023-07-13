#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "vec3.hpp"
#include <fstream>
#include <iostream>

using BYTE = unsigned char;

class Image {
private:
    int width, height;
    std::vector<color> pixels;

    int getIndex(int j, int i) const {
        return j + i * width;
    }

public:
    Image(int width, int height): width(width), height(height)
    {
        pixels.resize(width * height * 3);
    }

    ~Image() = default;

    void setPixel(int j,int i, const color& col, int samples_per_pixel)
    {
        const int idx = getIndex(j,i);

        float r = col.x();
        float g = col.y();
        float b = col.z();

        // Divide the color by the number of samples and gamma-correct for gamma=2.0.
        auto scale = 1.0 / samples_per_pixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        // Write the translated [0,255] value of each color component.
        BYTE R = static_cast<int>(256 * clamp(r, 0.0, 0.999));
        BYTE G = static_cast<int>(256 * clamp(g, 0.0, 0.999));
        BYTE B = static_cast<int>(256 * clamp(b, 0.0, 0.999));

        pixels[idx] = color(R,G,B);
    }

    void writePPM(const std::string & filename) const
    {
        std::ofstream file(filename);
        file << "P3\n" << width << " " << height << "\n255\n";
        for (int j = height-1; j >= 0; --j)
        {
            for (int i = 0; i < width; ++i)
            {
                const int idx = getIndex(j,i);
                const int R = pixels[idx].x();
                const int G = pixels[idx].y();
                const int B = pixels[idx].z();
                file << R << " " << G << " " << B << std::endl;
            }
        }
        file.close();
    }
};

#endif // IMAGE_HPP
