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

    auto lums = bh::ps1::numArray<2>(.25, .50);

    auto col1 = bh::ps1::Colour::HSLtoRGB(hue, sat, .25);
    auto col2 = bh::ps1::Colour::HSLtoRGB(hue, sat, lums[0]);
    auto col3 = bh::ps1::Colour::HSLtoRGB(hue, sat, lums[1]);

    bh::ps1::Formatting fmt;
    fmt.highlight(col1).text(" ").highlight(col3).colour(col1).text("")
       .resetColour().text(" \\u@\\h").highlight(col2).colour(col3).text("")
       .resetColour().text(" \\W").highlight(col1).colour(col2).text("")
       .resetColour().text(" \\$").resetHighlight().colour(col1).text(" ")
       .resetAll();
    std::cout << fmt.toString() << std::endl;
}

