#ifndef TARGETBOX_H
#define TARGETBOX_H

#include "oglobject.h"

class TargetBox : public OglObject
{
public:
    TargetBox(int angle);
    ~TargetBox();

    // OglObject interface
    void draw(QOpenGLShaderProgram *program) override;
    void update() override;

private:
    int angle;
};

#endif // TARGETBOX_H
