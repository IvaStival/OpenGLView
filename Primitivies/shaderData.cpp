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

// CALCULATE ALL VERTICES NORMALS
void ShaderData::normal(){


    for(int i=0; i<this->numIndex; ++i){
        Vector3D v1(this->vertices[this->index[i]].getPosition());
        Vector3D v2(this->vertices[this->index[i+1]].getPosition());
        Vector3D v3(this->vertices[this->index[i+2]].getPosition());

        Vector3D ver1;
        Vector3D ver2;

        ver1 = (v3 - v2);
        ver2 = (v1 - v2);

//        std::cout << "V3 = " << v3 << std::endl;
//        std::cout << "V2 = " << v2 << std::endl;
//        std::cout << "V1 = " << v1 << std::endl;

//        std::cout << "ver1 = " << ver1 << std::endl;
//        std::cout << "ver2 = " << ver2 << std::endl;

        QVector3D cross_result = QVector3D::crossProduct(QVector3D(ver1.getX(), ver1.getY(), ver1.getZ()), QVector3D(ver2.getX(), ver2.getY(), ver2.getZ()));
        float dist = sqrt(cross_result.x()*cross_result.x() + cross_result.y()*cross_result.y() + cross_result.z()*cross_result.z());

        QVector3D N = cross_result/dist;

//        std::cout << "Cross = " << cross_result.x() << " " << cross_result.y() << " " << cross_result.z() << std::endl;
//        std::cout << "N = " << N.x() << " " << N.y() << " " << N.z() << std::endl;

        this->vertices[this->index[i]].setNormal(N.x(), N.y(), N.z());
        this->vertices[this->index[i+1]].setNormal(N.x(), N.y(), N.z());
        this->vertices[this->index[i+2]].setNormal(N.x(), N.y(), N.z());

//        std::cout<<this->vertices[this->index[i]].getNormal() << std::endl;
//        std::cout<<this->vertices[this->index[i+1]].getNormal() << std::endl;
//        std::cout<<this->vertices[this->index[i+2]].getNormal() << std::endl;

        i+=2;
    }
}


// GENERATE THE SHADER WITH NORMAL VERTICES AND INDEX
ShaderData& ShaderData::generateNormal() const{

    ShaderData result;
    result.numVertices = this->numVertices*2;
    result.vertices = new Vertex[result.numVertices];

    Vector3D color(1.0f, 1.0f, 1.0f);

    for(int i=0; i<this->numVertices; ++i){
        int index = i * 2;
        Vector3D v(this->vertices[i].getPosition());
        Vector3D n(this->vertices[i].getNormal());

        Vertex& p1 = result.vertices[index];
        Vertex& p2 = result.vertices[index+1];

        p1.setPosition(v);
        p2.setPosition(v+n);
        p1.setColor(color);
        p2.setColor(color);

//        std::cout << p1.getPosition() << std::endl;
//        std::cout << p2.getPosition() << std::endl;
    }

    result.numIndex = result.numVertices;
    result.index = new ushort[result.numIndex];

    for(int i = 0; i<result.numIndex; ++i){
        result.index[i] = i;
    }

    result.positionSize = Vertex::positionSize;
    result.colorSize = Vertex::colorSize;
    result.stride = Vertex::stride();

    result.positionOffSet = Vertex::positionOffSet();
    result.colorOffset = Vertex::colorOffSet();

    return result;
}
