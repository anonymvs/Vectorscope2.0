#include "skintoneline.h"

SkinToneLine::SkinToneLine()
{
    zoom = 0;
    vertices.push_back(QVector3D(0, 270, 0));
    colors.push_back(QVector3D(1, 1, 1));
    vertices.push_back(QVector3D(0, -270, 0));
    colors.push_back(QVector3D(1, 1, 1));
}

SkinToneLine::~SkinToneLine()
{
    vbo[0].destroy();
    vbo[1].destroy();
    vao.destroy();
}

void SkinToneLine::draw(QOpenGLShaderProgram *program)
{
    program->setUniformValue(u_matrix, matrix);
    vao.bind();
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    vao.release();
}

void SkinToneLine::update()
{
    matrix.setToIdentity();
    matrix.scale(0.003 + zoom);
    matrix.rotate(-33, QVector3D(0,0,1));
}
