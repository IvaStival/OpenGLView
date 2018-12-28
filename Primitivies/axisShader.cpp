#include "axisShader.h"

AxisShader::AxisShader()
{

    Vertex verts[] = {
        Vertex(0.0f, 0.0f, 0.0f, +0.0f, +1.0f, +0.0f),
        Vertex(0.0f, 0.1f, 0.0f, +0.0f, +1.0f, +0.0f),

        Vertex(0.0f, 0.0f, 0.0f, +1.0f, +0.0f, +0.0f),
        Vertex(0.1f, 0.0f, 0.0f, +1.0f, +0.0f, +0.0f),

        Vertex(0.0f, 0.0f, 0.0f, +0.0f, +0.0f, +1.0f),
        Vertex(0.0f, 0.0f, -0.1f, +0.0f, +0.0f, +1.0f)
    };

    ushort indices[] = {
        0, 1, // Y
        2, 3, // X
        4, 5
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
