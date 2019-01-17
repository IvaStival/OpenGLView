#include "shaderData.h"

ShaderData::ShaderData() : vertices(nullptr), numVertices(0), positionSize(0), colorSize(0), stride(0){}

int ShaderData::verticesBufferSize() const{
    return (this->numVertices * sizeof (Vertex));
}

int ShaderData::indexBufferSize() const{
    return (this->numIndex * sizeof (ushort));
}

void ShaderData::cleanUp(){
    delete [] this->vertices;
    this->colorSize = this->positionSize = this->numVertices = this->stride = 0;
}

