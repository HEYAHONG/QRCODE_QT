#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <windows.h>
#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage MatToQImage(cv::Mat mat);

private:
    Ui::MainWindow *ui;
    QFileDialog *fileDialog;
    cv::QRCodeDetector *qrcode;
    cv::VideoCapture *cap;
    QTimer *VideoTimer;


public slots:
    void Execute();
    void OpenFile();
    void VideoTimerRun();
    void OpenCap();
};

#endif // MAINWINDOW_H
