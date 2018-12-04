#ifndef SHADERDATA_H
#define SHADERDATA_H

#include "vertex.h"

class Vertex;

class ShaderData{
public:
    Vertex* vertices;
    int numVertices;
    int positionSize;
    int colorSize;
    int positionOffSet;
    int colorOffset;
    int stride;

    ShaderData();

    int verticesBufferSize() const;
    void cleanUp();

};

#endif // SHADERDATA_H
