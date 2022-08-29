#include <iostream>
#include <iomanip>
#include <vector>
#include <cfenv>

#include "include/cxxopts.hpp"

int main(int argc, char* const argv[]) {
    cxxopts::Options options("./prog", "Find Cost of Tile to Cover WxH Floor");

    options.add_options()
        ("h,help", "Print usage")
        ("width", "Floor width in ft", cxxopts::value<int>())
        ("height", "Floor height in ft", cxxopts::value<int>())
        ("cost", "Tile cost in USD/sq. ft", cxxopts::value<long double>());

    options.parse_positional({"width", "height", "cost"});
    cxxopts::ParseResult result;

    try {
        result = options.parse(argc, argv);
    } catch (const cxxopts::OptionParseException& x) {
        std::cerr << "./prog: " << x.what() << std::endl;
        std::cerr << "usage: ./prog [options] <width> <height> <cost>" <<
            std::endl;
        exit(1);
    }

    // Check for help option and return success
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    // Check for required arguments
    if (!result.count("width") ||
        !result.count("height") ||
        !result.count("cost")) {
        std::cerr << "./prog: missing required arguments (width/height/cost)" <<
            std::endl;
        exit(1);
    }

    int width = result["width"].as<int>();
    int height = result["height"].as<int>();
    long double cost = result["cost"].as<long double>();
    long double prod = width*height*cost;

    std::fesetround(FE_DOWNWARD);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total cost of floor tiles: " << prod << " " << std::endl;
}