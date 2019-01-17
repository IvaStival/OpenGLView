#include "shaderGenerator.h"
#include <iostream>

ShaderGenerator::ShaderGenerator(){}

ShaderData ShaderGenerator::makeTriangle(){

    ShaderData data;
    Vertex verts[] = {Vertex(0.00f,  0.75f, 1.0f, 0.0f, 0.0f, 1.0f),
                      Vertex(0.75f, -0.75f, -0.5f, 0.0f, 1.0f, 0.0f),
                      Vertex(-0.75f, -0.75f, -0.5f, 1.0f, 0.0f, 0.0f)};


    data.numVertices = sizeof (verts) / sizeof(verts[0]);
    data.vertices = new Vertex[data.numVertices];
    memcpy(data.vertices, verts, sizeof(verts));

    data.positionSize = Vertex::positionSize;
    data.colorSize = Vertex::colorSize;
    data.stride = Vertex::stride();

    data.positionOffSet = Vertex::positionOffSet();
    data.colorOffset = Vertex::colorOffSet();

    return data;
}
