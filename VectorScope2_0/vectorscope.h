#ifndef VECTORSCOPE_H
#define VECTORSCOPE_H

#include <QImage>
#include <QVector>
#include <QVector3D>
#include <qmath.h>

class VectorScope
{
public:
    VectorScope();
    void processImage(QImage *image);
    QVector<QVector3D>& getVertices();
    QVector<QVector3D>& getColors();

private:
    QVector3D processPixel(QColor color);
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
};

#endif // VECTORSCOPE_H
