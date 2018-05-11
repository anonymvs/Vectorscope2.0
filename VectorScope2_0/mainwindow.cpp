#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->l_gamma_value->setNum(((double)ui->vs_gamma_slider->value())/100);

    ui->comboBox->addItem("colorwheel");
    ui->comboBox->addItem("colorbar");
    ui->comboBox->addItem("mycolorbar");
    ui->comboBox->addItem("mycolorbar2");
    ui->comboBox->addItem("sanfr_townhall");
    ui->comboBox->addItem("marine");
    ui->comboBox->addItem("eper");
    ui->comboBox->addItem("test");
    ui->comboBox->addItem("woman");
    ui->comboBox->addItem("house");
    ui->comboBox->addItem("natalie");
    ui->comboBox->addItem("colorfulpencils");
    ui->comboBox->addItem("temple");

    ui->cb_color_mode->addItem("Hsv color hexa");
    ui->cb_color_mode->addItem("Hsv color circle");
    ui->cb_color_mode->addItem("YCbCr");

    //FreeImage-er
    //gamma-t kéne eltölögatni 2.2-re emelni az rgb-t vagy 1/2.2
    //logaritmikus skála akár
    //magyarázat jelzések
    //saját átállás fv
    image = new QImage();
    QString path = "C:/Users/anonymvs/Documents/VectorScope";
    path.append("/colorwheel.jpg");
    //path.append("/colorbar.jpg");
    image->load(path);
    QImage scaled = image->scaled(768, 1024, Qt::KeepAspectRatio);
    clock_t t = clock();
    vs = new VectorScope(&scaled);
    vs->setGamma(2 * ((float)ui->vs_gamma_slider->value() + 1) / 100);
    ui->openGLWidget->loadScope(vs);
    clock_t t2 = clock();

    QString str = "time in ms: ";
    float dt = (float) t2 - t;
    str += QString::number(dt / CLOCKS_PER_SEC * 1000);
    ui->l_time->setText(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_load_image_clicked()
{
    delete image;
    image = new QImage();
    QString path = "C:/Users/anonymvs/Documents/VectorScope";
    QString ct = ui->comboBox->currentText();
    path.append("/");
    path.append(ct);
    path.append(".jpg");
    //std::cout << path.data() << "\n";
    image->load(path);
    QImage scaled = image->scaled(600, 800, Qt::KeepAspectRatio);

    clock_t t = clock();
    if(ui->cb_color_mode->currentIndex() == 0) {
        vs->processImage(&scaled, ColorMode::HsvColorMode);
    }
    if(ui->cb_color_mode->currentIndex() == 1) {
        vs->processImage(&scaled, ColorMode::QtHsvColorMode);
    }
    if(ui->cb_color_mode->currentIndex() == 2) {
        vs->processImage(&scaled, ColorMode::YCbCrMode);
    }
    ui->openGLWidget->loadScope(nullptr);
    clock_t t2 = clock();

    QString str = "time in ms: ";
    float dt = (float) t2 - t;
    str += QString::number(dt / CLOCKS_PER_SEC * 1000);
    ui->l_time->setText(str);
}

void MainWindow::on_pb_show_image_clicked()
{

}

void MainWindow::on_vs_gamma_slider_valueChanged(int value)
{
    ui->l_gamma_value->setNum(((double)value)/100);
    vs->setGamma(((float)value + 1)/100);
}
