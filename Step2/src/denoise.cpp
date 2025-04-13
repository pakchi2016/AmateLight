// denoise.cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: denoise <input_image> <output_image>" << std::endl;
        return -1;
    }

    cv::Mat input = cv::imread(argv[1]);
    if (input.empty())
    {
        std::cerr << "Failed to load input image: " << argv[1] << std::endl;
        return -1;
    }

    cv::Mat output;
    // ノイズ除去（非局所平均）
    cv::fastNlMeansDenoisingColored(input, output, 10, 10, 7, 21);

    if (!cv::imwrite(argv[2], output))
    {
        std::cerr << "Failed to save output image: " << argv[2] << std::endl;
        return -1;
    }

    std::cout << "Denoised image saved to: " << argv[2] << std::endl;
    return 0;
}
