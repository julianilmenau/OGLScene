#include "res/drawable/header/abstractDrawable.h"


void AbstractDrawable::setTransform(QMatrix4x4 matrix) {
    m_transform = matrix;
}


QMatrix4x4 AbstractDrawable::getTransform() {
    return m_transform;
}
