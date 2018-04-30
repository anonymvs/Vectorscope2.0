#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clock_t t = clock();

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

    image = new QImage();
    QString path = "C:/Users/anonymvs/Documents/VectorScope";
    path.append("/marine.jpg");
    //path.append("/colorbar.jpg");
    image->load(path);

    vs.processImage(image);

    ui->openGLWidget->loadVertices(vs.getVertices(), vs.getColors());
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

    clock_t t = clock();
    vs.processImage(image);
    ui->openGLWidget->loadVertices(vs.getVertices(), vs.getColors());
    clock_t t2 = clock();

    QString str = "time in ms: ";
    float dt = (float) t2 - t;
    str += QString::number(dt / CLOCKS_PER_SEC * 1000);
    ui->l_time->setText(str);
}

void MainWindow::on_pb_show_image_clicked()
{

}
