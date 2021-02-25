//
// Created by benjaminherne on 24/2/21.
//

#ifndef BENJAMINHERNE_PS1HELPERS_COMMON_H
#define BENJAMINHERNE_PS1HELPERS_COMMON_H

#include <array>
#include <vector>
#include <string>

namespace bh::ps1 {
    class Formatting {
    private:
        std::vector<std::string> data;
    public:
        Formatting& text(std::string text);
        Formatting& colour(const std::array<float, 3>& rgb);
        Formatting& highlight(const std::array<float, 3>& rgb);
        Formatting& resetColour();
        Formatting& resetHighlight();
        Formatting& resetAll();
        std::string toString();
    };

    class Colour {
    public:
        static std::array<float, 3> HSLtoRGB(float hue, float sat, float lum);
    };

    std::vector<float> numArray(float low, float high, int number);
}


#endif //BENJAMINHERNE_PS1HELPERS_COMMON_H
