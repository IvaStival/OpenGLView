#include "openglview.h"
#include "Primitivies/vertex.h"
#include "Math/perspectivematrix.h"
#include <QOpenGLShaderProgram>
#include <QVector4D>


float inst[] = {-0.5f, 0.0f, 0.5f};

OpenGLView::OpenGLView(QWidget * parent) : QOpenGLWidget(parent), indexVertexBufferObject(QOpenGLBuffer::IndexBuffer), instancingCubes(QOpenGLBuffer::VertexBuffer){
    bool m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;

    std::cout<<m_core<<std::endl;

}

OpenGLView::~OpenGLView(){}

int numVerticerToDraw = 0;
int numIndexToDraw = 0;
int uniform_color_id = 0;

void OpenGLView::initializeGL(){

    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // GL_CULL_FACE(0x0B44) AND GL_DEPTH_TEST(0x0B71) ARE NOT FLAGS THEN THEY NEED TO BE CALLED SEPERATLY
//    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    {
//        ShaderData triangle = ShaderGenerator::makeTriangle();
//        TriangleShader triangle;
        ShaderData *shader =  new CubeShader();
        numVerticerToDraw = shader->numVertices;
        numIndexToDraw = shader->numIndex;


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


        // CREATE AN OBJECT
        this->vertexArrayObject.create();
        // BIND AS CURRENT VERTEX ARRAY BUFFER
        this->vertexArrayObject.bind();


        // CREATE A BUFFER
        this->vertexBufferObject.create();
        // BIND AS CURRENT VERTEX BUFFER OBJECT
        this->vertexBufferObject.bind();

        this->vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);    // SET DRAW PATTERN AS STATIC
        this->vertexBufferObject.allocate(shader->vertices, shader->verticesBufferSize());                // ALOCATE verts ON GPU, USE YOUR SIZE

        // SET 0 TO VERTICES BUFFER
        this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
        // SET 1 TO COLORS VALUES
        this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

        // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
        // THIS FIRST IS TO READ VERTICES INFO
        this->program->setAttributeBuffer(0, GL_FLOAT, shader->positionOffSet,shader->positionSize,shader->stride);
                                                                 // 0 - id
                                                                 // GL_FLOAT - Variable type
                                                                 // 0 - offset
                                                                 // 3 - tuple size
                                                                 // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice

        // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
        // THIS FIRST IS TO READ VERTICES INFO
        this->program->setAttributeBuffer(1, GL_FLOAT, shader->colorOffset, shader->colorSize, shader->stride);
                                                                    // 1 - id
                                                                    // GL_FLOAT - Variable type
                                                                    // 12 - offset - (sizeof(GL_FLOAT) * 3 - (3 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                    //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                    // 3 - tuple size
                                                                    // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)

        // RELEASE VERTEX BUFFER
        this->vertexBufferObject.release();


        // INDEX BUFFERS
        this->indexVertexBufferObject.create();
        this->indexVertexBufferObject.bind();
        this->indexVertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);    // SET DRAW PATTERN AS STATIC
        this->indexVertexBufferObject.allocate(shader->index, shader->indexBufferSize());
        this->indexVertexBufferObject.release();

        // INSTANCING
        // CREATE TRANSFORM MATRIX
        PerspectiveMatrix persp;
        QMatrix4x4 projectionMatrix = persp.perspective(60.0f, ((float)width())/height(), 0.1f, 10.0f);
        QMatrix4x4 transform1, transform2;
        QMatrix4x4 rotate;

        transform1.setToIdentity();
        transform2.setToIdentity();

        transform1.translate(-1.0f, 0.0f, -3.0f);
        transform1.rotate(36, QVector3D(1,0,0));

        transform2.translate(1.0f,0.0f,-3.75f);
        transform2.rotate(126, QVector3D(0,1,0));

        QMatrix4x4 fullTransform[] = {
            projectionMatrix * transform1,
            projectionMatrix * transform2
            };

        int id = this->program->attributeLocation("fullTransform");

        // INSTANCING SHADER TRANSFORMS
        this->instancingCubes.create();
        this->instancingCubes.setUsagePattern(QOpenGLBuffer::StaticDraw);
        this->instancingCubes.bind();

        this->instancingCubes.allocate(fullTransform, sizeof(fullTransform));

        // SET ATTRIBUTE BUFFER TO INTERPRETER CORRECTLY THE MATRIX, WE NEED TO CREATE THIS BECAUSE THE GPU READ 4 VECTORS NOT 1 4x4 MATRIX

