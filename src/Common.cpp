//
// Created by benjaminherne on 24/2/21.
//

#include "Common.h"

#include <cmath>

bh::ps1::Formatting &bh::ps1::Formatting::text(std::string text) {
    data.push_back(text);
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::colour(const std::array<float, 3> &rgb) {
    int r = (int) std::round(rgb[0]);
    int g = (int) std::round(rgb[1]);
    int b = (int) std::round(rgb[2]);
    data.push_back("\\[\\e[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m\\]");
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::highlight(const std::array<float, 3> &rgb) {
    int r = (int) std::round(rgb[0]);
    int g = (int) std::round(rgb[1]);
    int b = (int) std::round(rgb[2]);
    data.push_back("\\[\\e[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m\\]");
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::resetColour() {
    data.emplace_back("\\e[39m");
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::resetHighlight() {
    data.emplace_back("\\e[49m");
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::resetAll() {
    data.emplace_back("\\e[0m");
    return *this;
}

std::string bh::ps1::Formatting::toString() {
    std::string myData;
    for (const std::string& elem : data) {
        myData.append(elem);
    }
    return myData;
}

std::array<float, 3> bh::ps1::Colour::HSLtoRGB(float hue, float sat, float lum) {
    float a = sat * std::min(lum, 1 - lum);

    auto f = [&](int n) {
        float k = fmodf((float) n + hue/30.f, 12.f);
        return (lum - a * std::max(-1.f, std::min(k - 3, std::min(9 - k, 1.f)))) * 255;
    };

    return {f(0), f(8), f(4)};
}
