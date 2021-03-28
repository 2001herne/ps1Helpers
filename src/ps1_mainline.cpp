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

    bh::ps1::Formatting fmt {};
    fmt.setMode(bh::ps1::Formatting::BASH);
    fmt.highlight(base_colour).text(" ").highlight(colours[1]).colour(base_colour).text("")
       .resetColour().text(" \\u@\\h").highlight(colours[0]).colour(colours[1]).text("")
       .resetColour().text(" \\W").highlight(base_colour).colour(colours[0]).text("")
       .resetColour().text(" \\$").resetHighlight().colour(base_colour).text(" ")
       .resetAll();
    std::cout << fmt.toString() << std::endl;
}

