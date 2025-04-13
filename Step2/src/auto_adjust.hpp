#ifndef AMATELITE_AUTO_ADJUST_HPP
#define AMATELITE_AUTO_ADJUST_HPP

#include "analyzer.hpp"

struct FilterParameters
{
    int denoise_strength;    // ノイズ除去 (0〜100)
    int sharpen_amount;      // シャープネス (0〜100)
    int contrast_level;      // コントラスト補正 (0〜100)
    int color_balance_level; // カラーバランス補正 (0〜100)
    int gamma_value;         // ガンマ補正 (0〜200 = 0.5〜2.0倍相当)
};

// 画像分析結果から最適なフィルタパラメータを生成
FilterParameters generate_parameters(const ImageAnalysisResult &analysis);

#endif // AMATELITE_AUTO_ADJUST_HPP
