#include "vectorscope.h"

VectorScope::VectorScope()
{

}

void VectorScope::processImage(QImage *image)
{
    for(int i = 0; i < image->size().height(); i++) {
        for(int j = 0; j < image->size().width(); j++) {
            QColor color = image->pixelColor(j, i);
            QVector3D cv(color.redF(), color.greenF(), color.blueF());
            vertices.push_back(processPixel(color));
            colors.push_back(cv);
        }
    }
}

QVector<QVector3D> &VectorScope::getVertices()
{
    return vertices;
}

QVector<QVector3D> &VectorScope::getColors()
{
    return colors;
}

QVector3D VectorScope::processPixel(QColor color)
{
    // form online source i figured the rotation of the colorwheel used in vectorscopes
    // is the following:
    // if 0 degree is around blue, red should be at 256 degree,
    // my calculations by default put red at the bottom. 256 - 90 = 166 degree
    // which i used turn the circle
    double hue = 360 - color.hueF() * 360;
    double sat = color.saturationF() * 255;
    return QVector3D(sat * qSin(qDegreesToRadians(hue)), sat * qCos(qDegreesToRadians(hue)), 0);
}
