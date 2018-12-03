#include "openglmainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include "vector3d.h"
#include "vertex3d.h"

int main(int argc, char *argv[])
{

//    Vector3D vt(2, 3, 4);
//    Vector3D vt2(vt);
//    Vector3D vt3(1,1,1);

//    Vector3D t;
//    t = vt + 10;
//    t = t * 10;
//    t += 10;

//    std::cout<<t<<std::endl;

//    t += vt3;
//    std::cout<<t<<std::endl;

//    Vector3D position(1.0f, 2.0f, 1.0f);
//    Vector3D color(1.0f, 0.5f, 0.5f, 1.0f);

//    Vertex3D vtx(position, color);

//    std::cout<<vtx<<std::endl;

//    return 0;
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    QSurfaceFormat::setDefaultFormat(format);

    OpenGlMainWindow w;
    w.show();

    return a.exec();
}
