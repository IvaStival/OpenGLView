#include "openglmainwindow.h"
#include "ui_openglmainwindow.h"

OpenGlMainWindow::OpenGlMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
//    ui->setupUi(this);
    this->setMinimumSize(QSize(800,600));
    this->setCentralWidget(new OpenGLView(this));
}

OpenGlMainWindow::~OpenGlMainWindow()
{
}
