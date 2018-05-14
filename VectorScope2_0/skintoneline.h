#ifndef SKINTONELINE_H
#define SKINTONELINE_H

#include "oglobject.h"

class SkinToneLine : public OglObject
{
public:
    SkinToneLine();
    ~SkinToneLine();

    // OglObject interface
    void draw(QOpenGLShaderProgram *program) override;
    void update() override;
};

#endif // SKINTONELINE_H
