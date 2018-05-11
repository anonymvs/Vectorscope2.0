#include "oglwidget.h"
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QGLFormat>

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

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    h = this->parentWidget()->size().height();
    w = this->parentWidget()->size().height();
    scope = nullptr;
}

void OGLWidget::loadScope(VectorScope *scope)
{
    if(this->scope != nullptr) {
        this->scope->reload();
        QOpenGLWidget::update();
    } else {
        this->scope = scope;
    }
}

OGLWidget::~OGLWidget() {
    delete scope;
    delete program;
}

void OGLWidget::initializeGL()
{
    if(scope == nullptr) {
        return;
    }

    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();
    program->bind();

    u_matrix = program->uniformLocation("matrix");
    matrix.setToIdentity();

    scope->initialize(program);

    program->bindAttributeLocation("position", 0);
    program->bindAttributeLocation("color", 1);

    program->release();

}

void OGLWidget::resizeGL(int w, int h)
{
    this->h = h;
    this->w = w;
}

void OGLWidget::paintGL()
{
    if(w <= h) {
        h = w;
    } else {
        w = h;
    }
    glViewport(0, 0,w, h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->bind();
    program->setUniformValue(u_matrix, matrix);
    scope->draw();
    program->release();

}

void OGLWidget::update()
{
    matrix.setToIdentity();
    matrix.scale(0.003);
    matrix.rotate(-14, QVector3D(0,0,1));
    QOpenGLWidget::update();
}
