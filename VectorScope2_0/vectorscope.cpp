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

}

VectorScope::~VectorScope() {
    vbo[0].destroy();
    vbo[1].destroy();
    vao.destroy();
}

void VectorScope::processImage(QImage *image, int mode)
{
//    QImage im;
//    if(image->size().height() > 1080 || image->size().width() > 1920 ) {
//        im = image->scaled(1080, 1920, Qt::KeepAspectRatio);
//    }
    switch (mode) {
    case ColorMode::HsvColorMode:
        qDebug() << "hsvcolormode " << ColorMode::HsvColorMode;
        break;
    case ColorMode::QtHsvColorMode:
        qDebug() << "QThsvcolormode " << ColorMode::QtHsvColorMode;
        break;
    case ColorMode::YCbCrMode:
        qDebug() << "yyfdfs " << ColorMode::YCbCrMode;
        break;
    default:
        break;
    }

    if(!vertices.isEmpty() && !colors.isEmpty()) {
        vertices.clear();
        colors.clear();
    }
    for(int i = 0; i < image->size().height(); i++) {
        for(int j = 0; j < image->size().width(); j++) {
            QColor color = image->pixelColor(j, i);
            QVector3D point;
            switch (mode) {
            case ColorMode::HsvColorMode:
                HsvColorProcess(color, point);
                vertices.push_back(point);
                colors.push_back(QVector3D(color.redF(), color.greenF(), color.blueF()));
                break;
            case ColorMode::QtHsvColorMode:
                if(QtHsvColorProcess(color, point)) {
                    RgbToHsv(color.redF(), color.greenF(), color.blueF());
                    vertices.push_back(point);
                    colors.push_back(QVector3D(color.redF(), color.greenF(), color.blueF()));
                }
                break;
            case ColorMode::YCbCrMode:
                break;
            default:
                break;
            }

        }
    }
//    for(int j = 0; j < 360; j++) {
//        vertices.push_back(QVector3D(255 * qSin(qDegreesToRadians((float)j)), 255 * qCos(qDegreesToRadians((float)j)),0));
//        vertices.push_back(QVector3D(0,0,0));
//    }
}

bool VectorScope::QtHsvColorProcess(QColor color, QVector3D& point)
{  
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

void VectorScope::HsvColorProcess(QColor color, QVector3D &point)
{
    QVector3D hsv = RgbToHsv(color.redF(), color.greenF(), color.blueF());
    point.setX(hsv.y() * 255 * qSin(qDegreesToRadians(360 - qRadiansToDegrees(hsv.x()))));
    point.setY(hsv.y() * 255 * qCos(qDegreesToRadians(360 - qRadiansToDegrees(hsv.x()))));
    point.setZ(0);
    return;
}

QVector3D VectorScope::RgbToHsv(float r, float g, float b)
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

    if(v == 0) {
        s = 0;
    } else {
        s = c / v;
    }

   // qDebug() << "hue: " << qRadiansToDegrees(h) << "sat: " << s;
    return QVector3D(h, s, v);
}

void VectorScope::reload(QOpenGLShaderProgram *program)
{
    vbo[0].bind();
    vbo[0].allocate(vertices.constData(), vertices.size() * sizeof(QVector3D));
    vbo[0].release();

    vbo[1].bind();
    vbo[1].allocate(colors.constData(), colors.size() * sizeof(QVector3D));
    vbo[1].release();

}

void VectorScope::initialize(QOpenGLShaderProgram *program)
{
    initializeOpenGLFunctions();

    vbo[0].create();
    vbo[0].bind();
    vbo[0].setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo[0].allocate(vertices.constData(), vertices.size() * sizeof(QVector3D));
    vbo[0].release();

    vbo[1].create();
    vbo[1].bind();
    vbo[1].setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo[1].allocate(colors.constData(), colors.size() * sizeof(QVector3D));
    vbo[1].release();

    vao.create();
    vao.bind();

    vbo[0].bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
    vbo[0].release();
    vbo[1].bind();
    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, 0, 3, 0);
    vbo[0].release();

    vao.release();
}

void VectorScope::draw()
{

    vao.bind();
    glDrawArrays(GL_POINTS, 0, vertices.size());
    vao.release();
}

void VectorScope::clearImage()
{
    vertices.clear();
    colors.clear();
}
