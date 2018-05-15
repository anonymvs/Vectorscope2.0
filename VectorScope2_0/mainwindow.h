#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "vectorscope.h"
#include "oglobject.h"

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

    void on_vs_gamma_slider_valueChanged(int value);

    void on_vs_zoom_slider_valueChanged(int value);

    void on_chb_colored_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QImage *image;
    VectorScope* vs;
    int width, height;
};

#endif // MAINWINDOW_H
