#include "analyzer.hpp"
#include "auto_adjust.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: analyze_main <image_path>" << std::endl;
        return 1;
    }

    try
    {
        std::string path = argv[1];
        ImageAnalysisResult result = analyze_image(path);
        FilterParameters params = generate_parameters(result);

        json j;
        j["denoise_strength"] = params.denoise_strength;
        j["sharpen_amount"] = params.sharpen_amount;
        j["contrast_level"] = params.contrast_level;
        j["color_balance_level"] = params.color_balance_level;
        j["gamma_value"] = params.gamma_value;

        std::cout << j.dump() << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }
}
