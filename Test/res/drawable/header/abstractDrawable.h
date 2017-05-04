#ifndef ABSTRACTDRAWABLE_H
#define ABSTRACTDRAWABLE_H


#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QVector>



class AbstractDrawable
{
public:

    QMatrix4x4 getTransform();

    void setTransform(QMatrix4x4 matrix);

    virtual void initialize(QOpenGLShaderProgram *program)=0;
    virtual void draw(QOpenGLFunctions & functions)=0;
    virtual void draw(GLenum mode, QOpenGLFunctions & functions)=0;

protected:

    QOpenGLVertexArrayObject m_vao;

    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_colorBuffer;
    QOpenGLBuffer m_normalBuffer;
    QVector<QOpenGLTexture*> m_textures;

    QMatrix4x4 m_transform;
};

#endif

