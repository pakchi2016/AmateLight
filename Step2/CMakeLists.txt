cmake_minimum_required(VERSION 3.10)
project(AmateLite)

# コンパイラ設定（MinGW-w64 使用）
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# OpenCV の Windows ビルド済みディレクトリを設定
# ↓パスは状況に応じて微調整してね！
set(OpenCV_DIR "/home/pakchi/projects/component/opencv/build")

# OpenCVを探す
find_package(OpenCV REQUIRED)

# ソースを追加
add_executable(denoise src/denoise.cpp)

# OpenCVリンク
target_link_libraries(denoise ${OpenCV_LIBS})

add_executable(analyze_main
    src/analyze_main.cpp
    src/analyzer.cpp
    src/auto_adjust.cpp
)

target_include_directories(analyze_main PRIVATE src)

target_link_libraries(analyze_main
    opencv_world
)
