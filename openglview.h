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

#include <iostream>
#include <vector>
#include <QMatrix4x4>

#include "Math/perspectivematrix.h"
#include "Primitivies/triangleshader.h"
#include "Primitivies/cubeshader.h"
#include "Primitivies/axisShader.h"
#include "Primitivies/vertex.h"
#include "Math/perspectivematrix.h"
#include "Math/camera.h"

using namespace std;

//class QOpenGLShaderProgram;

class OpenGLView : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT

private:
    QMatrix4x4 persp;
    QOpenGLBuffer vertexOrthoBufferObject;
    QOpenGLBuffer vertexBufferObject;                                             // Usado para alocar a memoria utilizada na GPU.
                                                                                  // Essa classe é que gerencia esse processo, com ela podemos
                                                                                  // especificar o espaço a ser utilizado e instanciar os valores de cada buffer.
    QOpenGLBuffer indexOrthoVertexBufferObject;
    QOpenGLBuffer indexVertexBufferObject;

    QOpenGLBuffer fullTransformBuffer;
    QOpenGLBuffer fullOrthoTransformBuffer;

    QOpenGLVertexArrayObject vertexArrayAxisObject;
    QOpenGLVertexArrayObject vertexArrayObject;                                   // Um Vertex Array Object é simplesmente um objeto armazenado na GPU que controla todos
                                                                                  // os buffers e vincula informações associadas a uma chamada de desenho.

    QOpenGLShaderProgram* program;                                                // Shader program permite é a parte do codigo que é executada em GPU
                                                                                  // São usados arquivos que usam a linguagem de programação GLSL, de inicio usaremos 2
                                                                                  // arquivos, um chamado VertexShader e outro FragmentShader.
                                                                                  // Resumidamente VertexShader é quem pode manipular atributos do vertice
                                                                                  // FragmentShader é responsavel por como os pixels entre os vertices aparecem, é parte da
                                                                                  // da Rasterização.
    Camera* camera;
    vector<QMatrix4x4> fullTransform;
    bool alt_pressed, ctrl_pressed, rigth_mouse;


    void printDebug(QString to_print);
    void printDebug(int to_print);
protected:

    void initializeGL();
    void resizeGL(int width, int hegth);
    void paintGL();
//    void teardownGL();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
public:

    explicit OpenGLView(QWidget *parent = 0);
    ~OpenGLView();

    void sendToOpenGLCubeShader();
    void sendToOpenGLAxisShader();
    QMatrix4x4 fullPerspectiveMatrix(const QVector3D& translate, const float& angle, const QVector3D& axis) const;
    QMatrix4x4 fullOrthoMatrix(const QVector3D& translate, const float& angle, const QVector3D& axis) const;


};

#endif // OPENGLVIEW_H
