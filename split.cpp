//
// Created by cartercpp on 7/2/26.
//

#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <ranges>

std::vector<std::string> Split(std::string_view str, char splitChar)
{
    auto r = str | std::views::split(splitChar);

    std::vector<std::string> output;
    output.reserve(std::ranges::distance(std::ranges::begin(r), std::ranges::end(r)));

    for (auto&& substr : r)
        output.emplace_back(std::ranges::begin(substr), std::ranges::end(substr));

    return output;
}