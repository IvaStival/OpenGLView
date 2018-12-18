#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QVector4D>
#include <QMouseEvent>
#include <QString>
#include <QtDebug>
#include "Math/perspectivematrix.h"
#include "Primitivies/triangleshader.h"
#include "Primitivies/cubeshader.h"
#include "Primitivies/vertex.h"
#include "Math/perspectivematrix.h"
#include "Math/camera.h"


#include <iostream>

class QOpenGLShaderProgram;

class OpenGLView : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT

private:
    QMatrix4x4 persp;
    QOpenGLBuffer vertexBufferObject;                                             // Usado para alocar a memoria utilizada na GPU.
                                                                                  // Essa classe é que gerencia esse processo, com ela podemos
                                                                                  // especificar o espaço a ser utilizado e instanciar os valores de cada buffer.
    QOpenGLBuffer indexVertexBufferObject;

//    QOpenGLBuffer instanced;

    QOpenGLBuffer instancingCubes;

    QOpenGLVertexArrayObject vertexArrayObject;                                   // Um Vertex Array Object é simplesmente um objeto armazenado na GPU que controla todos
                                                                                  // os buffers e vincula informações associadas a uma chamada de desenho.

    QOpenGLShaderProgram* program;                                                // Shader program permite é a parte do codigo que é executada em GPU
                                                                                  // São usados arquivos que usam a linguagem de programação GLSL, de inicio usaremos 2
                                                                                  // arquivos, um chamado VertexShader e outro FragmentShader.
                                                                                  // Resumidamente VertexShader é quem pode manipular atributos do vertice
                                                                                  // FragmentShader é responsavel por como os pixels entre os vertices aparecem, é parte da
                                                                                  // da Rasterização.
    Camera* camera;
    bool alt_pressed, rigth_mouse;


    void printDebug(QString to_print);
    void printDebug(int to_print);
protected:

    void initializeGL();
    void resizeGL(int width, int hegth);
    void paintGL();
    void teardownGL();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
public:



    explicit OpenGLView(QWidget *parent = 0);
    ~OpenGLView();


};

#endif // OPENGLVIEW_H
