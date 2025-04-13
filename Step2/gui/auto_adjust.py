import subprocess
import json

def apply_auto_adjust(image_path, ui):
    try:
        result = subprocess.run(
            ['./analyze_main', image_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=True,
            text=True
        )
        params = json.loads(result.stdout)

        ui.denoise_slider.setValue(params['denoise_strength'])
        ui.sharpen_slider.setValue(params['sharpen_amount'])
        ui.contrast_slider.setValue(params['contrast_level'])
        ui.color_slider.setValue(params['color_balance_level'])
        ui.gamma_slider.setValue(params['gamma_value'])

    except Exception as e:
        print("自動調整に失敗しました:", e)
