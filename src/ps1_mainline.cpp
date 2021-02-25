//
// Created by benjaminherne on 24/2/21.
//

#include "Common.h"

#include <iostream>

int main(int argc, char* argv[]) {
    float hue = 201;
    float sat = .45;

    float lumLow = .25;
    float lumHigh = .5;

    float* vars[4] = {&hue, &sat, &lumLow, &lumHigh};

    for (int i = 1; i < argc; i++) {
        *vars[i-1] = strtof(argv[i], nullptr);
    }

    auto lums = bh::ps1::numArray(.25, .50, 2);

    auto base_colour = bh::ps1::Colour::HSLtoRGB(hue, sat, lumLow);
    std::vector<std::array<float, 3>> colours {};
    colours.reserve(lums.size());
    for (auto lum : lums) {
        colours.push_back(bh::ps1::Colour::HSLtoRGB(hue, sat, lum));
    }

    bh::ps1::Formatting fmt;
    fmt.highlight(base_colour).text(" ").highlight(colours[1]).colour(base_colour).text("")
       .resetColour().text(" \\u@\\h").highlight(colours[0]).colour(colours[1]).text("")
       .resetColour().text(" \\W").highlight(base_colour).colour(colours[0]).text("")
       .resetColour().text(" \\$").resetHighlight().colour(base_colour).text(" ")
       .resetAll();
    std::cout << fmt.toString() << std::endl;
}

