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
    marker = new Marker();
    toneLine = new SkinToneLine();
    for(int i = 0; i < 6; i++) {
        targetMarkers.push_back(new TargetBox(i * 60));
    }
}

void OGLWidget::loadScope(OglObject *scope)
{
    if(this->scope != nullptr) {
        this->scope->reload();
        QOpenGLWidget::update();
    } else {
        this->scope = scope;
    }
}

void OGLWidget::setZoom(float zoom)
{
    scope->setZoom(zoom);
    marker->setZoom(zoom);
    toneLine->setZoom(zoom);
    foreach (auto* target, targetMarkers) {
        target->setZoom(zoom);
    }
}

OGLWidget::~OGLWidget() {
    delete scope;
    delete marker;
    delete program;
    delete toneLine;
    foreach (auto* target, targetMarkers) {
        delete target;
    }
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

    scope->initialize(program);
    marker->initialize(program);
    toneLine->initialize(program);
    foreach (auto* target, targetMarkers) {
        target->initialize(program);
    }

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
    scope->draw(program);
    marker->draw(program);
    toneLine->draw(program);
    foreach (auto* target, targetMarkers) {
        target->draw(program);
    }
    program->release();

}

void OGLWidget::update()
{
    marker->update();
    scope->update();
    toneLine->update();
    foreach (auto* target, targetMarkers) {
        target->update();
    }
    QOpenGLWidget::update();
}
