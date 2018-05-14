#include "oglobject.h"

OglObject::OglObject()
{

}

void OglObject::setZoom(float zoom)
{
    this->zoom = zoom / 1000;
}

void OglObject::initialize(QOpenGLShaderProgram *program)
{
    initializeOpenGLFunctions();

    u_matrix = program->uniformLocation("matrix");
    matrix.setToIdentity();

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

void OglObject::reload() {
    vbo[0].bind();
    vbo[0].allocate(vertices.constData(), vertices.size() * sizeof(QVector3D));
    vbo[0].release();

    vbo[1].bind();
    vbo[1].allocate(colors.constData(), colors.size() * sizeof(QVector3D));
    vbo[1].release();
}
