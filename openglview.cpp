#include "openglview.h"

OpenGLView::OpenGLView(QWidget * parent) : QOpenGLWidget(parent), indexVertexBufferObject(QOpenGLBuffer::IndexBuffer), indexOrthoVertexBufferObject(QOpenGLBuffer::IndexBuffer),
                                                                  fullTransformBuffer(QOpenGLBuffer::VertexBuffer), fullOrthoTransformBuffer(QOpenGLBuffer::VertexBuffer){
//    bool m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    this->alt_pressed = this->ctrl_pressed = false;
    this->rigth_mouse = false;

    camera = new Camera();
    this->setFocusPolicy ( Qt::StrongFocus );


}

OpenGLView::~OpenGLView(){
    delete camera;
}

int numVerticesToDraw = 0;
int numIndexToDraw = 0;
int numVerticesToDrawAxis = 0;
int numIndexToDrawAxis = 0;

void OpenGLView::initializeGL(){

    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // GL_CULL_FACE(0x0B44) AND GL_DEPTH_TEST(0x0B71) ARE NOT FLAGS THEN THEY NEED TO BE CALLED SEPERATLY
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

//    glCullFace(GL_FRONT);
//    glCullFace(GL_BACK);
    {

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

        // SEND AND CONFIGURE OPENGL DATA
        this->sendToOpenGLCubeShader();
        this->sendToOpenGLAxisShader();

        // RELEASE PROGRAM
        this->program->release();
    }
}

void OpenGLView::sendToOpenGLCubeShader(){
        // CREATE AN OBJECT
        this->vertexArrayObject.create();
        // BIND AS CURRENT VERTEX ARRAY BUFFER
        this->vertexArrayObject.bind();

        ShaderData *shader =  new CubeShader();
        numVerticesToDraw = shader->numVertices;
        numIndexToDraw = shader->numIndex;


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
        this->program->setAttributeBuffer(0, GL_FLOAT, shader->positionOffSet,shader->positionSize,shader->stride); // 0 - id
                                                                                                                    // GL_FLOAT - Variable type
                                                                                                                    // 0 - offset
                                                                                                                    // 3 - tuple size
                                                                                                                    // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice


        // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
        // THIS FIRST IS TO READ VERTICES INFO
        this->program->setAttributeBuffer(1, GL_FLOAT, shader->colorOffset, shader->colorSize, shader->stride);     // 1 - id
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

        // INSTANCING SHADER TRANSFORMS
        this->fullTransformBuffer.create();
        this->fullTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        this->fullTransformBuffer.bind();

        // SET ATTRIBUTE BUFFER TO INTERPRETER CORRECTLY THE MATRIX, WE NEED TO CREATE THIS BECAUSE THE GPU READ 4 VECTORS NOT 1 4x4 MATRIX
        // GET THE SHADER VAR ID fullTransform
        int id = this->program->attributeLocation("fullTransform");

        for( int i = 0; i < 4; ++i){
            this->program->setAttributeBuffer(id+i, GL_FLOAT, sizeof(GL_FLOAT)*i*4, 4, sizeof(QMatrix4x4));
            this->program->enableAttributeArray(id+i);
            glVertexAttribDivisor(id+i,1);
        }

        // RELEASE INSTANCING
        this->fullTransformBuffer.release();

        // WE CAN CLENUP BECAUSE THE INFO IS ON GPU RAM
        shader->cleanUp();

        this->vertexArrayObject.release();

}

