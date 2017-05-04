#include "camera.h"

#include <cassert>

Camera::Camera(
    const QVector3D & eye
,   const QVector3D & center
,   const QVector3D & up)
: m_dirty(false)

, m_eye(eye)
, m_center(center)
, m_up(up)

, m_fovy(40.f)
, m_aspect(1.f)
, m_zNear(0.1f)
, m_zFar(1024.0f)
{
}

Camera::~Camera()
{
}

void Camera::invalidateMatrices()
{
    m_view.invalidate();
    m_viewInverted.invalidate();
    m_projection.invalidate();
    m_projectionInverted.invalidate();
    m_viewProjection.invalidate();
    m_viewProjectionInverted.invalidate();
}

void Camera::dirty(bool update)
{
    m_dirty = true;

    if (update)
        this->update();
}

void Camera::moveRight() {
    QVector3D right = this->getLocalRight();
    this->setEye(m_eye+m_speedx*right);
    this->setCenter(m_center+m_speedx*right);
}


void Camera::moveRight(float f) {

    QVector3D right = this->getLocalRight();
    this->setEye(m_eye+f*right);
    this->setCenter(m_center+f*right);
}


void Camera::moveLeft() {
    QVector3D left = -this->getLocalRight();
    this->setEye(m_eye+m_speedx*left);
    this->setCenter(m_center+m_speedx*left);
}

void Camera::moveLeft(float f) {
    QVector3D left = -this->getLocalRight();
    this->setEye(m_eye+f*left);
    this->setCenter(m_center+f*left);
}


void Camera::moveForward() {
    QVector3D forwards = this->getLocalForward();
    forwards[1]=0;
    forwards.normalize();
    this->setEye(m_eye+m_speedz*forwards);
    this->setCenter(m_center+m_speedz*forwards);
}

void Camera::moveForward(float f) {
    QVector3D forwards = this->getLocalForward();
    this->setEye(m_eye+f*forwards);
    this->setCenter(m_center+f*forwards);
}


void Camera::moveBackwards() {
    QVector3D backwards = -this->getLocalForward();
    backwards[1]=0;
    backwards.normalize();
    this->setEye(m_eye+m_speedz*backwards);
    this->setCenter(m_center+m_speedz*backwards);
}

void Camera::moveBackwards(float f) {
    QVector3D backwards = -this->getLocalForward();
    this->setEye(m_eye+f*backwards);
    this->setCenter(m_center+f*backwards);
}


void Camera::moveUp() {
    QVector3D up = this->getLocalUp();
    this->setEye(m_eye+m_speedy*up);
    this->setCenter(m_center+m_speedy*up);
}

void Camera::moveUp(float f) {
    QVector3D up = this->getLocalUp();
    this->setEye(m_eye+f*up);
    this->setCenter(m_center+f*up);
}


void Camera::moveDown() {
    QVector3D down = -this->getLocalUp();
    this->setEye(m_eye+m_speedy*down);
    this->setCenter(m_center+m_speedy*down);
}

void Camera::moveDown(float f) {
    QVector3D down = -this->getLocalUp();
    this->setEye(m_eye+f*down);
    this->setCenter(m_center+f*down);
}

void Camera::rotatex(float angle) {

    QMatrix4x4 matrix;
    matrix.rotate(angle,1.0f,0.0f,0.0f);
    this->setCenter(this->viewInverted()* matrix *this->view() * m_center);

}


void Camera::rotatey(float angle) {

    QMatrix4x4 matrix;
    matrix.rotate(angle,0.0f,1.0f,0.0f);
    this->setCenter(this->viewInverted()* matrix *this->view() * m_center);
}

void Camera::setSpeedx(float f) {
    m_speedx=f;
}

void Camera::setSpeedz(float f) {
    m_speedz=f;
}

void Camera::setSpeedy(float f) {
    m_speedy=f;
}

QVector3D Camera::getLocalForward() const {
    return (m_center-m_eye).normalized();
}

QVector3D Camera::getLocalUp() const {
    return m_up.normalized();
}

QVector3D Camera::getLocalRight() const {
    return -QVector3D::crossProduct(m_up,this->getLocalForward().normalized());
}

const QVector3D & Camera::eye() const
{
    return m_eye;
}

void Camera::setEye(const QVector3D & eye)
{
    if (eye == m_eye)
        return;

    m_eye = eye;
    dirty();


}

const QVector3D & Camera::center() const
{
    return m_center;
}

void Camera::setCenter(const QVector3D & center)
{
    if (center == m_center)
        return;

    m_center =  center;
    dirty();
}

const QVector3D & Camera::up() const
{
    return m_up;
}

void Camera::setUp(const QVector3D & up)
{
    if (up == m_up)
        return;

    m_up = up;
    dirty();
}

float Camera::zNear() const
{
    return m_zNear;
}

void Camera::setZNear(const float zNear)
{
    if (zNear == m_zNear)
        return;

    m_zNear = zNear;
    assert(m_zNear > 0.0);

    dirty();
}

float Camera::zFar() const
{
    return m_zFar;
}

void Camera::setZFar(const float zFar)
{
    if (zFar == m_zFar)
        return;

    m_zFar = zFar;
    assert(m_zFar > m_zNear);

    dirty();
}

float Camera::fovy() const
{
    return m_fovy;
}

void Camera::setFovy(const float fovy)
{
    if (fovy == m_fovy)
        return;

    m_fovy = fovy;
    assert(m_fovy > 0.0);

    dirty();
}

const QSize & Camera::viewport() const
{
    return m_viewport;
}

void Camera::setViewport(const QSize & viewport)
{
    if (viewport == m_viewport)
        return;

    m_aspect = viewport.width() / qMax<float>(static_cast<float>(viewport.height()), 1.f);
    m_viewport = viewport;

    dirty();
}

void Camera::update()
{
    if (!m_dirty)
        return;

    invalidateMatrices();

    m_dirty = false;

    emit(changed());
}

const QMatrix4x4 & Camera::view()
{
    if (m_dirty)
        update();

    if (!m_view.isValid())
    {
        m_view.value().setToIdentity();
        m_view.value().lookAt(m_eye, m_center, m_up);
        m_view.validate();
    }

    return m_view.value();
}

const QMatrix4x4 & Camera::projection()
{
    if (m_dirty)
        update();

    if (!m_projection.isValid())
    {
        m_projection.value().setToIdentity();
        m_projection.value().perspective(m_fovy, m_aspect, m_zNear, m_zFar);
        m_projection.validate();
    }

    return m_projection.value();
}

const QMatrix4x4 & Camera::viewProjection()
{
    if (m_dirty)
        update();

    if (!m_viewProjection.isValid())
        m_viewProjection.setValue(projection() * view());

    return m_viewProjection.value();
}

const QMatrix4x4 & Camera::viewInverted()
{
    if (m_dirty)
        update();

    if (!m_viewInverted.isValid())
        m_viewInverted.setValue(QMatrix4x4(view().inverted()));

    return m_viewInverted.value();
}

const QMatrix4x4 & Camera::projectionInverted()
{
    if (m_dirty)
        update();

    if (!m_projectionInverted.isValid())
        m_projectionInverted.setValue(QMatrix4x4(projection().inverted()));

    return m_projectionInverted.value();
}

const QMatrix4x4 & Camera::viewProjectionInverted()
{
    if (m_dirty)
        update();

    if (!m_viewProjectionInverted.isValid())
        m_viewProjectionInverted.setValue(QMatrix4x4(viewProjection().inverted()));

    return m_viewProjectionInverted.value();
}

