#ifndef MARKER_H
#define MARKER_H

#include "oglobject.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QVector>
#include <QVector3D>
#include <qmath.h>

class Marker : public OglObject
{
public:
    Marker();
    ~Marker();

    void update() override;
    void draw(QOpenGLShaderProgram *program) override;
};

#endif // MARKER_H
