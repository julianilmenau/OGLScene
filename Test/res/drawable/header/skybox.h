#ifndef SKYBOX_H
#define SKYBOX_H




#include <unordered_map>
#include <array>
#include <vector>
#include <res/drawable/header/abstractDrawable.h>


class SkyBox : public AbstractDrawable
{
public:
    using Face = std::array<GLuint, 3>;

    static std::array<QVector3D, 8> vertices();
    static std::array<Face, 12> indices(); /// individual triangle indices (no strip, no fan)

    SkyBox();
    ~SkyBox();



    void initialize(QOpenGLShaderProgram *program);
    void draw(QOpenGLFunctions & functions);
    void draw(GLenum mode, QOpenGLFunctions & functions);

protected:

};

#endif // UNITCUBE_H

