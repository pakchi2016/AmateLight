#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    std::cout << "Hello, GIMP Turbo with OpenCV!" << std::endl;

    // 画像を読み込む
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
    {
        std::cerr << "画像が読み込めませんでした。" << std::endl;
        return -1;
    }

    // 画像を表示
    cv::imshow("Test Image", img);
    cv::waitKey(0);

    return 0;
}