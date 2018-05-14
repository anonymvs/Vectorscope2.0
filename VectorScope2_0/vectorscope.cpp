#include "vectorscope.h"


VectorScope::VectorScope(QImage *image)
{
//    QVector3D q1 = RgbToHsv(0.255, 0.104, 0.918);
//    QVector3D q2 =RgbToHsv(0.75, 0.75, 0.0);
//    QVector3D q3 =RgbToHsv(0.0, 0.5, 0.0);
//    QVector3D q4 = RgbToHsv(0.5, 1.0, 1.0);
//    QVector3D q5 = RgbToHsv(0.0, 1.0, 0.0);
//    QVector3D q6 = RgbToHsv(0.0, 0.0, 1.0);
    processImage(image, ColorMode::HsvColorMode);
    zoom = 0;
}

VectorScope::~VectorScope()
{
    vbo[0].destroy();
    vbo[1].destroy();
    vao.destroy();
}

void VectorScope::setGamma(float gamma)
{
    this->gamma = gamma;
}

void VectorScope::setColored(int b)
{
    isColored = b;
}

void VectorScope::processImage(QImage *image, int mode)
{
//    QImage im;
//    if(image->size().height() > 1080 || image->size().width() > 1920 ) {
//        im = image->scaled(1080, 1920, Qt::KeepAspectRatio);
//    }

    if(!vertices.isEmpty() && !colors.isEmpty()) {
        vertices.clear();
        colors.clear();
    }

    for(int i = 0; i < image->size().height(); i++) {
        for(int j = 0; j < image->size().width(); j++) {
            QColor color = image->pixelColor(j, i);
            QVector3D point;
            if(mode == ColorMode::HsvColorMode) {
                hsvColorProcess(color, point);
                vertices.push_back(point);
                if(isColored)
                    colors.push_back(QVector3D(color.redF(), color.greenF(), color.blueF()));
                else
                    colors.push_back(QVector3D(1,1,1));
            }
            if(mode == ColorMode::QtHsvColorMode) {
                if(qtHsvColorProcess(color, point)) {
                    rgbToHsv(color.redF(), color.greenF(), color.blueF());
                    vertices.push_back(point);
                    if(isColored)
                        colors.push_back(QVector3D(color.redF(), color.greenF(), color.blueF()));
                    else
                        colors.push_back(QVector3D(1,1,1));
                }
            }
            if(mode == ColorMode::YCbCrMode) {

            }
        }
    }
}

bool VectorScope::qtHsvColorProcess(QColor color, QVector3D& point)
{  
    color.setRedF(gammaCorrection(color.redF()));
    color.setGreenF(gammaCorrection(color.greenF()));
    color.setBlueF(gammaCorrection(color.blueF()));
    double hue = 360 - color.hsvHueF() * 360;
    double sat = color.hsvSaturationF() * 255;

    //qDebug() << "qt : h | s | v  <--->" <<  color.hsvHueF() << color.hsvSaturationF() << color.valueF();
    if(hue < 0 || hue > 360 || sat < 0 || sat > 255) {
        return false;
    }

    point.setX(sat * qSin(qDegreesToRadians(hue)));
    point.setY(sat * qCos(qDegreesToRadians(hue)));
    point.setZ(0);
    return true;
}

void VectorScope::hsvColorProcess(QColor color, QVector3D &point)
{
    QVector3D hsv = rgbToHsv(color.redF(), color.greenF(), color.blueF());
    point.setX(hsv.y() * 255 * qSin(2 * M_PI - hsv.x()));
    point.setY(hsv.y() * 255 * qCos(2 * M_PI - hsv.x()));
    point.setZ(0);
    return;
}

float VectorScope::gammaCorrection(float v)
{
    //gamma = 0.5;
    return C * qPow(v, gamma);
}

QVector3D VectorScope::rgbToHsv(float r, float g, float b)
{
//    float h, s, v;
//    float max = qMax(r, qMax(g, b));
//    float min = qMin(r, qMin(g, b));
//    float delta = max - min;
//    v = max;
//    if(max != 0.0) {
//        s = delta / max;
//    } else {
//        s = 0.0;
//    }
//    if(s == 0.0) {
//        h = -1;
//    } else {
//        if(r == max) {
//            h = (g - b) / delta;
//        } else if(g == max) {
//            h = 2 + (b - r) / delta;
//        } else if(b == max) {
//            h = 4 + (r - g) / delta;
//            h *= 60.0;
//            if(h < 0)
//                h += 360.0;
//            h /= 360.0;
//        }
//    }

//    qDebug() << "my : h | s | v  <--->" << h << s << v;
//    return QVector3D(h, s, v);

    //Return hue in radians
    float h, s, v; // hue, saturation, value
    float alpha = 0.5 * (2 * r - g - b);
    float beta = qSqrt(3) / 2 * (g - b);
    h = qAtan2(beta, alpha);
    float c = qSqrt(qPow(alpha, 2) + qPow(beta, 2)); //chroma

    v = qMax(r, qMax(g, b));
    v = gammaCorrection(v);

    if(v == 0) {
        s = 0;
    } else {
        s = c / v;
    }

   // qDebug() << "hue: " << qRadiansToDegrees(h) << "sat: " << s;
    return QVector3D(h, s, v);
}

void VectorScope::clearImage()
{
    vertices.clear();
    colors.clear();
}

void VectorScope::update()
{
    matrix.setToIdentity();
    matrix.scale(0.003 + zoom);
    matrix.rotate(-14, QVector3D(0,0,1));
}

void VectorScope::draw(QOpenGLShaderProgram *program)
{

    program->setUniformValue(u_matrix, matrix);
    vao.bind();
    glDrawArrays(GL_POINTS, 0, vertices.size());
    vao.release();
}
