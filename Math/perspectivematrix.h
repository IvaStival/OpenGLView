#ifndef PERSPECTIVEMATRIX_H
#define PERSPECTIVEMATRIX_H

#include <QMatrix4x4>
#include <math.h>

class PerspectiveMatrix
{
private:
    double fov, aspect, near, far;
    QMatrix4x4 matrix;

public:
    PerspectiveMatrix();

    static double PI;
    QMatrix4x4& perspective(double fov, double aspect, double near, double far);
    const QMatrix4x4& getMatrix();
};

#endif // PERSPECTIVEMATRIX_H
