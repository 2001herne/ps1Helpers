//  Copyright 2021 Benjamin Herne
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.


#include "Common.h"

#include <cmath>

void bh::ps1::Formatting::startEscape() {
    switch (mode) {
        case BASH:
            data.push_back(bashOpen + escapeSequenceStart);
            break;
        case SUDO:
            data.push_back(sudoEscapeSequenceStart);
            break;
    }
}

void bh::ps1::Formatting::endEscape() {
    data.push_back(escapeSequenceEnd);
    switch (mode) {
        case BASH:
            data.push_back(bashClose);
            break;
    }
}

bh::ps1::Formatting &bh::ps1::Formatting::text(std::string text) {
    data.push_back(text);
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::colour(const std::array<float, 3> &rgb) {
    int r = (int) std::round(rgb[0]);
    int g = (int) std::round(rgb[1]);
    int b = (int) std::round(rgb[2]);
    startEscape();
    data.push_back("38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b));
    endEscape();
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::highlight(const std::array<float, 3> &rgb) {
    int r = (int) std::round(rgb[0]);
    int g = (int) std::round(rgb[1]);
    int b = (int) std::round(rgb[2]);
    startEscape();
    data.push_back("48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b));
    endEscape();
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::resetColour() {
    startEscape();
    data.emplace_back("39");
    endEscape();
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::resetHighlight() {
    startEscape();
    data.emplace_back("49");
    endEscape();
    return *this;
}

bh::ps1::Formatting &bh::ps1::Formatting::resetAll() {
    startEscape();
    data.emplace_back("0");
    endEscape();
    return *this;
}

std::string bh::ps1::Formatting::toString() {
    std::string myData;
    for (const std::string& elem : data) {
        myData.append(elem);
    }
    return myData;
}

bh::ps1::Formatting &bh::ps1::Formatting::setMode(SpecialMode mode) {
    this->mode = mode;
    return *this;
}

std::array<float, 3> bh::ps1::Colour::HSLtoRGB(float hue, float sat, float lum) {
    float a = sat * std::min(lum, 1 - lum);

    auto f = [&](int n) {
        float k = fmodf((float) n + hue/30.f, 12.f);
        return (lum - a * std::max(-1.f, std::min(k - 3, std::min(9 - k, 1.f)))) * 255;
    };

    return {f(0), f(8), f(4)};
}

std::vector<float> bh::ps1::numArray(float low, float high, int number) {
    std::vector<float> ret;
    ret.reserve(number);
    for (int i = 0; i < number; i++) {
        ret.push_back(low + (float) (i+1) * (high - low) / (float) (number + 1));
    }
    return ret;
}