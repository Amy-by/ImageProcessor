#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>   // 用于打开文件对话框
#include <QMessageBox>   // 用于弹出提示框

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 绑定滑块信号与槽函数（滑块动时触发调节函数）
    connect(ui->brightnessSlider, &QSlider::valueChanged,
            this, &Widget::on_brightnessChanged);
    connect(ui->contrastSlider, &QSlider::valueChanged,
            this, &Widget::on_contrastChanged);

    // 初始化滑块位置（中间值100，对应正常亮度/对比度）
    ui->brightnessSlider->setValue(100);
    ui->contrastSlider->setValue(100);
}

Widget::~Widget()
{
    delete ui;
}

// 加载图片按钮点击事件
void Widget::on_loadBtn_clicked()
{
    // 打开文件选择对话框，只允许选择jpg/png图片
    QString path = QFileDialog::getOpenFileName(
        this, "选择图片", "/home", "图片文件 (*.jpg *.png)"
    );

    if (path.isEmpty()) return;  // 没选图片就退出

    // 用OpenCV读取图片
    srcImg = cv::imread(path.toStdString());
    if (srcImg.empty()) {  // 读取失败
        QMessageBox::warning(this, "错误", "无法打开图片");
        return;
    }

    currImg = srcImg.clone();  // 复制原始图像到当前图像
    showImage(currImg);  // 显示图片
}

// 显示图像到界面的函数
void Widget::showImage(cv::Mat &img)
{
    // 转换OpenCV的BGR格式为Qt的RGB格式（解决颜色错乱问题）
    cv::Mat rgbImg;
    cv::cvtColor(img, rgbImg, cv::COLOR_BGR2RGB);

    // 转换为Qt能显示的QImage
    QImage qimg(
        rgbImg.data,          // 图像数据
        rgbImg.cols,          // 宽度
        rgbImg.rows,          // 高度
        rgbImg.cols * 3,      // 每行字节数
        QImage::Format_RGB888 // 格式
    );

    // 在Label上显示（自动缩放适应Label大小，保持比例）
    ui->imgLabel->setPixmap(QPixmap::fromImage(
        qimg.scaled(ui->imgLabel->width(), ui->imgLabel->height(), Qt::KeepAspectRatio)
    ));
}

// 亮度调节（滑块值变化时触发）
void Widget::on_brightnessChanged(int value)
{
    if (srcImg.empty()) return;  // 没加载图片就退出

    double brightness = (value - 100) / 50.0;  // 计算亮度偏移量（-2.0到2.0）
    srcImg.convertTo(currImg, -1, 1.0, brightness * 50);  // 应用亮度变化
    showImage(currImg);  // 显示变化后的图像
}

// 对比度调节（滑块值变化时触发）
void Widget::on_contrastChanged(int value)
{
    if (srcImg.empty()) return;  // 没加载图片就退出

    double contrast = value / 100.0;  // 计算对比度比例（0到2.0）
    srcImg.convertTo(currImg, -1, contrast, 0);  // 应用对比度变化
    showImage(currImg);  // 显示变化后的图像
}

// 灰度化按钮点击事件
void Widget::on_grayBtn_clicked()
{
    if (srcImg.empty()) return;  // 没加载图片就退出

    cv::cvtColor(srcImg, currImg, cv::COLOR_BGR2GRAY);  // 转为灰度图
    showImage(currImg);  // 显示灰度图
}

// 高斯模糊按钮点击事件
void Widget::on_blurBtn_clicked()
{
    if (srcImg.empty()) return;  // 没加载图片就退出

    cv::GaussianBlur(srcImg, currImg, cv::Size(15, 15), 0);  // 应用高斯模糊
    showImage(currImg);  // 显示模糊后的图像
}
