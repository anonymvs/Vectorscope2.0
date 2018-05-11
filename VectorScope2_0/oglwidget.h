#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <vectorscope.h>

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShader>
#include <QMatrix4x4>
#include <GL/GLU.h>
#include <GL/GL.h>

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OGLWidget(QWidget *parent);
    void loadScope(VectorScope *scope);
    ~OGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected slots:
    void update();

private:
    QOpenGLBuffer vbo[2];
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram *program;
    QMatrix4x4 matrix;
    int u_matrix;
    int w;
    int h;

    VectorScope *scope;
};

#endif // OGLWIDGET_H
