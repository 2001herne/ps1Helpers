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

#include <git2.h>

#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
    git_libgit2_init();
    git_buf root {nullptr};
    auto dir = std::filesystem::current_path().string();
    int error = git_repository_discover(&root, dir.c_str(), false, nullptr);
    bool isRepo = !error;
    if (isRepo) {
        std::string data {root.ptr};
        std::string repo_name = std::filesystem::path(data).parent_path().parent_path().filename().string();
        git_buf_free(&root);

        git_repository* repo = {nullptr};
        git_reference* head = {nullptr};

        git_repository_open(&repo, data.c_str());
        git_repository_head(&head, repo);

        const char * branch = nullptr;
        error = git_branch_name(&branch, head);
        bool is_branch = !error;

        git_reference* commit_ref = {nullptr};
        git_reference_resolve(&commit_ref, head);
        const git_oid* commit_oid = git_reference_target(commit_ref);
        char commit_id[7];
        git_oid_tostr(commit_id, 7, commit_oid);

        float hue = 201;
        float sat = .45;
        float lumLow = .25;
        float lumHigh = .5;

        float* args[] {&hue, &sat, &lumLow, &lumHigh};

        for (int i = 1; i < argc; i++) {
            *(args[i-1]) = strtof(argv[i], nullptr);
        }

        int numCols = 2 + is_branch * 2;

        auto lums = bh::ps1::numArray(lumLow, lumHigh, numCols);

        auto base_colour = bh::ps1::Colour::HSLtoRGB(hue, sat, lumLow);
        std::vector<std::array<float, 3>> cols {};
        cols.reserve(lums.size());
        for (auto lum : lums) {
            cols.push_back(bh::ps1::Colour::HSLtoRGB(hue, sat, lum));
        }

        auto rCols = cols.rbegin();

        bh::ps1::Formatting fmt;
        fmt.highlight(base_colour).text(" ").highlight(rCols[0]).colour(base_colour).text("")
           .resetColour().text(" " + repo_name).highlight(rCols[1]).colour(rCols[0]).text("");
        if (is_branch) {
            fmt.resetColour().text(" ").highlight(rCols[2]).colour(rCols[1]).text("")
               .resetColour().text(" " + std::string(branch)).highlight(rCols[3]).colour(rCols[2]).text("");
        }
        fmt.resetColour().text(" ").highlight(base_colour).colour(cols[0]).text("")
           .resetColour().text(" " + std::string(commit_id)).resetHighlight().colour(base_colour).text(" ")
           .resetAll();

        std::string gitline = fmt.toString();

        std::string rem1 = "\\[";

        std::string gitline_erased = gitline;
        for (auto i = gitline_erased.find(rem1); i != std::string::npos; i = gitline_erased.find(rem1)) {
            gitline_erased.erase(i, rem1.length());
        }

        std::string rem2 = "\\]";

        for (auto i = gitline_erased.find(rem2); i != std::string::npos; i = gitline_erased.find(rem2)) {
            gitline_erased.erase(i, rem2.length());
        }

        for (auto i = gitline_erased.find("\\e["); i != std::string::npos; i = gitline_erased.find("\\e[")) {
            std::string substr = gitline_erased.substr(i);
            auto j = substr.find('m');
            if (j != std::string::npos) {
                gitline_erased.erase(i, j + 1);
            }
        }

        std::cout << gitline << std::endl;
    }
}

