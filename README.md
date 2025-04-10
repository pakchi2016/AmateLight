# AmateLite(画質向上アプリ)開発計画
本プロジェクトは画像生成AIに読み込ませる画像を予め画質向上させておくことで、生成する画像の結果を向上させることを目的としている。

## 開発環境
Windows11のWSL上に構成したubuntuにインストールしたdocker上で開発を行う。

## 動作環境
Windowsネイティブ(動作確認はWindows11のみ)

## 機能
**以下機能で画質を向上**
- ノイズ除去
- アップスケーリング
- コントラスト調整
- シャープネス強調
- 色補正
- ガンマ補正

## 利用ライブラリ
- OpenCV

# マイルストーン
## マイルストーン1: 開発環境のセットアップ
- **WSLとUbuntuのセットアップ**: Windows 11上でWSLをインストールし、Ubuntuをセットアップ。
- **Dockerのインストール**: Dockerをインストールし、必要なコンテナを構築。

## マイルストーン2: 画像処理機能の実装 (C++)
- **OpenCVのインストール**:
  ```bash
  sudo apt update
  sudo apt install libopencv-dev
  ```
# 各画像処理機能の実装
- ノイズ除去 (`denoise.cpp`)
- アップスケーリング (`upscale.cpp`)
- コントラスト調整 (`contrast.cpp`)
- シャープネス強調 (`sharpen.cpp`)
- 色補正 (`color_correction.cpp`)
- ガンマ補正 (`gamma_correction.cpp`)

## マイルストーン3: GUI部分の実装 (Python)
- **GUIライブラリの選定とセットアップ**: TkinterやPyQtなどのライブラリを選定し、セットアップ。
- **画像取り込み機能の実装**: 画像を取り込んで表示する機能を実装。
- **パラメータ調整機能の実装**: スライダーを使って各パラメータを調整できるようにする。

## マイルストーン4: コンソールとGUIの連携
- **PythonからC++の呼び出し**: PythonからC++のコンソールプログラムを呼び出す仕組みを構築。
- **パラメータの転送と画像の受信**: パラメータを転送し、処理された画像を受信するプロトコルを設計。

## マイルストーン5: 統合とスタティックリンク
- **C++とPythonの統合**: C++コードをPythonバインディングとして公開し、統合。
- **スタティックリンクの準備**: CMakeを使用してスタティックライブラリをビルドし、Pythonコードをコンパイルして実行ファイルにリンク。

## マイルストーン6: テストとデバッグ
- **各機能のテスト**: 各機能が正しく動作するかテスト。
- **バグ修正とパフォーマンス最適化**: バグを修正し、パフォーマンスを最適化。

## マイルストーン7: ドキュメントとユーザーガイドの作成
- **使用方法のドキュメント作成**: 使用方法やインストール手順をまとめたドキュメントを作成。
- **ユーザーガイドの作成**: ユーザーガイドを作成し、使いやすさを向上。

## マイルストーン8: 最終リリースとメンテナンス
- **最終リリース**: 完成したアプリをリリース。
- **メンテナンス**: ユーザーからのフィードバックを元に改善を行う。
