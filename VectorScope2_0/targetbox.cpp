#include "targetbox.h"

TargetBox::TargetBox(int angle) : angle{angle}
{
    zoom = 0;
    float r = 0.75 * 255;
    float curv = 5.0;
    float d = 15.0;
    vertices.push_back(QVector3D(
                           (r - d) * qSin(qDegreesToRadians(curv)),
                           (r - d) * qCos(qDegreesToRadians(curv)),
                           0
    ));
    colors.push_back(QVector3D(1, 1, 1));
    vertices.push_back(QVector3D(
                           (r + d) * qSin(qDegreesToRadians(curv)),
                           (r + d) * qCos(qDegreesToRadians(curv)),
                           0
    ));
    colors.push_back(QVector3D(1, 1, 1));
    vertices.push_back(QVector3D(
                           (r + d) * qSin(qDegreesToRadians(-curv)),
                           (r + d) * qCos(qDegreesToRadians(-curv)),
                           0
    ));
    colors.push_back(QVector3D(1, 1, 1));
    vertices.push_back(QVector3D(
                           (r - d) * qSin(qDegreesToRadians(-curv)),
                           (r - d) * qCos(qDegreesToRadians(-curv)),
                           0
    ));
    colors.push_back(QVector3D(1, 1, 1));
    vertices.push_back(QVector3D(
                           (r - d) * qSin(qDegreesToRadians(curv)),
                           (r - d) * qCos(qDegreesToRadians(curv)),
                           0
    ));
    colors.push_back(QVector3D(1, 1, 1));
}

TargetBox::~TargetBox()
{
    vbo[0].destroy();
    vbo[1].destroy();
    vao.destroy();
}

void TargetBox::draw(QOpenGLShaderProgram *program)
{
    program->setUniformValue(u_matrix, matrix);
    vao.bind();
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    vao.release();
}

void TargetBox::update()
{
    matrix.setToIdentity();
    matrix.scale(0.003 + zoom);
    matrix.rotate(-14 + angle, QVector3D(0,0,1));
}
