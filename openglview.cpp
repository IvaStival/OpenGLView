#include "openglview.h"

int numVerticesToDraw = 0;
int numIndexToDraw = 0;
int numVerticesToDrawAxis = 0;
int numIndexToDrawAxis = 0;
int numVerticesToDrawGrid = 0;
int numIndexToDrawGrid = 0;


OpenGLView::OpenGLView(QWidget * parent) : QOpenGLWidget(parent), fullTransformBuffer(QOpenGLBuffer::VertexBuffer), indexVertexBufferObject(QOpenGLBuffer::IndexBuffer),
                                                                  fullOrthoTransformBuffer(QOpenGLBuffer::VertexBuffer), indexOrthoVertexBufferObject(QOpenGLBuffer::IndexBuffer),
                                                                  fullGridTransformBuffer(QOpenGLBuffer::VertexBuffer), indexGridVertexBufferObject(QOpenGLBuffer::IndexBuffer){
    this->alt_pressed = this->ctrl_pressed = false;
    this->rigth_mouse = false;

    camera = new Camera();
    this->setFocusPolicy ( Qt::StrongFocus );

    // ---------- IMPLEMENTATION OF THE TWO GEOMETRIES ON THE SAME BUFFER ------------
    this->numCubeVertices = 0;
    this->numArrowVertices = 0;
    this->numSphereVertices = 0;
    this->numCubeNormalVertices = 0;
    this->numCubeIndex = 0;
    this->numArrowIndex = 0;
    this->numSphereIndex = 0;
    this->numCubeNormalIndex = 0;
    this->arrowIndexByteOffset = 0;
    this->sphereIndexByteOffset = 0;
    this->cubeNormalIndexByteOffset = 0;
    // -------------------------------------------------------------------------------


}

OpenGLView::~OpenGLView(){
    this->vertexBufferObject.destroy();
    this->vertexOrthoBufferObject.destroy();
    this->vertexGridBufferObject.destroy();
    delete camera;
}

void OpenGLView::initializeGL(){

    initializeOpenGLFunctions();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    // GL_CULL_FACE(0x0B44) AND GL_DEPTH_TEST(0x0B71) ARE NOT FLAGS THEN THEY NEED TO BE CALLED SEPERATLY
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

//    glFrontFace(GL_CW);
//    glCullFace(GL_FRONT);
//    glCullFace(GL_BACK);
//    glCullFace(GL_FRONT_AND_BACK);
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
//        this->sendToOpenGLCubeShader();
        this->sendToOpenGL3DShader();
        this->sendToOpenGLGridShader();
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
        delete shader;
}

void OpenGLView::sendToOpenGLSphereShader(){
        // CREATE AN OBJECT
        this->vertexArrayObject.create();
        // BIND AS CURRENT VERTEX ARRAY BUFFER
        this->vertexArrayObject.bind();

        ShaderData *shader =  new SphereShader();
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
        delete shader;
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
    delete axisShader;

}

