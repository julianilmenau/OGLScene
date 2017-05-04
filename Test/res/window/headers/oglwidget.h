#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QtCore/QCoreApplication>

#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QTimer>
#include "res/drawable/header/skybox.h"
#include "res/drawable/header/unitcube.h"
#include "res/drawable/header/floor.h"

#include "res/util/camera.h"




class OGLWidget : public QOpenGLWidget , protected QOpenGLFunctions
{
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

protected:


    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    QOpenGLShaderProgram * m_skyProgram;
    QOpenGLShaderProgram * m_cubeProgram;
    QOpenGLShaderProgram * m_floorProgram;


    Camera *camera;
    SkyBox m_sky;
    UnitCube m_cube;
    Floor *m_floor;



    void OGLWidget::processKeys();

public slots:
    void update();

};

#endif // OGLWIDGET_H
