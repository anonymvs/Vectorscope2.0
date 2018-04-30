#ifndef OGLWIDGET_H
#define OGLWIDGET_H

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
    void loadVertices(QVector<QVector3D>& vertices, QVector<QVector3D>& colors);
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
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
    QMatrix4x4 matrix;
    int u_matrix;
    int w;
    int h;
};

static const char *vertexShaderSource = R"(
    #version 330
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 color;
    out vec4 vColor;

    uniform mat4 matrix;

    void main(void)
    {
        gl_Position = vec4(position, 1) * matrix;
        vColor = vec4(color, 1);
    }
)";

static const char *fragmentShaderSource = R"(
      #version 330
      in vec4 vColor;
      out vec4 fColor;

      void main(void)
      {
          gl_FragColor = vColor;
      }

)";

#endif // OGLWIDGET_H
