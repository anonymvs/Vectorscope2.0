#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <vectorscope.h>
#include <marker.h>
#include "skintoneline.h"
#include "targetbox.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QMatrix4x4>
#include <GL/GLU.h>
#include <GL/GL.h>

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OGLWidget(QWidget *parent);
    void loadScope(OglObject *scope);
    void setZoom(float zoom);
    ~OGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected slots:
    void update();

private:
    QOpenGLShaderProgram *program;
//    QMatrix4x4 matrix;
//    int u_matrix;
    int w;
    int h;

    OglObject *scope;
    OglObject *marker;
    OglObject *toneLine;
    QVector<OglObject*> targetMarkers;
};

#endif // OGLWIDGET_H
