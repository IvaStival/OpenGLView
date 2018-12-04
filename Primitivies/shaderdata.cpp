#include "shaderdata.h"

ShaderData::ShaderData() : vertices(nullptr), numVertices(0), positionSize(0), colorSize(0), stride(0){}

int ShaderData::verticesBufferSize() const{
    return (this->numVertices * sizeof (Vertex));
}

void ShaderData::cleanUp(){
    delete [] this->vertices;
    this->colorSize = this->positionSize = this->numVertices = this->stride = 0;
}
