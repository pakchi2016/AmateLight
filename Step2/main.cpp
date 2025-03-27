#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "使用方法: GIMP-Turbo.exe <画像ファイルのパス>" << std::endl;
        return 1;
    }

    // 画像ファイルのパスを取得
    std::string imagePath = argv[1];

    // 画像を読み込む
    cv::Mat image = cv::imread(imagePath);
    if (image.empty()) {
        std::cerr << "画像を読み込めません: " << imagePath << std::endl;
        return 1;
    }

    // 画像情報を表示
    std::cout << "画像を読み込みました: " << imagePath << std::endl;
    std::cout << "サイズ: " << image.cols << "x" << image.rows << std::endl;

    // 画像をウィンドウに表示（確認用）
    cv::imshow("Input Image", image);
    cv::waitKey(0);  // キー入力待ち

    return 0;
}