void OpenGLView::sendToOpenGLGridShader(){


    this->vertexArrayGridObject.create();
    this->vertexArrayGridObject.bind();
    ShaderData* gridShader = new GridShader();

    numVerticesToDrawGrid = gridShader->numVertices;
    numIndexToDrawGrid = gridShader->numIndex;

    this->vertexGridBufferObject.create();
    this->vertexGridBufferObject.bind();
    this->vertexGridBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
    this->vertexGridBufferObject.allocate(gridShader->vertices, gridShader->verticesBufferSize());

    // SET 0 TO VERTICES BUFFER
    this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
    // SET 1 TO COLORS VALUES
    this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

    // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(0, GL_FLOAT, gridShader->positionOffSet,gridShader->positionSize,gridShader->stride);
                                                             // 0 - id
                                                             // GL_FLOAT - Variable type
                                                             // 0 - offset
                                                             // 3 - tuple size
                                                             // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice

    // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(1, GL_FLOAT, gridShader->colorOffset, gridShader->colorSize, gridShader->stride);
                                                                // 1 - id
                                                                // GL_FLOAT - Variable type
                                                                // 12 - offset - (sizeof(GL_FLOAT) * 3 - (3 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                // 3 - tuple size
                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)

    // RELEASE VERTEX BUFFER
    this->vertexGridBufferObject.release();

    // INDEX BUFFERS
    this->indexGridVertexBufferObject.create();
    this->indexGridVertexBufferObject.bind();
    this->indexGridVertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);    // SET DRAW PATTERN AS STATIC
    this->indexGridVertexBufferObject.allocate(gridShader->index, gridShader->indexBufferSize());
    this->indexGridVertexBufferObject.release();

    // INSTANCING SHADER TRANSFORMS
    this->fullGridTransformBuffer.create();
    this->fullGridTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    this->fullGridTransformBuffer.bind();

    // SET ATTRIBUTE BUFFER TO INTERPRETER CORRECTLY THE MATRIX, WE NEED TO CREATE THIS BECAUSE THE GPU READ 4 VECTORS NOT 1 4x4 MATRIX
    // GET THE SHADER VAR ID fullTransform
    int id = this->program->attributeLocation("fullTransform");

    for( int i = 0; i < 4; ++i){
        this->program->setAttributeBuffer(id+i, GL_FLOAT, sizeof(GL_FLOAT)*i*4, 4, sizeof(QMatrix4x4));
        this->program->enableAttributeArray(id+i);
        glVertexAttribDivisor(id+i,1);
    }

//     RELEASE INSTANCING
    this->fullGridTransformBuffer.release();

    // RELEASE VAO
    this->indexGridVertexBufferObject.release();

    // WE CAN CLENUP BECAUSE THE INFO IS ON GPU RAM
    gridShader->cleanUp();
    this->vertexArrayGridObject.release();
    delete gridShader;

}

void OpenGLView::sendToOpenGL3DShader(){

    // ------- CREATE THE CUBE AND ARROW SHADERS ------
    ShaderData *cube =  new CubeShader();
    ShaderData *arrow = new ArrowShader();
    ShaderData *sphere = new SphereShader();
    ShaderData cube_normal = cube->generateNormal();
    // ------------------------------------------------

    // ----- SET THE NUMBER OF VERTICES AND INDEX -----
    this->numCubeVertices = cube->numVertices;
    this->numCubeIndex = cube->numIndex;
    this->numCubeNormalVertices = cube_normal.numVertices;
    this->numCubeNormalIndex = cube_normal.numIndex;
    this->numArrowVertices = arrow->numVertices;
    this->numArrowIndex = arrow->numIndex;
    this->numSphereVertices = sphere->numVertices;
    this->numSphereIndex = sphere->numIndex;

    // ------------------------------------------------


    // ---------- CREATE THE VERTEX BUFFER ------------
    int cube_buffer_size = cube->verticesBufferSize();
    int cube_normal_buffer_size = cube_normal.verticesBufferSize();
    int arrow_buffer_size = arrow->verticesBufferSize();
    int sphere_buffer_size = sphere->verticesBufferSize();

    this->vertexBufferObject.create();

    // BIND AS CURRENT VERTEX BUFFER OBJECT AND SET USAGE TYPE
    this->vertexBufferObject.bind();
    this->vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);    // SET DRAW PATTERN AS STATIC

    // ALOCATE MEMORY AND ADD DATA TO IT
    this->vertexBufferObject.allocate(cube_buffer_size + arrow_buffer_size + sphere_buffer_size + cube_normal_buffer_size);
    this->vertexBufferObject.write(0, cube->vertices, cube_buffer_size);
    this->vertexBufferObject.write(cube_buffer_size, arrow->vertices, arrow_buffer_size);
    this->vertexBufferObject.write(cube_buffer_size + arrow_buffer_size, sphere->vertices, sphere_buffer_size);
    this->vertexBufferObject.write(cube_buffer_size + arrow_buffer_size + sphere_buffer_size, cube_normal.vertices, cube_normal_buffer_size);
    this->vertexBufferObject.release();
    // ------------------------------------------------


    // ---------------- INDEX BUFFERS -----------------
    int cube_index_buffer_size = cube->indexBufferSize();
    int arrow_index_buffer_size = arrow->indexBufferSize();
    int sphere_index_buffer_size = sphere->indexBufferSize();
    int cube_normal_index_buffer_size = cube_normal.indexBufferSize();

    this->indexVertexBufferObject.create();
    this->indexVertexBufferObject.bind();
    this->indexVertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);    // SET DRAW PATTERN AS STATIC
    this->indexVertexBufferObject.allocate(cube_index_buffer_size + arrow_index_buffer_size + sphere_index_buffer_size + cube_normal_index_buffer_size);
    this->indexVertexBufferObject.write(0, cube->index, cube_index_buffer_size);
    this->indexVertexBufferObject.write(cube_index_buffer_size, arrow->index, arrow_index_buffer_size);
    this->indexVertexBufferObject.write(cube_index_buffer_size + arrow_index_buffer_size, sphere->index, sphere_index_buffer_size);
    this->indexVertexBufferObject.write(cube_index_buffer_size + arrow_index_buffer_size + sphere_index_buffer_size, cube_normal.index, cube_normal_index_buffer_size);
    this->indexVertexBufferObject.release();
    // ------------------------------------------------

    // ------------ FULL TRANSFORM BUFFER -------------
    this->fullTransformBuffer.create();
    this->fullTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    // ------------------------------------------------

    // ------ CREATE VERTEX ARRAYS TO EACH SHADER -----
    this->vertexArrayCube.create();
    this->vertexArrayArrow.create();
    this->vertexArraySphere.create();
    this->vertexArrayNormalCube.create();

    // ---------------- CUBE ARRAY --------------------
    // BIND THE CUBE VERTEX ARRAY AS CURRENT
    this->vertexArrayCube.bind();
    this->vertexBufferObject.bind();
