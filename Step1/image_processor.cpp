#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    // コマンドライン引数のチェック
    if (argc != 3) {
        std::cerr << "使い方: " << argv[0] << " <入力画像> <出力画像>\n";
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    // 画像を読み込む
    cv::Mat image = cv::imread(inputPath);
    if (image.empty()) {
        std::cerr << "エラー: 画像を読み込めませんでした: " << inputPath << "\n";
        return 1;
    }

    std::cout << "画像を正常に読み込みました: " << inputPath << "\n";

    // 画像を保存する
    if (!cv::imwrite(outputPath, image)) {
        std::cerr << "エラー: 画像の保存に失敗しました: " << outputPath << "\n";
        return 1;
    }

    std::cout << "画像を保存しました: " << outputPath << "\n";

    return 0;
}
