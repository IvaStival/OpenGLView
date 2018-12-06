#include "transform3d.h"

Transform3D::Transform3D(){}

void Transform3D::translate(const QVector3D& add_vt) {
    this->n_translate += add_vt;
}

void Transform3D::rotate(const QQuaternion& add_r){
    this->n_rotation =  add_r * this->n_rotation;
}

void Transform3D::scale(const QVector3D& add_vt){
    this->n_scale *= add_vt;
}

void Transform3D::setTranslate(const QVector3D& vt){
    this->n_translate = vt;
}

void Transform3D::setRotation(const QQuaternion& r){
    this->n_rotation = r;
}

void Transform3D::setScale(const QVector3D& vt){
    this->n_scale = vt;
}



const QVector3D& Transform3D::getTranslate(){
    return this->n_translate;
}

const QVector3D& Transform3D::getScale(){
    return this->n_scale;
}

const QQuaternion& Transform3D::getRotate(){
    return this->n_rotation;
}

const QMatrix4x4& Transform3D::toMatrix(){
    this->world.setToIdentity();
    this->world.translate(this->n_translate);
    this->world.rotate(this->n_rotation);
    this->world.scale(this->n_scale);
    return this->world;
}