//    this->indexVertexBufferObject.bind();

    // SET 0 TO VERTICES BUFFER
    this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
    // SET 1 TO COLORS VALUES
    this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

    // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(0, GL_FLOAT, cube->positionOffSet,cube->positionSize,cube->stride); // 0 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 0 - offset
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice


    // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(1, GL_FLOAT, cube->colorOffset, cube->colorSize, cube->stride);     // 1 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 16 - offset - (sizeof(GL_FLOAT) * 3 - (3 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                                                                //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)
    // ---------- BIND FULL TRANSFORM BUFFER -------------
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
    this->vertexArrayCube.release();
    // ---------------------------------------------------


    // ----------------- ARROW ARRAY ---------------------
    // NOW BIND THE ARRAW VERTEX ARRAY AS CURRENT
    this->vertexArrayArrow.bind();
    this->vertexBufferObject.bind();
    this->indexVertexBufferObject.bind();

    //SET 0 TO VERTICES BUFFER
    this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
    // SET 1 TO COLORS VALUES
    this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

    // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(0, GL_FLOAT, arrow->positionOffSet + cube_buffer_size, arrow->positionSize,arrow->stride); // 0 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 768 - cube vertices size + offset
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice

    // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(1, GL_FLOAT, cube_buffer_size + arrow->colorOffset, arrow->colorSize, arrow->stride);     // 1 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 768 + 16 - offset - cube vertices + (sizeof(GL_FLOAT) * 4 - (3+1 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                                                                //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)


    // ---------- BIND FULL TRANSFORM BUFFER -------------
    this->fullTransformBuffer.bind();

