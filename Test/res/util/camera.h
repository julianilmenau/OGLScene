#pragma once

#include <QtGlobal>
#include <QObject>

#include <QSize>
#include <QVector3D>
#include <QMatrix4x4>
#include "cachedvalue.h"


class Camera : public QObject
{
    Q_OBJECT

public:
    Camera(
        const QVector3D & eye    = QVector3D(0.0f, 0.0f, 1.0f)
    ,   const QVector3D & center = QVector3D(0.0f, 0.0f, 0.0f)
    ,   const QVector3D & up     = QVector3D(0.0f, 1.0f, 0.0f));

    virtual ~Camera();

    const QVector3D & eye() const;
    void setEye(const QVector3D & eye);
    const QVector3D & center() const;
    void setCenter(const QVector3D & center);
    const QVector3D & up() const;
    void setUp(const QVector3D & up);

    QVector3D getLocalForward() const;
    QVector3D getLocalUp() const;
    QVector3D getLocalRight() const;


    void setSpeedx(float speed);
    void setSpeedz(float speed);
    void setSpeedy(float speed);

    void moveRight();
    void moveLeft();
    void moveForward();
    void moveBackwards();
    void moveUp();
    void moveDown();

    void move(QVector3D direction);

    void moveRight(float f);
    void moveLeft(float f);
    void moveForward(float f);
    void moveBackwards(float f);
    void moveUp(float f);
    void moveDown(float f);


    void rotatex(float angle);
    void rotatey(float angle);



    float zNear() const;
    void setZNear(float zNear);
    float zFar() const;
    void setZFar(float zFar);

    float fovy() const;
    void setFovy(float fovy);

    const QSize & viewport() const;
    void setViewport(const QSize & viewport);

    // lazy matrices getters

    const QMatrix4x4 & view();
    const QMatrix4x4 & projection();
    const QMatrix4x4 & viewProjection();
    const QMatrix4x4 & viewInverted();
    const QMatrix4x4 & projectionInverted();
    const QMatrix4x4 & viewProjectionInverted();

    void update();

signals:
    void changed();

protected:
    void dirty(bool update = true);
    void invalidateMatrices();

protected:
    bool m_dirty;

    QVector3D m_eye;
    QVector3D m_center;
    QVector3D m_up;

    float m_speedx;
    float m_speedz;
    float m_speedy;

    float m_fovy;
    float m_aspect;
    float m_zNear;
    float m_zFar;
    QSize m_viewport;

    CachedValue<QMatrix4x4> m_view;
    CachedValue<QMatrix4x4> m_viewInverted;
    CachedValue<QMatrix4x4> m_projection;
    CachedValue<QMatrix4x4> m_projectionInverted;
    CachedValue<QMatrix4x4> m_viewProjection;
    CachedValue<QMatrix4x4> m_viewProjectionInverted;
};
