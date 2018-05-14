#include "marker.h"

Marker::Marker()
{
    zoom = 0;
    for(int i = 0; i < 6; i++) {
        vertices.push_back(QVector3D(255 * qSin(0 + (i * M_PI / 3)), 255 * qCos(0 + (i * M_PI / 3)), 0));
    }
    colors.push_back(QVector3D(1,0,0));
    colors.push_back(QVector3D(1,0,1));
    colors.push_back(QVector3D(0,0,1));
    colors.push_back(QVector3D(0,1,1));
    colors.push_back(QVector3D(0,1,0));
    colors.push_back(QVector3D(1,1,0));
    vertices.push_back(vertices[0]);
    colors.push_back(colors[0]);
}

Marker::~Marker()
{
    vbo[0].destroy();
    vbo[1].destroy();
    vao.destroy();
}

void Marker::update()
{
    matrix.setToIdentity();
    matrix.scale(0.003 + zoom);
    matrix.rotate(-14, QVector3D(0,0,1));
}

void Marker::draw(QOpenGLShaderProgram *program)
{
    program->setUniformValue(u_matrix, matrix);
    vao.bind();
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    vao.release();
}


