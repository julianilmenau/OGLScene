#ifndef FLOOR_H
#define FLOOR_H

#include <res/drawable/header/abstractDrawable.h>


class Floor : public AbstractDrawable
{
public:
    Floor(int gwidth, int gheight);
    void initialize(QOpenGLShaderProgram *program);
    void draw(GLenum mode, QOpenGLFunctions &functions);
    void draw(QOpenGLFunctions &functions);
protected:
    void genGrid();
    int width,height;
    QVector<QVector<float>> grid;
};

#endif // FLOOR_H
