#ifndef AMATELITE_ANALYZER_HPP
#define AMATELITE_ANALYZER_HPP

#include <string>

struct ImageAnalysisResult
{
    double noise_level;     // ノイズの推定値（0.0〜1.0相当）
    double sharpness_score; // シャープネスの指標（高いほどシャープ）
    double contrast_ratio;  // コントラストの幅（0.0〜1.0）
    double color_balance;   // RGBバランスの偏差（0に近いほど中立）
    double gamma_guess;     // ガンマ値の推定（例: 0.8〜1.8）
};

// 画像ファイルを解析して画質指標を返す関数
ImageAnalysisResult analyze_image(const std::string &image_path);

#endif // AMATELITE_ANALYZER_HPP
