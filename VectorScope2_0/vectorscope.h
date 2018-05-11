#ifndef VECTORSCOPE_H
#define VECTORSCOPE_H

#include <QImage>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QVector>
#include <QVector3D>
#include <qmath.h>

namespace ColorMode {
    const int HsvColorMode = 0;
    const int QtHsvColorMode = 1;
    const int YCbCrMode = 2;
}

class VectorScope : protected QOpenGLFunctions
{
public:
    VectorScope(QImage *image);
    ~VectorScope();
    void processImage(QImage *image, int mode);
    void clearImage();
    void reload(QOpenGLShaderProgram *program);

    void initialize(QOpenGLShaderProgram *program);
    void draw();
    void update();

private:
    bool QtHsvColorProcess(QColor color, QVector3D& point);
    void HsvColorProcess(QColor color, QVector3D& point);
    QVector3D RgbToHsv(float r, float g, float b);

    QOpenGLBuffer vbo[2];
    QOpenGLVertexArrayObject vao;
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
};

#endif // VECTORSCOPE_H
