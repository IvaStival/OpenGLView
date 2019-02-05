#ifndef SHADERDATA_H
#define SHADERDATA_H

#include "vertex.h"
#include "Math/vector3d.h"
#include "math.h"
#include <QVector3D>

class Vertex;

class ShaderData{
public:
    Vertex* vertices;
    ushort* index;
    int numVertices;
    int numIndex;
    int positionSize;
    int colorSize;
    int normalSize;
    int positionOffSet;
    int colorOffset;
    int normalOffset;
    int stride;

    ShaderData();

    int verticesBufferSize() const;
    int indexBufferSize() const;

    void normal();
    ShaderData& generateNormal() const;

    void cleanUp();

};

#endif // SHADERDATA_H
