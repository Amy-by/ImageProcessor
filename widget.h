#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>  // 引入OpenCV头文件

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // 按钮点击事件
    void on_loadBtn_clicked();      // 加载图片按钮
    void on_grayBtn_clicked();      // 灰度化按钮
    void on_blurBtn_clicked();      // 高斯模糊按钮
    // 滑块滑动事件
    void on_brightnessChanged(int value);  // 亮度调节
    void on_contrastChanged(int value);    // 对比度调节

private:
    Ui::Widget *ui;
    cv::Mat srcImg;  // 存储原始图像
    cv::Mat currImg; // 存储当前处理的图像
    void showImage(cv::Mat &img);  // 显示图像到界面的函数
};
#endif // WIDGET_H
