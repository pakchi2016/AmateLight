param([string]$filePath)

# Shift_JIS から UTF-8 に変換
$utf8Path = [System.Text.Encoding]::UTF8.GetString(
    [System.Text.Encoding]::GetEncoding("Shift_JIS").GetBytes($filePath)
)

# 出力ファイル名（入力ファイル名 + "_processed"）
$outputPath = $utf8Path -replace "(?<=\.)[^.]+$", "processed.jpg"

# WSL のコンソールアプリを実行
wsl ./image_processor "$utf8Path" "$outputPath"

# 実行完了後にウィンドウを閉じない
pause
