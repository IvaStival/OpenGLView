#include "sphereShader.h"

#define PI 3.1415926535897932384626433832795

SphereShader::SphereShader()
{

    Vector3D color(0.5f, 0.8f, 0.5f);
    float radius = 1;
    unsigned int sectorCount = 20;
    unsigned int stackCount = 20;
    std::vector<Vertex> temp_vertices;
    std::vector<ushort> temp_indices;

    double x, y, z, xy;                              // vertex position
//    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
//    float s, t;                                     // vertex texCoord

    double sectorStep = 2 * PI / sectorCount;
    double stackStep = PI / stackCount;
    double sectorAngle, stackAngle;

    for(unsigned int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
//            temp_vertices.push_back(x);
//            temp_vertices.push_back(y);
//            temp_vertices.push_back(z);
            temp_vertices.push_back(Vertex(x,y,z,color));
            // normalized vertex normal (nx, ny, nz)
//            nx = x * lengthInv;
//            ny = y * lengthInv;
//            nz = z * lengthInv;
//            normals.push_back(nx);
//            normals.push_back(ny);
//            normals.push_back(nz);

            // vertex tex coord (s, t) range between [0, 1]
//            s = (float)j / sectorCount;
//            t = (float)i / stackCount;
//            texCoords.push_back(s);
//            texCoords.push_back(t);
        }
    }

    // generate CCW index list of sphere triangles

    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                temp_indices.push_back(k1);
                temp_indices.push_back(k2);
                temp_indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stackCount-1))
            {
                temp_indices.push_back(k1 + 1);
                temp_indices.push_back(k2);
                temp_indices.push_back(k2 + 1);
            }
        }
    }

    Vertex verts[temp_vertices.size()];
    ushort indices[temp_indices.size()];

    int count = 0;
    for(std::vector<Vertex>::iterator it = temp_vertices.begin();it != temp_vertices.end(); ++it){

        verts[count] = *it;
        count++;
    }

    count = 0;
    for(std::vector<ushort>::iterator it2 = temp_indices.begin(); it2 != temp_indices.end(); ++it2){
        indices[count] = *it2;
        count++;
    }

    this->numVertices = sizeof (verts) / sizeof(verts[0]);
    this->vertices = new Vertex[this->numVertices];
    memcpy(this->vertices, verts, sizeof(verts));

    this->numIndex = sizeof (indices) / sizeof (indices[0]);
    this->index = new ushort[this->numIndex];
    memcpy(this->index, indices, sizeof (indices));

    this->positionSize = Vertex::positionSize;
    this->colorSize = Vertex::colorSize;
    this->normalSize = Vertex::normalSize;
    this->stride = Vertex::stride();

    this->positionOffSet = Vertex::positionOffSet();
    this->colorOffset = Vertex::colorOffSet();
    this->normalOffset = Vertex::normalOffSet();

//    delete verts;
//    delete indices;
    this->normal();


}
