#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
    if (image.empty()) {
        std::cerr << "OpenCV の動作確認に失敗しました！" << std::endl;
        return -1;
    } else {
        std::cout << "OpenCV は正常に動作しています！" << std::endl;
        return 0;
    }
}
