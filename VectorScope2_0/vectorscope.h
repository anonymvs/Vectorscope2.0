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

#include "oglobject.h"

namespace ColorMode {
    const int HsvColorMode = 0;
    const int QtHsvColorMode = 1;
    const int YCbCrMode = 2;
}

class VectorScope : public OglObject
{
public:
    VectorScope(QImage *image);
    ~VectorScope();

    void setGamma(float gamma);
    void setColored(int b);

    void processImage(QImage *image, int mode);
    void clearImage();

    void update() override;
    void draw(QOpenGLShaderProgram *program) override;

private:
    bool qtHsvColorProcess(QColor color, QVector3D& point);
    void hsvColorProcess(QColor color, QVector3D& point);
    float gammaCorrection(float v);
    QVector3D rgbToHsv(float r, float g, float b);

    bool isColored = true;
    float gamma = 1;
    float C = 1; //set by the monitor contrast value, by default is 1
};

#endif // VECTORSCOPE_H
