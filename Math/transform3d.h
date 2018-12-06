#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class Transform3D
{
private:
    QVector3D n_translate;
    QQuaternion n_rotation;
    QVector3D n_scale;
    QMatrix4x4 world;

public:
    Transform3D();

    void translate(const QVector3D& add_vt);
    void translate(float add_x, float add_y, float add_z);
    void rotate(const QQuaternion& add_r);
    void rotate(float add_angle, float on_x, float on_y, float on_z);
    void rotate(float add_angle, const QVector3D& on_axis);
    void scale(const QVector3D& add_vt);
    void scale(float add_x, float add_y, float add_z);

    void setTranslate(const QVector3D& vt);
    void setTranslate(float x, float y, float z);
    void setRotation(const QQuaternion& r);
    void setRotation(float angle, float x, float y, float z);
    void setRotation(float angle, const QVector3D& axis);
    void setScale(const QVector3D& vt);
    void setScale(float x, float y, float z);

    const QVector3D& getTranslate();
    const QQuaternion& getRotate();
    const QVector3D& getScale();
    const QMatrix4x4& toMatrix();


};

inline void Transform3D::translate(float add_x, float add_y, float add_z){ this->translate(QVector3D(add_x, add_y, add_z)); }
inline void Transform3D::rotate(float add_angle, float on_x, float on_y, float on_z) { this->rotate(QQuaternion::fromAxisAndAngle(QVector3D(on_x, on_y, on_z), add_angle)); }
inline void Transform3D::rotate(float add_angle, const QVector3D& on_axis) { this->rotate(QQuaternion::fromAxisAndAngle(on_axis, add_angle)); }
inline void Transform3D::scale(float add_x, float add_y, float add_z) { this->scale(QVector3D(add_x, add_y, add_z)); }

inline void Transform3D::setTranslate(float x, float y, float z) { this->setTranslate(QVector3D(x, y, z)); }
inline void Transform3D::setRotation(float angle, float x, float y, float z) { this->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(x, y, z), angle)); }
inline void Transform3D::setRotation(float angle, const QVector3D& axis) { this->setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
inline void Transform3D::setScale(float x, float y, float z) { this->setScale(QVector3D(x, y, z)); }

#endif // TRANSFORM3D_H
