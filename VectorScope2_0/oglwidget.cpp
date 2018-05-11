#include "oglwidget.h"
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QGLFormat>

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    //setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    h = this->parentWidget()->size().height();
    w = this->parentWidget()->size().height();
    scope = nullptr;
}

void OGLWidget::loadScope(VectorScope *scope)
{
    if(this->scope != nullptr) {
        this->scope->reload(program);
        QOpenGLWidget::update();
    } else {
        this->scope = scope;
    }
//    QOpenGLWidget::update();
}

OGLWidget::~OGLWidget() {
    delete scope;
    delete program;
}

void OGLWidget::initializeGL()
{
    //vertices << QVector3D(0.00f, 0.75f, 1.0f) << QVector3D( 0.75f, -0.75f, 1.0f) << QVector3D(-0.75f, -0.75f, 1.0f);

    //colors << QVector3D(1.0f, 0.0f, 0.0f) << QVector3D(0.0f, 1.0f, 0.0f) << QVector3D(0.0f, 0.0f, 1.0f);
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