//                this->program->setAttributeBuffer(2, GL_FLOAT, 0, 4, sizeof(QMatrix4x4));
//                this->program->setAttributeBuffer(3, GL_FLOAT, sizeof(GL_FLOAT) * 1 * 4, 4, sizeof(QMatrix4x4));
//                this->program->setAttributeBuffer(4, GL_FLOAT, sizeof(GL_FLOAT) * 2 * 4, 4, sizeof(QMatrix4x4));
//                this->program->setAttributeBuffer(5, GL_FLOAT, sizeof(GL_FLOAT) * 3 * 4, 4, sizeof(QMatrix4x4));

//                this->program->enableAttributeArray(2);
//                this->program->enableAttributeArray(3);
//                this->program->enableAttributeArray(4);
//                this->program->enableAttributeArray(5);

//                glVertexAttribDivisor(2,1);
//                glVertexAttribDivisor(3,1);
//                glVertexAttribDivisor(4,1);
//                glVertexAttribDivisor(5,1);

        for( int i = 0; i < 4; ++i){
            this->program->setAttributeBuffer(id+i, GL_FLOAT, sizeof(GL_FLOAT)*i*4, 4, sizeof(QMatrix4x4));
            this->program->enableAttributeArray(id+i);
            glVertexAttribDivisor(id+i,1);
        }

        // RELEASE INSTANCING
        this->instancingCubes.release();

        // RELEASE VAO
        this->vertexArrayObject.release();
        // RELEASE PROGRAM
        this->program->release();

        char *version = (char*)glGetString(GL_VERSION);
                std::cout <<*version<<std::endl ;

        // WE CAN CLENUP BECAUSE THE INFO IS ON GPU RAM
        shader->cleanUp();

    }
    this->printDebug("Criando nova cor!");

}

void OpenGLView::resizeGL(int width, int height){
//    (void)width;
//    (void)height;
    glViewport(0, 0, width, height);
}

void OpenGLView::paintGL(){
    // CLEAR COLOR BUFFER TO ENABLE UPDATE REDRAW COLOR
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glViewport(0,0,width(), height());


    // BIND TO THIS PROGRAM
    this->program->bind();
    {
        // BIND TO THIS VERTEX ARRAY OBJECT
        this->vertexArrayObject.bind();             // VAO
        this->indexVertexBufferObject.bind();       // INDEX BUFFER


//        // PROJECTION * TRANSLATE * ROTATE
//        PerspectiveMatrix persp;
//        QMatrix4x4 projectionMatrix = persp.perspective(60.0f, ((float)width())/height(), 0.1f, 10.0f);
//        QMatrix4x4 translate;
//        translate.translate(0.0f, 0.0f, -3.0f);
//        QMatrix4x4 rotate;
//        rotate.rotate(0, QVector3D(1,0,0));

//        // GET GLSL VARS IDS
//        int world_matrix_id = this->program->uniformLocation("worldMatrix");
//        int projection_id = this->program->uniformLocation("projection");

//        // SET GPU UNIFORM MATRIX
//        this->program->setUniformValue(world_matrix_id, translate*rotate);
//        this->program->setUniformValue(projection_id, projectionMatrix);

//        // DRAW AS TRIANGLES
//        glDrawArrays(GL_TRIANGLES, 0, numVerticerToDraw);                         // glDrawArrays(MODE, FIRST, VERTICE_SIZE)

//          // DRAW ELEMENTS USING INDICES
//        glDrawElements(GL_TRIANGLE_STRIP, numIndexToDraw, GL_UNSIGNED_SHORT, 0);

        // DRAW ELEMENTS USING INDICES AND RENDER INSTANCING, THE NUMBER 3 IS THE NUMBER OF INSTANCING TO RENDER, THIS IS THE SIZE OF ARRAY INSTANCING
        glDrawElementsInstanced(GL_TRIANGLES, numIndexToDraw, GL_UNSIGNED_SHORT, 0, 2);
//        glDrawArraysInstanced(GL_TRIANGLES, 0, numVerticerToDraw, 2);

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
