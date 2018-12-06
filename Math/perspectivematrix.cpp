#include "perspectivematrix.h"

double PerspectiveMatrix::PI =  3.141592653589793238462643383279;

PerspectiveMatrix::PerspectiveMatrix() : fov(0.0), aspect(0.0), near(0.0), far(0.0){}

QMatrix4x4& PerspectiveMatrix::perspective(double fov, double aspect, double near, double far){
    double D2R = PI / 180.0;
    double yScale = 1.0 / tan(D2R * fov / 2);
    double xScale = yScale / aspect;
    double nearmfar = near - far;

    this->matrix.setRow(0, QVector4D(xScale, 0, 0, 0));
    this->matrix.setRow(1, QVector4D(0, yScale, 0, 0));
    this->matrix.setRow(2, QVector4D(0, 0, (far + near) / nearmfar, 2*far*near / nearmfar));
    this->matrix.setRow(3, QVector4D(0, 0, -1, 0));

    return this->matrix;
}


const QMatrix4x4& PerspectiveMatrix::getMatrix(){
    return this->matrix;
}