//    std::cout<<sizeof(float)<<std::endl;

    // SET ATTRIBUTE BUFFER TO INTERPRETER CORRECTLY THE MATRIX, WE NEED TO CREATE THIS BECAUSE THE GPU READ 4 VECTORS NOT 1 4x4 MATRIX
    // GET THE SHADER VAR ID fullTransform
    int id2 = this->program->attributeLocation("fullTransform");

    for( int i = 0; i < 4; ++i){
        this->program->setAttributeBuffer(id2+i, GL_FLOAT, sizeof(GL_FLOAT)*i*4, 4, sizeof(QMatrix4x4));
        this->program->enableAttributeArray(id2+i);
        glVertexAttribDivisor(id2+i,1);
    }

    this->vertexArrayArrow.release();
    // ---------------------------------------------------

    arrowIndexByteOffset = cube->indexBufferSize();



    // ----------------- SPHERE ARRAY ---------------------
    // NOW BIND THE ARRAW VERTEX ARRAY AS CURRENT
    this->vertexArraySphere.bind();
    this->vertexBufferObject.bind();
    this->indexVertexBufferObject.bind();

    //SET 0 TO VERTICES BUFFER
    this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
    // SET 1 TO COLORS VALUES
    this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

    // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(0, GL_FLOAT, sphere->positionOffSet + arrow_buffer_size + cube_buffer_size ,sphere->positionSize,sphere->stride); // 0 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 768 - cube vertices size + offset
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice

    // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(1, GL_FLOAT, cube_buffer_size + arrow_buffer_size + sphere->colorOffset, sphere->colorSize, sphere->stride);     // 1 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 768 + 16 - offset - cube vertices + (sizeof(GL_FLOAT) * 4 - (3+1 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                                                                //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)


    // ---------- BIND FULL TRANSFORM BUFFER -------------
    this->fullTransformBuffer.bind();

//    std::cout<<sizeof(float)<<std::endl;

    // SET ATTRIBUTE BUFFER TO INTERPRETER CORRECTLY THE MATRIX, WE NEED TO CREATE THIS BECAUSE THE GPU READ 4 VECTORS NOT 1 4x4 MATRIX
    // GET THE SHADER VAR ID fullTransform
    int id3 = this->program->attributeLocation("fullTransform");

    for( int i = 0; i < 4; ++i){
        this->program->setAttributeBuffer(id3+i, GL_FLOAT, sizeof(GL_FLOAT)*i*4, 4, sizeof(QMatrix4x4));
        this->program->enableAttributeArray(id3+i);
        glVertexAttribDivisor(id3+i,1);
    }

    this->vertexArraySphere.release();
    // ---------------------------------------------------

    sphereIndexByteOffset = cube->indexBufferSize()+arrow->indexBufferSize();



    // ----------------- CUBE NORMAL ARRAY ---------------------
    // NOW BIND THE ARRAW VERTEX ARRAY AS CURRENT
    this->vertexArrayNormalCube.bind();
    this->vertexBufferObject.bind();
    this->indexVertexBufferObject.bind();

    //SET 0 TO VERTICES BUFFER
    this->program->enableAttributeArray(0);                 // ENABLE id 0, THIS id WILL VERTICES ID
    // SET 1 TO COLORS VALUES
    this->program->enableAttributeArray(1);                 // ENABLE id 1, THIS id WILL COLOR ID

    // SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT VERTICE, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(0, GL_FLOAT, cube_normal.positionOffSet + arrow_buffer_size + cube_buffer_size + sphere_buffer_size, cube_normal.positionSize, cube_normal.stride); // 0 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 768 - cube vertices size + offset
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - 6 = 3vertices + 3colors, go to the next vertice

    // AGAIN SET BUFFER TYPE, OFFSET, TUPLE SIZE AND STRIDE TO NEXT COLOR, ON HERE WE SPECIFY HOW GLSL READ THE BUFFER DATA
    // THIS FIRST IS TO READ VERTICES INFO
    this->program->setAttributeBuffer(1, GL_FLOAT, cube_buffer_size + arrow_buffer_size + sphere_buffer_size + cube_normal.colorOffset, cube_normal.colorSize, cube_normal.stride);     // 1 - id
                                                                                                                // GL_FLOAT - Variable type
                                                                                                                // 768 + 16 - offset - cube vertices + (sizeof(GL_FLOAT) * 4 - (3+1 = vertices) (WHEN USE Vertex THE OFFSET IS 16 BECAUSE
                                                                                                                //                                                       WE ADD THE 'w' COLOR CHANNEL TO THE CLASS)
                                                                                                                // 3 - tuple size
                                                                                                                // 24 - stride (sizeof(GL_FLOAT) * 6) - (6 = 3vertices + 3colors)


    // ---------- BIND FULL TRANSFORM BUFFER -------------
    this->fullTransformBuffer.bind();