void OpenGLView::sendToOpenGLAxisShader(){

    this->vertexArrayAxisObject.create();
    this->vertexArrayAxisObject.bind();
    ShaderData* axisShader = new AxisShader();

    numVerticesToDrawAxis = axisShader->numVertices;
    numIndexToDrawAxis = axisShader->numIndex;

    this->vertexOrthoBufferObject.create();
    this->vertexOrthoBufferObject.bind();
    this->vertexOrthoBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
    this->vertexOrthoBufferObject.allocate(axisShader->vertices, axisShader->verticesBufferSize());

    // SET 0 TO VERTICES BUFFER
    this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
    // SET 1 TO COLORS VALUES
    this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

    // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(0, GL_FLOAT, axisShader->positionOffSet,axisShader->positionSize,axisShader->stride);
                                                             // 0 - id
                                                             // GL_FLOAT - Variable type
                                                             // 0 - offset
                                                             // 3 - tuple size
                                                             // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice

    // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(1, GL_FLOAT, axisShader->colorOffset, axisShader->colorSize, axisShader->stride);
                                                                // 1 - id
                                                                // GL_FLOAT - Variable type
                                                                // 12 - offset - (sizeof(GL_FLOAT) * 3 - (3 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                // 3 - tuple size
                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)

    // RELEASE VERTEX BUFFER
    this->vertexOrthoBufferObject.release();

    // INDEX BUFFERS
    this->indexOrthoVertexBufferObject.create();
    this->indexOrthoVertexBufferObject.bind();
    this->indexOrthoVertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);    // SET DRAW PATTERN AS STATIC
    this->indexOrthoVertexBufferObject.allocate(axisShader->index, axisShader->indexBufferSize());
    this->indexOrthoVertexBufferObject.release();

    // INSTANCING SHADER TRANSFORMS
    this->fullOrthoTransformBuffer.create();
    this->fullOrthoTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->fullOrthoTransformBuffer.bind();

    // SET ATTRIBUTE BUFFER TO INTERPRETER CORRECTLY THE MATRIX, WE NEED TO CREATE THIS BECAUSE THE GPU READ 4 VECTORS NOT 1 4x4 MATRIX
    // GET THE SHADER VAR ID fullTransform
    int id = this->program->attributeLocation("fullTransform");

    for( int i = 0; i < 4; ++i){
        this->program->setAttributeBuffer(id+i, GL_FLOAT, sizeof(GL_FLOAT)*i*4, 4, sizeof(QMatrix4x4));
        this->program->enableAttributeArray(id+i);
        glVertexAttribDivisor(id+i,1);
    }

//     RELEASE INSTANCING
    this->fullOrthoTransformBuffer.release();

    // RELEASE VAO
    this->indexOrthoVertexBufferObject.release();

    // WE CAN CLENUP BECAUSE THE INFO IS ON GPU RAM
    axisShader->cleanUp();
    this->vertexArrayAxisObject.release();

}

void OpenGLView::resizeGL(int width, int height){
//    (void)width;
//    (void)height;
    glViewport(0, 0, width, height);
}

void OpenGLView::paintGL(){
    // CLEAR COLOR BUFFER TO ENABLE UPDATE REDRAW COLOR
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // BIND TO THIS PROGRAM
    this->program->bind();
    {
        // BIND TO THIS VERTEX ARRAY OBJECT
        this->vertexArrayObject.bind();             // VAO
        this->indexVertexBufferObject.bind();       // INDEX BUFFER

        this->fullTransformBuffer.bind();
        this->fullTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

        QMatrix4x4 transform = this->fullPerspectiveMatrix(QVector3D(0.0, 0.0, -3.0), 0, QVector3D(1,0,0));
        QMatrix4x4 transform2 = this->fullPerspectiveMatrix(QVector3D(1.0, 0.0, -3.75), 126, QVector3D(0,1,0));

        QMatrix4x4 fullTransform[] = { transform, transform2 };

        this->fullTransformBuffer.allocate(fullTransform, sizeof(fullTransform));

        // DRAW ELEMENTS USING INDICES AND RENDER INSTANCING, THE NUMBER 3 IS THE NUMBER OF INSTANCING TO RENDER, THIS IS THE SIZE OF ARRAY INSTANCING
        glDrawElementsInstanced(GL_TRIANGLES, numIndexToDraw, GL_UNSIGNED_SHORT, 0, 1);

        // RELEASE ALL
        this->fullTransformBuffer.release();
        this->indexVertexBufferObject.release();
        this->vertexArrayObject.release();

        this->vertexArrayAxisObject.bind();
        this->indexOrthoVertexBufferObject.bind();
        this->fullOrthoTransformBuffer.bind();
        this->fullOrthoTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

        QMatrix4x4 transform3 = this->fullOrthoMatrix(QVector3D(-0.9, -0.9, -0.5), 0, QVector3D(0,0,0));
        QMatrix4x4 fullTransform2[] = { transform3 };

        this->fullOrthoTransformBuffer.allocate(fullTransform2, sizeof(fullTransform2));

        glDrawElementsInstanced(GL_LINES, numIndexToDrawAxis, GL_UNSIGNED_SHORT, 0, 1);

        this->vertexArrayAxisObject.release();
    }
    this->program->release();
}

