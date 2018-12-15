#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileDialog = new QFileDialog(this);
    VideoTimer=new QTimer;
    VideoTimer->start(100);
    qrcode=new cv::QRCodeDetector;
    cap=new cv::VideoCapture(0);
    setWindowTitle("QRCODE");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(OpenCap()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Execute()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(OpenFile()));
    connect(VideoTimer,SIGNAL(timeout()),this,SLOT(VideoTimerRun()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileDialog;
    delete qrcode;
    delete VideoTimer;
}
void MainWindow::Execute()
{
QString cmd;
cmd=ui->lineEdit_2->text();
if(cmd.length()>0)
{
    ShellExecute(NULL,L"open",(LPCWSTR)cmd.toStdWString().data(),NULL,NULL,SW_SHOWNORMAL);
}
}
void MainWindow::OpenFile()
{
  if(fileDialog->exec() == QDialog::Accepted)
  {
     QString path = fileDialog->selectedFiles()[0];
     ui->lineEdit->setText(path);
     cap->open(path.toStdString().data());
     if(!cap->isOpened())
     {
        QMessageBox::about(NULL, "警告", "打开视频失败！");

     }


  }

}
void MainWindow::OpenCap()
{
    QString num_s=ui->lineEdit->text();

    int num=atoi(num_s.toStdString().data());
    cap->open(num);

    if(!cap->isOpened())
    {
       QMessageBox::about(NULL, "警告", "打开摄像头失败！");

    }

}
void MainWindow::VideoTimerRun()
{
cv::Mat frame,Label_mat,src;
*cap >> frame;
if(frame.empty()) return;

cv::resize(frame,Label_mat,cv::Size(ui->label->width(),ui->label->height()));
ui->label->setPixmap(QPixmap::fromImage(MatToQImage(Label_mat)));
//ui->label->resize(ui->label->pixmap()->size());
ui->label->show();
{ //检测二维码
    std::string decode_info;
    std::vector<cv::Point> transformpoint;
    cv::cvtColor(frame, src, cv::COLOR_BGR2GRAY);
    if(qrcode->detect(src, transformpoint))
    {
      decode_info = qrcode->decode(src, transformpoint);
      if(!decode_info.empty()) ui->lineEdit_2->setText(QString::fromStdString(decode_info));
    }

}

}

QImage MainWindow::MatToQImage(cv::Mat mat)
{

static cv::Mat rgb;
QImage img;
if(mat.channels() == 3) // RGB image
{
cv::cvtColor(mat,rgb,CV_BGR2RGB);
img = QImage((const uchar*)(rgb.data), //(const unsigned char*)
rgb.cols,rgb.rows,
rgb.cols*rgb.channels(),
QImage::Format_RGB888);
}else if(mat.channels() ==1) // gray image
{
img = QImage((const uchar*)(mat.data),
mat.cols,mat.rows,
mat.cols*mat.channels(),
QImage::Format_Indexed8);
}
return img;

}
