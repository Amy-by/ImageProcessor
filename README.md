# ImageProcessor - 图像实时处理工具  

## 项目介绍  
基于 **Qt 6** 和 **OpenCV 4** 开发的桌面图像处理器，支持 **实时交互调节** 和 **一键滤镜处理**，适合快速调试图片效果。核心功能：  
- 🖼️ 本地图片加载（JPG/PNG 格式）  
- 🌗 实时调节 **亮度**（0-200 范围）、**对比度**（0-200 范围）  
- 🎨 一键切换 **灰度化**、**高斯模糊** 滤镜  
- 🔍 界面实时预览处理结果  


## 环境依赖  
### 1. 必须安装  
| 依赖项       | 安装方式                                                                 |  
|--------------|--------------------------------------------------------------------------|  
| **Qt 6**     | 通过 [Qt Online Installer](https://www.qt.io/download) 安装（含 Qt Creator） |  
| **OpenCV 4** | - Windows：[官网下载](https://opencv.org/releases/) 并配置环境变量         <br>- Ubuntu：`sudo apt install libopencv-dev`                 |  


## 编译与运行  
### 方式1：Qt Creator（推荐）  
1. 打开 Qt Creator → 点击 **File → Open File or Project** → 选择项目根目录的 `ImageProcessor.pro`。  
2. 左侧 **Projects** 面板 → 确认构建工具为 `qmake`（默认即可）。  
3. 点击左下角 **🔨 构建** → 构建完成后点击 **▶️ 运行**。  


### 方式2：命令行编译（Linux/Mac/Windows）  
```bash
# 1. 进入项目目录  
cd /path/to/ImageProcessor  

# 2. 生成 Makefile（Qt 6 环境）  
qmake ImageProcessor.pro  

# 3. 编译（-j4 加速，按需调整线程数）  
make -j4  

# 4. 运行程序  
./ImageProcessor  # Linux/Mac  
ImageProcessor.exe  # Windows（位于 build/release 目录）  
```  


## 使用指南  
### 1. 加载图片  
点击 **「加载图片」** 按钮，选择本地 JPG/PNG 图片，图片会自动适配界面显示。  


### 2. 调节参数  
| 控件          | 功能说明                                  | 操作逻辑                     |  
|---------------|-------------------------------------------|------------------------------|  
| **亮度滑块**  | 调整图像亮度                              | 100 = 原始亮度，<100 变暗、>100 变亮 |  
| **对比度滑块**| 调整图像对比度                            | 100 = 原始对比度，<100 降低、>100 增强 |  


### 3. 滤镜效果  
| 按钮          | 效果说明                                  |  
|---------------|-------------------------------------------|  
| **灰度化**    | 将彩色图像转为黑白模式                    |  
| **高斯模糊**  | 应用 15×15 核的高斯模糊，使图像柔和化      |  


## 常见问题  
### 1. 编译报错 `opencv2/opencv.hpp: No such file or directory`  
→ 解决方案：修改 `ImageProcessor.pro`，指定 OpenCV 路径：  
```pro
# Windows 示例（替换为你的 OpenCV 路径）  
INCLUDEPATH += C:/opencv/build/include  
LIBS += -LC:/opencv/build/x64/vc15/lib -lopencv_core480 -lopencv_imgproc480 -lopencv_imgcodecs480  

# Ubuntu 示例（若通过 apt 安装，通常无需修改）  
INCLUDEPATH += /usr/include/opencv4  
LIBS += -lopencv_core -lopencv_imgproc -lopencv_imgcodecs  
```  


### 2. 运行时无图片显示/操作无响应  
→ 检查：  
- 是否已加载图片（必须先点击「加载图片」）；  
- 图片路径是否含中文（建议放英文路径）。  


## 扩展建议  
- ✨ **新增滤镜**：在 `Widget.cpp` 中添加 OpenCV 算法（如 `cv::Canny` 边缘检测、`cv::applyColorMap` 伪彩色）。  
- 📥 **图片保存**：通过 `cv::imwrite` 实现，搭配 `QFileDialog` 让用户选择保存路径。  
- 🎛️ **更多参数**：扩展滑块（如模糊半径、灰度阈值），丰富调节功能。  


欢迎提交 PR 或 Issue 参与改进！ 🚀  
（项目地址：[https://github.com/Amy-by/ImageProcessor](https://github.com/Amy-by/ImageProcessor)）
