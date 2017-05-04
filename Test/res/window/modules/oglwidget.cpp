#include "res/window/headers/oglwidget.h"
#include "res/util/input.h"



OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
        camera = new Camera();

        camera->setFovy(40.0);
        camera->setCenter(QVector3D(0.0f, 0.0f, 0.0f));
        camera->setEye(QVector3D(0.0f, 0.5f, 4.0f));
        camera->setUp(QVector3D(0.0f, 1.0f, 0.0f));
        camera->setSpeedx(0.01f);
        camera->setSpeedz(0.01f);
        camera->setSpeedy(0.01f);
}

OGLWidget::~OGLWidget()
{

    //delete m_cubeProgram;
    delete camera;
}

void OGLWidget::update() {


    this->processKeys();
    QOpenGLWidget::update();
}

void OGLWidget::processKeys(){

    // Camera Transformation
    if (Input::keyPressed(Qt::Key_W))
        {
            camera->moveForward();
        }
    if (Input::keyPressed(Qt::Key_S))
        {
            camera->moveBackwards();
        }
    if (Input::keyPressed(Qt::Key_A))
        {
            camera->moveLeft();
        }
    if (Input::keyPressed(Qt::Key_D))
        {
            camera->moveRight();
        }
    if (Input::keyPressed(Qt::Key_Q))
        {
            camera->moveUp();
        }
    if (Input::keyPressed(Qt::Key_E))
        {
            camera->moveDown();
        }
    if (Input::keyPressed(Qt::Key_Space))
        {
            camera->setCenter(QVector3D(0.0f,0.0f,0.0f));
        }

    if (Input::buttonPressed(Qt::RightButton))
    {
        camera->rotatex(-Input::mouseDelta().y()/8.0);
        camera->rotatey(-Input::mouseDelta().x()/8.0);
    }
}

void OGLWidget::initializeGL()
{

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glClearColor(0.0f,0.0f,0.5f,1.0f);

    m_floor = new Floor(10,10);
    m_skyProgram = new (QOpenGLShaderProgram);
    m_sky.initialize(m_skyProgram);
    m_cubeProgram = new (QOpenGLShaderProgram);
    m_cube.initialize(m_cubeProgram);
    m_floorProgram = new (QOpenGLShaderProgram);
    m_floor->initialize(m_floorProgram);

    //LabGrid *labgrid = new LabGrid(QVector3D(0,0,0),10);


}

void OGLWidget::paintGL()
{

    QOpenGLFunctions * funcs = this;

    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    m_skyProgram->bind();
    m_skyProgram->setUniformValue("modelTransform", m_sky.getTransform());
    m_skyProgram->setUniformValue("viewProjection", camera->viewProjection());
    m_skyProgram->setUniformValue("cameraPosition", camera->eye());

    m_sky.draw(*funcs);

    glEnable(GL_DEPTH_TEST);

    m_cubeProgram->bind();
    m_cubeProgram->setUniformValue("modelTransform", m_cube.getTransform());
    m_cubeProgram->setUniformValue("viewProjection", camera->viewProjection());

    m_cube.draw(*funcs);

    m_floorProgram->bind();
    m_floorProgram->setUniformValue("modelTransform", m_floor->getTransform());
    m_floorProgram->setUniformValue("viewProjection", camera->viewProjection());

    m_floor->draw(*funcs);
}


void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

}



