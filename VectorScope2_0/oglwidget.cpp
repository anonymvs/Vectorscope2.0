#include "oglwidget.h"
#include <QOpenGLShaderProgram>
#include <QDebug>

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    h = this->parentWidget()->size().height();
    w = this->parentWidget()->size().height();
}

void OGLWidget::loadVertices(QVector<QVector3D>& vertices, QVector<QVector3D>& colors)
{
    this->vertices = vertices;
    this->colors = colors;

    QOpenGLWidget::update();
}

OGLWidget::~OGLWidget() {
    vao.destroy();
    vbo[0].destroy();
    vbo[1].destroy();
    delete program;
}

void OGLWidget::initializeGL()
{
    vertices << QVector3D(0.00f, 0.75f, 1.0f) << QVector3D( 0.75f, -0.75f, 1.0f) << QVector3D(-0.75f, -0.75f, 1.0f);

    colors << QVector3D(1.0f, 0.0f, 0.0f) << QVector3D(0.0f, 1.0f, 0.0f) << QVector3D(0.0f, 0.0f, 1.0f);

    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();
    program->bind();

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
    makeCurrent();

    //qDebug() << matrix;

    program->bind();
    vao.bind();
    program->setUniformValue(u_matrix, matrix);
    glDrawArrays(GL_POINTS, 0, vertices.size());
    vao.release();
    program->release();
}

void OGLWidget::update()
{
    matrix.setToIdentity();
    matrix.scale(0.003);
    matrix.rotate(-14, QVector3D(0,0,1));
    QOpenGLWidget::update();
}
