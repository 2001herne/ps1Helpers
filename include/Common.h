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
        public:
            enum SpecialMode {
                NONE,
                BASH,
                SUDO
            };
        private:
            std::vector<std::string> data;
            SpecialMode mode = NONE;

            inline static const std::string bashOpen = "\\[";
            inline static const std::string bashClose = "\\]";

            inline static const std::string escapeSequenceStart = "\\e[";
            inline static const std::string escapeSequenceEnd = "m";

            inline static const std::string sudoEscapeSequenceStart = "\x1b[";

            void startEscape();
            void endEscape();

        public:
            Formatting& text(std::string text);
            Formatting& colour(const std::array<float, 3>& rgb);
            Formatting& highlight(const std::array<float, 3>& rgb);
            Formatting& resetColour();
            Formatting& resetHighlight();
            Formatting& resetAll();
            std::string toString();
            Formatting& setMode(SpecialMode mode);
    };

    class Colour {
        public:
            static std::array<float, 3> HSLtoRGB(float hue, float sat, float lum);
        };

    std::vector<float> numArray(float low, float high, int number);
}


#endif //BENJAMINHERNE_PS1HELPERS_COMMON_H
