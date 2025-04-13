#include "auto_adjust.hpp"
#include <algorithm>

static int normalize_to_slider(double value, double min_v, double max_v, int slider_min, int slider_max)
{
    double clamped = std::clamp((value - min_v) / (max_v - min_v), 0.0, 1.0);
    return static_cast<int>(clamped * (slider_max - slider_min) + slider_min);
}

FilterParameters generate_parameters(const ImageAnalysisResult &a)
{
    FilterParameters p;

    // ノイズが高いほど強く除去（反比例）
    p.denoise_strength = normalize_to_slider(1.0 - a.noise_level, 0.0, 1.0, 0, 100);

    // シャープネスはそのまま使う
    p.sharpen_amount = normalize_to_slider(a.sharpness_score, 0.0, 1.0, 0, 100);

    // コントラストは少ないほど強く補正
    p.contrast_level = normalize_to_slider(1.0 - a.contrast_ratio, 0.0, 1.0, 0, 100);

    // 色の偏りが大きいとき補正（大きいほど補正強く）
    p.color_balance_level = normalize_to_slider(a.color_balance, 0.0, 0.5, 0, 100);

    // ガンマは0.5〜2.0を 0〜200にマップ
    p.gamma_value = normalize_to_slider(a.gamma_guess, 0.5, 2.0, 0, 200);

    return p;
}
