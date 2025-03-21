#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat img = cv::imread("test.jpg"); // 画像を読み込む
    if (img.empty())
    {
        std::cerr << "画像が読み込めません！" << std::endl;
        return -1;
    }

    cv::imshow("Test Image", img); // 画像を表示
    cv::waitKey(0);                // キー入力待ち
    return 0;
}