//    std::cout<<sizeof(float)<<std::endl;

    // SET ATTRIBUTE BUFFER TO INTERPRETER CORRECTLY THE MATRIX, WE NEED TO CREATE THIS BECAUSE THE GPU READ 4 VECTORS NOT 1 4x4 MATRIX
    // GET THE SHADER VAR ID fullTransform
    int id4 = this->program->attributeLocation("fullTransform");

    for( int i = 0; i < 4; ++i){
        this->program->setAttributeBuffer(id4+i, GL_FLOAT, sizeof(GL_FLOAT)*i*4, 4, sizeof(QMatrix4x4));
        this->program->enableAttributeArray(id4+i);
        glVertexAttribDivisor(id4+i,1);
    }

    this->vertexArrayNormalCube.release();
    // ---------------------------------------------------

    cubeNormalIndexByteOffset = cube->indexBufferSize() + arrow->indexBufferSize() + sphere->indexBufferSize();


    // WE CAN CLENUP BECAUSE THE INFO IS ON GPU RAM
    cube->cleanUp();
    arrow->cleanUp();
    sphere->cleanUp();
    cube_normal.cleanUp();

    delete cube;
    delete arrow;
    delete sphere;
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

//        // BIND TO THIS VERTEX ARRAY OBJECT
//        this->vertexArrayObject.bind();             // VAO
//        this->indexVertexBufferObject.bind();       // INDEX BUFFER

//        this->fullTransformBuffer.bind();
//        this->fullTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

//        QMatrix4x4 transform = this->fullPerspectiveMatrix(QVector3D(0.0, 0.0, 0.0), 0, QVector3D(1,0,0));
//        QMatrix4x4 transform2 = this->fullPerspectiveMatrix(QVector3D(1.0, 0.0, -3.75), 126, QVector3D(0,1,0));

//        QMatrix4x4 fullTransform[] = { transform, transform2 };

//        this->fullTransformBuffer.allocate(fullTransform, sizeof(fullTransform));

//        // DRAW ELEMENTS USING INDICES AND RENDER INSTANCING, THE NUMBER 3 IS THE NUMBER OF INSTANCING TO RENDER, THIS IS THE SIZE OF ARRAY INSTANCING
//        glDrawElementsInstanced(GL_TRIANGLES, numIndexToDraw, GL_UNSIGNED_SHORT, 0, 2);

//        // RELEASE ALL
//        this->fullTransformBuffer.release();
//        this->indexVertexBufferObject.release();
//        this->vertexArrayObject.release();

        // ----------------------- AMBINTE LIGHT ------------------------
        QVector4D ambientLight(1.0f, 1.0f, 1.0f, 1.0f);
        int ambient_light_location = this->program->uniformLocation("ambient_light");
        this->program->setUniformValue(ambient_light_location, ambientLight);

        // ---------------------------------------------------------------

        // ---------------------- CUBE --------------------------
        this->vertexArrayCube.bind();
        this->indexVertexBufferObject.bind();

        this->fullTransformBuffer.bind();
        this->fullTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        QMatrix4x4 transform2 = this->fullPerspectiveMatrix(QVector3D(0.0, 0.0, 0.0), 0, QVector3D(1,0,0));
        QMatrix4x4 fullTransform2[] = { transform2 };

        this->fullTransformBuffer.allocate(fullTransform2, sizeof(fullTransform2));
        glDrawElementsInstanced(GL_TRIANGLES, numCubeIndex, GL_UNSIGNED_SHORT, 0, 1);

            // NORMAL CUBE DRAW
            this->vertexArrayNormalCube.bind();
            this->indexVertexBufferObject.bind();
            glDrawElements(GL_LINES, numCubeNormalIndex, GL_UNSIGNED_SHORT, (void*)cubeNormalIndexByteOffset);


//        this->fullTransformBuffer.release();
//        this->indexVertexBufferObject.release();
//        this->vertexArrayCube.release();
//        this->vertexArrayNormalCube.release();

        // --------------------------------------------------------



        // ----------------------- ARROW --------------------------
        this->vertexArrayArrow.bind();
        this->indexVertexBufferObject.bind();

        this->fullTransformBuffer.bind();
        this->fullTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        QMatrix4x4 transform3 = this->fullPerspectiveMatrix(QVector3D(5.0, 0.0, 0.0), 0, QVector3D(1,0,0));
        QMatrix4x4 fullTransform3[]  = { transform3 };

        this->fullTransformBuffer.allocate(fullTransform3, sizeof(fullTransform3));

        glDrawElementsInstanced(GL_TRIANGLES, numArrowIndex, GL_UNSIGNED_SHORT, (void*)arrowIndexByteOffset, 1);

