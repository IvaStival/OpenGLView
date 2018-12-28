#include "gridshader.h"

gridShader::gridShader()
{
    Vector3D color(0.9f, 0.9f, 0.9f);
    Vertex verts[] = {
        Vertex(0.0f, 0.0f, -1.0f, color),
        Vertex(0.0f, 0.0f, 1.0f, color),

        Vertex(-1.0f, 0.0f, -1.0f, color),
        Vertex(-1.0f, 0.0f, 1.0f, color),

        Vertex(1.0f, 0.0f, -1.0f, color),
        Vertex(1.0f, 0.0f, 1.0f, color),

        Vertex(-1.0f, 0.0f, -1.0f, color),
        Vertex(1.0f, 0.0f, -1.0f, color),

        Vertex(-1.0f, 0.0f, 1.0f, color),
        Vertex(1.0f, 0.0f, 1.0f, color),

    };

    ushort indices[] = {
        0, 1, // Y
        2, 3, // X
        4, 5,
        6, 7,
        8, 9
    };

    this->numVertices = sizeof (verts) / sizeof(verts[0]);
    this->vertices = new Vertex[this->numVertices];
    memcpy(this->vertices, verts, sizeof(verts));

    this->numIndex = sizeof (indices) / sizeof (indices[0]);
    this->index = new ushort[this->numIndex];
    memcpy(this->index, indices, sizeof (indices));

    this->positionSize = Vertex::positionSize;
    this->colorSize = Vertex::colorSize;
    this->stride = Vertex::stride();

    this->positionOffSet = Vertex::positionOffSet();
    this->colorOffset = Vertex::colorOffSet();

}

