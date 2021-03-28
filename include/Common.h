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


#ifndef BENJAMINHERNE_PS1HELPERS_COMMON_H
#define BENJAMINHERNE_PS1HELPERS_COMMON_H

#include <array>
#include <vector>
#include <string>

namespace bh::ps1 {
    class Formatting {
        private:
            std::vector<std::string> data;
            bool usedInBash = false;
            std::string bashOpen = "\\[";
            std::string bashClose = "\\]";

        public:
            Formatting& text(std::string text);
            Formatting& colour(const std::array<float, 3>& rgb);
            Formatting& highlight(const std::array<float, 3>& rgb);
            Formatting& resetColour();
            Formatting& resetHighlight();
            Formatting& resetAll();
            std::string toString();
            Formatting& setUsedInBash(bool state);
        };

    class Colour {
        public:
            static std::array<float, 3> HSLtoRGB(float hue, float sat, float lum);
        };

    std::vector<float> numArray(float low, float high, int number);
}


#endif //BENJAMINHERNE_PS1HELPERS_COMMON_H
