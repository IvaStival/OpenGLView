#include "openglview.h"
#include "Primitivies/vertex.h"
#include <QOpenGLShaderProgram>


OpenGLView::OpenGLView(QWidget * parent) : QOpenGLWidget(parent){}

OpenGLView::~OpenGLView(){}

int numVerticerToDraw = 0;
int uniform_color_id = 0;

void OpenGLView::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE);

    {
        ShaderData triangle = ShaderGenerator::makeTriangle();
        numVerticerToDraw = triangle.numVertices;



        // CREATE A SHADER
        // INSTANTIATE A NEW VERTEX AND FRAGMENT SHADER
        // VERTEX SHADER IS RESPONSIBLE BY CREATE ALL GEOMETRY USING USER POSITIONS BUFFER AND PASS CUSTOM DATA TO FRAGMENT SHADER(COLOR)
        // FRAGMENT SHADER IS RESPONSIBLE BY INTERPOLATE CUSTOM DATA (AS COLOR)
        this->program = new QOpenGLShaderProgram();
        // ADD SHADERS BY FILES
        this->program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
        this->program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
        // LINK SHADERS
        this->program->link();
        // BIND
        this->program->bind();


        // CREATE A BUFFER
        this->vertexBufferObject.create();
        // BIND AS CURRENT VERTEX BUFFER OBJECT
        this->vertexBufferObject.bind();
        this->vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);    // SET DRAW PATTERN AS STATIC
        this->vertexBufferObject.allocate(triangle.vertices, triangle.verticesBufferSize());                // ALOCATE verts ON GPU, USE YOUR SIZE

//        std::cout<<triangle.verticesBufferSize()<<std::endl;

        // CREATE AN OBJECT
        this->vertexArrayObject.create();
        // BIND AS CURRENT VERTEX ARRAY BUFFER
        this->vertexArrayObject.bind();
        // SET 0 TO VERTICES BUFFER
        this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
        // SET 1 TO COLORS VALUES
        this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

        // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
        // THIS FIRST IS TO READ VERTICES INFO
        this->program->setAttributeBuffer(0, GL_FLOAT, triangle.positionOffSet,triangle.positionSize,triangle.stride);  // 0 - id
                                                                 // GL_FLOAT - Variable type
                                                                 // 0 - offset
                                                                 // 3 - tuple size
                                                                 // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice

        // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
        // THIS FIRST IS TO READ VERTICES INFO
        this->program->setAttributeBuffer(1, GL_FLOAT, triangle.colorOffset, triangle.colorSize, triangle.stride);  // 1 - id
                                                                    // GL_FLOAT - Variable type
                                                                    // 12 - offset - (sizeof(GL_FLOAT) * 3 - (3 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                    //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                    // 3 - tuple size
                                                                    // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)

        // RELEASE ALL
        this->vertexBufferObject.release();
        this->vertexArrayObject.release();
        this->program->release();

        triangle.cleanUp();
    }
    this->printDebug("Criando nova cor!");

}

void OpenGLView::resizeGL(int width, int height){
    (void)width;
    (void)height;
}

void OpenGLView::paintGL(){
    // CLEAR COLOR BUFFER TO ENABLE UPDATE REDRAW COLOR
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // BIND TO THIS PROGRAM
    this->program->bind();
    {
        // BIND TO THIS VERTEX ARRAY OBJECT
        this->vertexArrayObject.bind();

        QVector4D vt(1.0f,0.0f,0.0f,1.0f);
        uniform_color_id = this->program->uniformLocation("uniformValue");
        printDebug(uniform_color_id);


        this->program->setUniformValue(uniform_color_id, vt);

        // DRAW AS TRIANGLES
        glDrawArrays(GL_TRIANGLES, 0, 6);                         // glDrawArrays(MODE, FIRST, VERTICE_SIZE)

        // RELEASE ALL
        this->vertexArrayObject.release();
    }
    this->program->release();
}

void OpenGLView::teardownGL(){
    // Actually destroy our OpenGL information
    this->vertexBufferObject.destroy();
    this->vertexArrayObject.destroy();
    delete this->program;
}

void OpenGLView::printDebug(QString to_print){
    qDebug()<<to_print;
}

void OpenGLView::printDebug(int to_print){
    qDebug()<<to_print;
}
