#include "planeShader.h"

PlaneShader::PlaneShader() : dimensions(21) {
    this->make();
}
PlaneShader::PlaneShader(int dimension) : dimensions(dimension) {
    this->make();
}

void PlaneShader::make() {
    int half = this->dimensions/2;

    this->numVertices = this->dimensions * this->dimensions;
    this->vertices = new Vertex[this->numVertices];
    this->numIndex = (this->dimensions - 1) * (this->dimensions -1) * 2 * 3; // 2 triangles per square, 3 indices per triangle

    this->index = new u_short[this->numIndex];

    Vector3D color(0.5f, 0.5f, 0.5f);

    for(int i = 0; i < this->dimensions; ++i){
        for(int j = 0; j < this->dimensions; ++j){

            Vertex& vert = this->vertices[i * this->dimensions + j];
            vert.setPosition((j-half), 0, (i - half));
            vert.setNormal(0.0f, 1.0f, 0.0f);
            vert.setColor(color);
        }
    }

    int count = 0;
    for(int row = 0; row < this->dimensions - 1; row++){
        for(int col = 0; col < this->dimensions -1 ; col++){

            this->index[count++] = this->dimensions * row + col;
            this->index[count++] = this->dimensions * row + col + this->dimensions;
            this->index[count++] = this->dimensions * row + col + this->dimensions + 1;

            this->index[count++] = this->dimensions * row + col;
            this->index[count++] = this->dimensions * row + col + this->dimensions + 1;
            this->index[count++] = this->dimensions * row + col + 1;
        }
    }

    this->positionSize = Vertex::positionSize;
    this->colorSize = Vertex::colorSize;
    this->normalSize = Vertex::normalSize;
    this->stride = Vertex::stride();

    this->positionOffSet = Vertex::positionOffSet();
    this->colorOffset = Vertex::colorOffSet();
    this->normalOffset = Vertex::normalOffSet();
}
