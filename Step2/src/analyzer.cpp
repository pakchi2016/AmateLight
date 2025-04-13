#include "analyzer.hpp"
#include <opencv2/opencv.hpp>
#include <numeric>
#include <cmath>

using namespace cv;

namespace
{

    // ノイズ量を推定（Laplacianの分散）
    double estimate_noise_level(const Mat &gray)
    {
        Mat lap;
        Laplacian(gray, lap, CV_64F);
        Scalar mean, stddev;
        meanStdDev(lap, mean, stddev);
        return std::min(stddev[0] / 100.0, 1.0); // 正規化
    }

    // シャープネスを推定（Sobelで縦横エッジ）
    double estimate_sharpness(const Mat &gray)
    {
        Mat gx, gy;
        Sobel(gray, gx, CV_64F, 1, 0);
        Sobel(gray, gy, CV_64F, 0, 1);
        Mat grad;
        magnitude(gx, gy, grad);
        return std::min(mean(grad)[0] / 100.0, 1.0); // 正規化
    }

    // コントラストを推定（ヒストグラムのレンジ幅）
    double estimate_contrast(const Mat &gray)
    {
        double min_val, max_val;
        minMaxLoc(gray, &min_val, &max_val);
        return (max_val - min_val) / 255.0;
    }

    // カラーバランスを推定（R/G/Bの平均差）
    double estimate_color_balance(const Mat &image)
    {
        std::vector<Mat> channels;
        split(image, channels);
        Scalar r_mean = mean(channels[2]);
        Scalar g_mean = mean(channels[1]);
        Scalar b_mean = mean(channels[0]);
        double rg = std::abs(r_mean[0] - g_mean[0]);
        double gb = std::abs(g_mean[0] - b_mean[0]);
        double br = std::abs(b_mean[0] - r_mean[0]);
        return (rg + gb + br) / (3.0 * 255.0); // 正規化
    }

    // ガンマ値の推定（明るさから逆算）
    double estimate_gamma(const Mat &gray)
    {
        Scalar avg = mean(gray);
        double normalized = avg[0] / 255.0;
        return std::clamp(std::log(normalized) / std::log(0.5), 0.5, 2.0); // 仮想モデル
    }

} // namespace

ImageAnalysisResult analyze_image(const std::string &image_path)
{
    Mat image = imread(image_path);
    if (image.empty())
    {
        throw std::runtime_error("Failed to read image: " + image_path);
    }

    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    ImageAnalysisResult result;
    result.noise_level = estimate_noise_level(gray);
    result.sharpness_score = estimate_sharpness(gray);
    result.contrast_ratio = estimate_contrast(gray);
    result.color_balance = estimate_color_balance(image);
    result.gamma_guess = estimate_gamma(gray);

    return result;
}
