#include "openglmainwindow.h"
#include "ui_openglmainwindow.h"

OpenGlMainWindow::OpenGlMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
//    ui->setupUi(this);
    this->setCentralWidget(new OpenGLView(this));
}

OpenGlMainWindow::~OpenGlMainWindow()
{
}
