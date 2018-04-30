#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <vectorscope.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_load_image_clicked();

    void on_pb_show_image_clicked();

private:
    Ui::MainWindow *ui;
    QImage *image;
    VectorScope vs;
};

#endif // MAINWINDOW_H
