#include "cubeShader.h"

CubeShader::CubeShader(){


    Vector3D color(0.564, 0.905, 0.435);

//    Vertex verts[] = {
//            Vertex(-1.0f, +1.0f, +1.0f, +1.0f, +0.0f, +0.0f),
//            Vertex(+1.0f, +1.0f, +1.0f, +0.0f, +1.0f, +0.0f),
//            Vertex(+1.0f, +1.0f, -1.0f, +0.0f, +0.0f, +1.0f),
//            Vertex(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f),

//            Vertex(-1.0f, +1.0f, -1.0f, +1.0f, +0.0f, +1.0f),
//            Vertex(+1.0f, +1.0f, -1.0f, +0.0f, +0.5f, +0.2f),
//            Vertex(+1.0f, -1.0f, -1.0f, +0.8f, +0.6f, +0.4f),
//            Vertex(-1.0f, -1.0f, -1.0f, +0.3f, +1.0f, +0.5f),

//            Vertex(+1.0f, +1.0f, -1.0f, +0.2f, +0.5f, +0.2f),
//            Vertex(+1.0f, +1.0f, +1.0f, +0.9f, +0.3f, +0.7f),
//            Vertex(+1.0f, -1.0f, +1.0f, +0.3f, +0.7f, +0.5f),
//            Vertex(+1.0f, -1.0f, -1.0f, +0.5f, +0.7f, +0.5f),

//            Vertex(-1.0f, +1.0f, +1.0f, +0.7f, +0.8f, +0.2f),
//            Vertex(-1.0f, +1.0f, -1.0f, +0.5f, +0.7f, +0.3f),
//            Vertex(-1.0f, -1.0f, -1.0f, +0.4f, +0.7f, +0.7f),
//            Vertex(-1.0f, -1.0f, +1.0f, +0.2f, +0.5f, +1.0f),

//            Vertex(+1.0f, +1.0f, +1.0f, +0.6f, +1.0f, +0.7f),
//            Vertex(-1.0f, +1.0f, +1.0f, +0.6f, +0.4f, +0.8f),
//            Vertex(-1.0f, -1.0f, +1.0f, +0.2f, +0.8f, +0.7f),
//            Vertex(+1.0f, -1.0f, +1.0f, +0.2f, +0.7f, +1.0f),

//            Vertex(+1.0f, -1.0f, -1.0f, +0.8f, +0.3f, +0.7f),
//            Vertex(-1.0f, -1.0f, -1.0f, +0.8f, +0.9f, +0.5f),
//            Vertex(-1.0f, -1.0f, +1.0f, +0.5f, +0.8f, +0.5f),
//            Vertex(+1.0f, -1.0f, +1.0f, +0.9f, +1.0f, +0.2f)
//        };

    Vertex verts[] = {
            Vertex(-1.0f, +1.0f, +1.0f, color),
            Vertex(+1.0f, +1.0f, +1.0f, color),
            Vertex(+1.0f, +1.0f, -1.0f, color),
            Vertex(-1.0f, +1.0f, -1.0f, color),

            Vertex(-1.0f, +1.0f, -1.0f, color),
            Vertex(+1.0f, +1.0f, -1.0f, color),
            Vertex(+1.0f, -1.0f, -1.0f, color),
            Vertex(-1.0f, -1.0f, -1.0f, color),

            Vertex(+1.0f, +1.0f, -1.0f, color),
            Vertex(+1.0f, +1.0f, +1.0f, color),
            Vertex(+1.0f, -1.0f, +1.0f, color),
            Vertex(+1.0f, -1.0f, -1.0f, color),

            Vertex(-1.0f, +1.0f, +1.0f, color),
            Vertex(-1.0f, +1.0f, -1.0f, color),
            Vertex(-1.0f, -1.0f, -1.0f, color),
            Vertex(-1.0f, -1.0f, +1.0f, color),

            Vertex(+1.0f, +1.0f, +1.0f, color),
            Vertex(-1.0f, +1.0f, +1.0f, color),
            Vertex(-1.0f, -1.0f, +1.0f, color),
            Vertex(+1.0f, -1.0f, +1.0f, color),

            Vertex(+1.0f, -1.0f, -1.0f, color),
            Vertex(-1.0f, -1.0f, -1.0f, color),
            Vertex(-1.0f, -1.0f, +1.0f, color),
            Vertex(+1.0f, -1.0f, +1.0f, color)
        };



    ushort indices[] = {
            0,   1,  2,  0,  2,  3, // Top
            4,   5,  6,  4,  6,  7, // Front
            8,  9,  10,  8, 10, 11, // Right
            12, 13, 14, 12, 14, 15, // Left
            16, 17, 18, 16, 18, 19, // Back
            20, 23, 22, 20, 22, 21,  // Bottom

        };

    this->numVertices = sizeof (verts) / sizeof(verts[0]);
    this->vertices = new Vertex[this->numVertices];
    memcpy(this->vertices, verts, sizeof(verts));

    this->numIndex = sizeof (indices) / sizeof (indices[0]);
    this->index = new ushort[this->numIndex];
    memcpy(this->index, indices, sizeof (indices));

    this->positionSize = Vertex::positionSize;
    this->colorSize = Vertex::colorSize;
    this->normalSize = Vertex::normalSize;
    this->stride = Vertex::stride();

    this->positionOffSet = Vertex::positionOffSet();
    this->colorOffset = Vertex::colorOffSet();
    this->normalOffset = Vertex::normalOffSet();
    this->normal();

};
