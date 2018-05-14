#ifndef OGLOBJECT_H
#define OGLOBJECT_H

#include <QImage>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QVector>
#include <QVector3D>
#include <qmath.h>

class OglObject : protected QOpenGLFunctions
{
public:
    OglObject();
    virtual ~OglObject() {}

    void setZoom(float zoom);

    void initialize(QOpenGLShaderProgram *program);
    virtual void draw(QOpenGLShaderProgram *program) = 0;
    virtual void update() = 0;
    void reload();

protected:
    QOpenGLBuffer vbo[2];
    QOpenGLVertexArrayObject vao;
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;

    float zoom;

    QMatrix4x4 matrix;
    int u_matrix;
};

#endif // OGLOBJECT_H
