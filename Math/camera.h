#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QVector3D>
#include <QVector2D>
#include <iostream>

class Camera
{
private:
    QVector3D position;
    QVector3D view;
    QVector3D up;
    QVector2D oldPosition;
    float theta, phi;
    QVector3D center;
    float radius;

    bool up_change;

public:
    Camera();

    void mouseLookUpdate(const QVector2D newPos);

    void mouseRotateUpdate(const QVector2D newPos);

    void mousePressUpdate(const QVector2D pos);

    void mouseZoomUpdate(const QVector2D newPos);

    QMatrix4x4 getModelToViewLookAt() const;
    QMatrix4x4 getModelToView() const;

};

#endif // CAMERA_H
