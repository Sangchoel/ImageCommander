#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageCommander.h"
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageCommanderClass; }
QT_END_NAMESPACE

class ImageCommander : public QMainWindow
{
    Q_OBJECT

public:
    ImageCommander(QWidget* parent = nullptr);
    ~ImageCommander();

private:
    Ui::ImageCommanderClass* ui;
    cv::Mat originalImage;

    void updateLabelWithMat(const cv::Mat& mat);

private slots:
    void openImage();
    void on_btnGray_clicked();
    void on_btnBlur_clicked();
    void on_btnEdge_clicked();
    void on_btnOringinal_clicked();
};
