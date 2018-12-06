#ifndef SHADERDATA_H
#define SHADERDATA_H

#include "vertex.h"

class Vertex;

class ShaderData{
public:
    Vertex* vertices;
    ushort* index;
    int numVertices;
    int numIndex;
    int positionSize;
    int colorSize;
    int positionOffSet;
    int colorOffset;
    int stride;

    ShaderData();

    int verticesBufferSize() const;
    int indexBufferSize() const;
    void cleanUp();

};

#endif // SHADERDATA_H
