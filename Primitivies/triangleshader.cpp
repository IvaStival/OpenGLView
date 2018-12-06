#include "triangleshader.h"

TriangleShader::TriangleShader()
{

    Vertex verts[] = {Vertex(0.00f,  0.75f, 1.0f, 0.0f, 0.0f, 1.0f),
                      Vertex(0.75f, -0.75f, -0.5f, 0.0f, 1.0f, 0.0f),
                      Vertex(-0.75f, -0.75f, -0.5f, 1.0f, 0.0f, 0.0f)};

    ushort ind[] = { 0, 1, 2 };

    this->numVertices = sizeof (verts) / sizeof(verts[0]);
    this->vertices = new Vertex[this->numVertices];
    memcpy(this->vertices, verts, sizeof(verts));

    this->numIndex = sizeof (ind) / sizeof (ind[0]);
    this->index = new ushort[this->numIndex];
    memcpy(this->index, ind, sizeof (ind));

    this->positionSize = Vertex::positionSize;
    this->colorSize = Vertex::colorSize;
    this->stride = Vertex::stride();

    this->positionOffSet = Vertex::positionOffSet();
    this->colorOffset = Vertex::colorOffSet();
}
