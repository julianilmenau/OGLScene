#ifndef UNITCUBE_H
#define UNITCUBE_H




#include <unordered_map>
#include <array>
#include <vector>
#include <res/drawable/header/abstractDrawable.h>


class UnitCube : public AbstractDrawable
{
public:
    using Face = std::array<GLuint, 3>;

    static std::array<QVector3D, 8> vertices();
    static std::array<Face, 12> indices(); /// individual triangle indices (no strip, no fan)

    UnitCube();
    ~UnitCube();



    void initialize(QOpenGLShaderProgram *program);
    void draw(QOpenGLFunctions & functions);
    void draw(GLenum mode, QOpenGLFunctions & functions);

protected:

};

#endif // UNITCUBE_H

