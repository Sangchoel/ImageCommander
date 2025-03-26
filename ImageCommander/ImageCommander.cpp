#include "ImageCommander.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QDebug>

ImageCommander::ImageCommander(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageCommanderClass)
{
    ui->setupUi(this);
    this->resize(1000, 700);

    connect(ui->btnOpen, &QPushButton::clicked, this, &ImageCommander::openImage);
    connect(ui->btnGray, &QPushButton::clicked, this, &ImageCommander::on_btnGray_clicked);
    connect(ui->btnBlur, &QPushButton::clicked, this, &ImageCommander::on_btnBlur_clicked);
    connect(ui->btnEdge, &QPushButton::clicked, this, &ImageCommander::on_btnEdge_clicked);
    connect(ui->btnOriginal, &QPushButton::clicked, this, &ImageCommander::on_btnOringinal_clicked);

}

ImageCommander::~ImageCommander()
{
    delete ui;
}

void ImageCommander::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");

    if (fileName.isEmpty()) {
        ui->logText->append("[Info] Image selection canceled.");
        return;
    }

    originalImage = cv::imread(fileName.toStdString());

    if (originalImage.empty()) {
        ui->logText->append("[Error] Failed to load image.");
        return;
    }

    updateLabelWithMat(originalImage);
    ui->logText->append("[OK] Image loaded.");
}

void ImageCommander::updateLabelWithMat(const cv::Mat& mat)
{
    cv::Mat rgb;
    if (mat.channels() == 1)
        cv::cvtColor(mat, rgb, cv::COLOR_GRAY2RGB);
    else
        cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);

    QImage qimg(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    ui->labelImage->setPixmap(QPixmap::fromImage(qimg).scaled(
        ui->labelImage->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
}

void ImageCommander::on_btnGray_clicked()
{
    if (originalImage.empty()) return;

    cv::Mat gray;
    cv::cvtColor(originalImage, gray, cv::COLOR_BGR2GRAY);
    updateLabelWithMat(gray);
    ui->logText->append("[OK] Grayscale applied.");
}

void ImageCommander::on_btnBlur_clicked()
{
    if (originalImage.empty()) return;

    cv::Mat blur;
    cv::GaussianBlur(originalImage, blur, cv::Size(7, 7), 1.5);
    updateLabelWithMat(blur);
    ui->logText->append("[OK] Blur applied.");
}

void ImageCommander::on_btnEdge_clicked()
{
    if (originalImage.empty()) return;

    cv::Mat gray, edge;
    cv::cvtColor(originalImage, gray, cv::COLOR_BGR2GRAY);
    cv::Canny(gray, edge, 50, 150);
    updateLabelWithMat(edge);
    ui->logText->append("[OK] Edge detection applied.");
}

void ImageCommander::on_btnOringinal_clicked()
{
    if (originalImage.empty()) return;
    updateLabelWithMat(originalImage);
    ui->logText->append("[OK] Original image restored.");

}
