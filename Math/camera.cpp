#include "camera.h"
#include <math.h>

Camera::Camera() : view(0.0f, 0.0f, -1.0f) ,position(2.0,2.0,2.0), theta(0.0f), phi( 3.14f / 2.0f), center(0.0f,0.0f,-3.0f), up(0.0f, 1.0f, 0.0f), radius(5.0f){
    this->up_change = false;
}


void Camera::mouseLookUpdate(const QVector2D newPos){
    QVector2D delta = newPos - this->oldPosition;

    if(delta.length() > 50.0f){
        this->oldPosition = newPos;
        return;
    }
    float speed = 0.5f;
    QMatrix4x4 matrixX;
    QMatrix4x4 matrixY;
    QVector3D rotateAround = QVector3D::crossProduct(this->view, this->up);

    matrixX.rotate(-delta.x() * speed, this->up);
    matrixY.rotate(-delta.y() * speed, rotateAround);
    this->view = matrixX * matrixY * this->view;
    this->oldPosition = newPos;

}

void Camera::mousePressUpdate(const QVector2D pos){
    this->oldPosition = pos;
}

void Camera::mouseRotateUpdate(const QVector2D newPos){
    QVector2D delta = newPos - this->oldPosition;
    float step = 3.0f;


    this->theta += (newPos.x()-this->oldPosition.x()) * 0.3f;
    this->phi   += (newPos.y()-this->oldPosition.y()) * 0.3f;

    this->oldPosition = newPos;
}

void Camera::mouseZoomUpdate(const QVector2D newPos){
    QVector2D delta = newPos - this->oldPosition;

    float x = -(newPos.x()-this->oldPosition.x()) * 0.01f;
    float y = -(newPos.y()-this->oldPosition.y()) * 0.01f;

    this->radius += x + y;
    this->oldPosition = newPos;
}

QMatrix4x4 Camera::getModelToViewLookAt() const{
    QMatrix4x4 result;

//    float eyeX = center.x() + radius*sin(theta)*cos(phi);
//    float eyeY = center.y() + radius*sin(theta)*sin(phi);
//    float eyeZ = center.z() + radius*cos(theta);

    float eyeX = center.x() + radius*cos(phi)*cos(theta);
    float eyeY = center.y() + radius*sin(phi);
    float eyeZ = center.z() + radius*cos(phi)*sin(theta);

//    result.lookAt(this->position, QVector3D(0.0f, 0.0f, -3.0f), this->up);
    result.lookAt(QVector3D(eyeX, eyeY, eyeZ), this->center, this->up);


    return result;
}


QMatrix4x4 Camera::getModelToView() const{
    QMatrix4x4 result;


    result.setToIdentity();
    result.translate(0.0f, 0.0f, -radius);
    result.rotate(this->phi, QVector3D(1, 0, 0));
    result.rotate(this->theta, QVector3D(0, 1, 0));
    result.translate(-this->center.x(), -this->center.y(), -this->center.z());

    return result;
}
