#ifndef OPENGLMAINWINDOW_H
#define OPENGLMAINWINDOW_H

#include <QMainWindow>
#include "openglview.h"

namespace Ui {
class OpenGlMainWindow;
}

class OpenGlMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenGlMainWindow(QWidget *parent = nullptr);
    ~OpenGlMainWindow();

//private:
//    Ui::OpenGlMainWindow *ui;
};

#endif // OPENGLMAINWINDOW_H