//        this->fullTransformBuffer.release();
//        this->indexVertexBufferObject.release();
//        this->vertexArrayArrow.release();
        // ---------------------------------------------------------

        // ------------------------ SPHERE -------------------------
        this->vertexArraySphere.bind();
        this->indexVertexBufferObject.bind();

        this->fullTransformBuffer.bind();
        this->fullTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        QMatrix4x4 transform4 = this->fullPerspectiveMatrix(QVector3D(-5.0, 0.0, 0.0), 0, QVector3D(1,0,0));
        QMatrix4x4 fullTransform4[]  = { transform4 };

        this->fullTransformBuffer.allocate(fullTransform4, sizeof(fullTransform4));

        glDrawElementsInstanced(GL_TRIANGLES, numSphereIndex, GL_UNSIGNED_SHORT, (void*)sphereIndexByteOffset, 1);

//        this->fullTransformBuffer.release();
//        this->indexVertexBufferObject.release();
//        this->vertexArraySphere.release();
        // ---------------------------------------------------------


        // ----------------------- AMBINTE LIGHT ------------------------
        ambientLight = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
        this->program->setUniformValue(ambient_light_location, ambientLight);
        // --------------------------------------------------------------

        // ------------------------- GRID --------------------------
        this->vertexArrayGridObject.bind();
        this->indexGridVertexBufferObject.bind();
        this->fullGridTransformBuffer.bind();
        this->fullGridTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

        QMatrix4x4 transform5 = this->fullPerspectiveMatrix(QVector3D(0.0, 0.0, 0.0), 0, QVector3D(0,0,0));
        QMatrix4x4 fullTransform5[] = { transform5 };

        this->fullGridTransformBuffer.allocate(fullTransform5, sizeof(fullTransform5));

        glDrawElementsInstanced(GL_LINES, numIndexToDrawGrid, GL_UNSIGNED_SHORT, 0, 1);

//        this->vertexArrayGridObject.release();
        // ---------------------------------------------------------


        // -------------------- X, Y AND Z AXIS --------------------
        this->vertexArrayAxisObject.bind();
        this->indexOrthoVertexBufferObject.bind();
        this->fullOrthoTransformBuffer.bind();
        this->fullOrthoTransformBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

        QMatrix4x4 transform6 = this->fullOrthoMatrix(QVector3D(-0.9, -0.9, -0.5), 0, QVector3D(0,0,0));
        QMatrix4x4 fullTransform6[] = { transform6 };

        this->fullOrthoTransformBuffer.allocate(fullTransform6, sizeof(fullTransform6));

        glDrawElementsInstanced(GL_LINES, numIndexToDrawAxis, GL_UNSIGNED_SHORT, 0, 1);

//        this->vertexArrayAxisObject.release();
        // ---------------------------------------------------------
    }
    this->program->release();
}

QMatrix4x4 OpenGLView::fullPerspectiveMatrix(const QVector3D& translate, const float& angle, const QVector3D& axis) const{
    // INSTANCING
    // CREATE TRANSFORM MATRIX
    QMatrix4x4 projectionMatrix;
    PerspectiveMatrix persp;
    projectionMatrix = persp.perspective(60.0f, ((float)width())/height(), 0.1f, 100.0f);

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

// MOUSE EVENTS
// MOVE
// HERE THE ROTATE AND ZOOM CAMERA OCCOURS, IS A ALT KEY IS PRESSED AND THE RIGHT MOUSE BUTTON IS PRESSED THE ZOOM ACCOURS
// ELSE THE ROTATE OCCOURS
void OpenGLView::mouseMoveEvent(QMouseEvent* e){
    QVector2D point(e->x(), e->y());
    if(!this->alt_pressed){
        if(this->ctrl_pressed){
//            printDebug("ASDASD");
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
