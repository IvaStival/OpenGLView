#include "openglmainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
int main(int argc, char *argv[])
{
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