QMatrix4x4 OpenGLView::fullPerspectiveMatrix(const QVector3D& translate, const float& angle, const QVector3D& axis) const{
    // INSTANCING
    // CREATE TRANSFORM MATRIX
    QMatrix4x4 projectionMatrix;
    PerspectiveMatrix persp;
    projectionMatrix = persp.perspective(60.0f, ((float)width())/height(), 0.1f, 30.0f);

    QMatrix4x4 transform;

    transform.setToIdentity();

    transform.translate(translate);
    transform.rotate(angle, axis);

    QMatrix4x4 view = camera->getModelToView();

    return projectionMatrix * view * transform;
}

QMatrix4x4 OpenGLView::fullOrthoMatrix(const QVector3D& translate, const float& angle, const QVector3D& axis) const{
    QMatrix4x4 projection_ortho;
    projection_ortho.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 5.f);

    QVector2D mouseMove = camera->getXY();

    QMatrix4x4 transform;

    transform.setToIdentity();

    transform.translate(translate);
    transform.rotate(angle, axis); // Y
    transform.rotate(mouseMove.y(), QVector3D(1,0,0)); // X
    transform.rotate(mouseMove.x(), QVector3D(0,1,0)); // Y


//    QMatrix4x4 view = camera->getModelToView();

    return projection_ortho * transform;
}

//void OpenGLView::teardownGL(){
////    // Actually destroy our OpenGL information
////    this->vertexBufferObject.destroy();
////    this->vertexArrayObject.destroy();
////    delete this->program;
//}

// MOUSE EVENTS
// MOVE
// HERE THE ROTATE AND ZOOM CAMERA OCCOURS, IS A ALT KEY IS PRESSED AND THE RIGHT MOUSE BUTTON IS PRESSED THE ZOOM ACCOURS
// ELSE THE ROTATE OCCOURS
void OpenGLView::mouseMoveEvent(QMouseEvent* e){
    QVector2D point(e->x(), e->y());
    if(!this->alt_pressed){
        if(this->ctrl_pressed){
            printDebug("ASDASD");
            camera->mouseLookUpdate(point);
        }
        else{
            camera->mouseRotateUpdate(point);
        }
    }
    else{
       if(this->rigth_mouse){
            camera->mouseZoomUpdate(point);
        }
       else{
           camera->mouseRotateUpdate(point);
       }
    }
    repaint();
}

// MOUSE PRESS BUTTON
// HERE WHEN THE RIGHT MOUSE BUTTON IS PRESSED AND THE ALT KEY IS PRESSED CHANGE THE BOOL VARIABLE right_mouse TO TRUE ELSE CHANGE TO FALSE
// AFTER UPDATE THE CLICKED POSITION AS THE CURRENT OLD POSITION ON CAMERA
void OpenGLView::mousePressEvent(QMouseEvent* e){

    if(this->alt_pressed){
        if(e->button() == Qt::RightButton){
            this->rigth_mouse = true;
        }
        else{
            this->rigth_mouse = false;
        }
    }
    camera->mousePressUpdate(QVector2D(e->x(), e->y()));

}

// KEYBOARD EVENTS
// KEY PRESS
// HERE WHEN PRESS ALT KEY CHANGE THE BOOL VARIABLE TO TRUE, THAT IS USED ON MOUSE PRESS AND MOVE EVENT
void OpenGLView::keyPressEvent(QKeyEvent* e){
    switch (e->key()) {
    case Qt::Key_Alt:
        this->alt_pressed = true;
        break;

    case Qt::Key_Control:
        this->ctrl_pressed = true;
        break;

    }
//    if(e->key() == Qt::Key_Alt){
//        this->alt_pressed = true;
//    }

}

// KEY RELEASE
// CHANGE THE ALT BOOL VARIABLE TO FALSE
void OpenGLView::keyReleaseEvent(QKeyEvent* e){
//    if(e->key() == Qt::Key_Alt){
//        this->alt_pressed = false;
//    }

    switch (e->key()) {
    case Qt::Key_Alt:
        this->alt_pressed = false;
        break;

    case Qt::Key_Control:
        this->ctrl_pressed = false;
        break;

    }
}

void OpenGLView::printDebug(QString to_print){
    qDebug()<<to_print;
}

void OpenGLView::printDebug(int to_print){
    qDebug()<<to_print;
}
