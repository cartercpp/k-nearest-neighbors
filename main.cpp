#include <iostream>
#include <print>
#include <string>
#include <string_view>
#include <stdexcept>
#include <array>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <ranges>
#include <cstddef>
#include <cmath>
#include "color.h"

extern const std::array<Color, 50> colors;

std::vector<std::string> Split(std::string_view, char);

int main()
{
    constexpr int K = 7;

    std::println("Example input:");
    std::println("\tInput RGB: (255,255,255)");
    std::println("\tPredicted color: White\n");

    while (true)
        try
        {
            std::string input;
            std::print("Input RGB: ");
            std::getline(std::cin, input);

            if (input.empty())
                break;
            else if ((input.front() != '(') || (input.back() != ')'))
                throw std::runtime_error{"Proper format: (R,G,B)"};

            input.erase(input.begin());
            input.pop_back();

            const std::vector<std::string> splitInput{Split(input, ',')};
            if (splitInput.size() != 3)
                throw std::runtime_error{"Proper format: (R,G,B)"};

            const int red = std::stoi(splitInput[0]),
                      green = std::stoi(splitInput[1]),
                      blue = std::stoi(splitInput[2]);

            std::vector<std::pair<Color, double>> colorDistances(colors.size());
            for (std::size_t i = 0; i < colors.size(); ++i)
            {
                const auto& color{colors[i]};
                const double distance = std::sqrt(
                    (red - color.m_red) * (red - color.m_red)
                    + (green - color.m_green) * (green - color.m_green)
                    + (blue - color.m_blue) * (blue - color.m_blue)
                );
                colorDistances[i] = std::pair{color, distance};
            }

            std::ranges::sort(colorDistances, [](const auto& lArg, const auto& rArg) {
                return lArg.second < rArg.second;
            });

            colorDistances.erase(colorDistances.begin() + K, colorDistances.end());

            std::map<std::string, double> labelToWeightedCount;
            for (const auto& [color, distance] : colorDistances)
                    labelToWeightedCount[color.m_name] += (distance > 0) ? (1 / distance) : 1;

            std::string output;
            double outputCount = 0;

            for (const auto& [label, count] : labelToWeightedCount)
                if (count > outputCount)
                {
                    output = label;
                    outputCount = count;
                }

            std::println("Predicted color: {}\n", output);
        }
        catch (const std::exception& e)
        {
            std::println("Error: {}\n", e.what());
        }
}