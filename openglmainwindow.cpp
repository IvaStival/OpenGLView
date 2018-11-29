#include "openglmainwindow.h"
#include "ui_openglmainwindow.h"

OpenGlMainWindow::OpenGlMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenGlMainWindow)
{
    ui->setupUi(this);
}

OpenGlMainWindow::~OpenGlMainWindow()
{
    delete ui;
}
