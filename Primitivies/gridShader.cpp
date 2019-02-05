#include "gridShader.h"

GridShader::GridShader()
{
    Vector3D color(0.1f, 0.1f, 0.1f);
    int size = 10;
    Vertex verts[] = {
        Vertex(-size, 0.0f, 0.0f, color),
        Vertex(size, 0.0f, 0.0f, color),

        Vertex(0.0f, 0.0f, -size, color),
        Vertex(0.0f, 0.0f, size, color),

        //////////////////////////////////////////////////
        // HORIZONTAL RIGHT
        //////////////////////////////////////////////////
        Vertex(1.0f, 0.0f, -size, color),
        Vertex(1.0f, 0.0f, size, color),

        Vertex(2.0f, 0.0f, -size, color),
        Vertex(2.0f, 0.0f, size, color),

        Vertex(3.0f, 0.0f, -size, color),
        Vertex(3.0f, 0.0f, size, color),

        Vertex(4.0f, 0.0f, -size, color),
        Vertex(4.0f, 0.0f, size, color),

        Vertex(5.0f, 0.0f, -size, color),
        Vertex(5.0f, 0.0f, size, color),

        Vertex(6.0f, 0.0f, -size, color),
        Vertex(6.0f, 0.0f, size, color),

        Vertex(7.0f, 0.0f, -size, color),
        Vertex(7.0f, 0.0f, size, color),

        Vertex(8.0f, 0.0f, -size, color),
        Vertex(8.0f, 0.0f, size, color),

        Vertex(9.0f, 0.0f, -size, color),
        Vertex(9.0f, 0.0f, size, color),

        Vertex(size, 0.0f, -size, color),
        Vertex(size, 0.0f, size, color),

        //////////////////////////////////////////////////
        // HORIZONTAL LEFT
        //////////////////////////////////////////////////
        Vertex(-1.0f, 0.0f, -size, color),
        Vertex(-1.0f, 0.0f, size, color),

        Vertex(-2.0f, 0.0f, -size, color),
        Vertex(-2.0f, 0.0f, size, color),

        Vertex(-3.0f, 0.0f, -size, color),
        Vertex(-3.0f, 0.0f, size, color),

        Vertex(-4.0f, 0.0f, -size, color),
        Vertex(-4.0f, 0.0f, size, color),

        Vertex(-5.0f, 0.0f, -size, color),
        Vertex(-5.0f, 0.0f, size, color),

        Vertex(-6.0f, 0.0f, -size, color),
        Vertex(-6.0f, 0.0f, size, color),

        Vertex(-7.0f, 0.0f, -size, color),
        Vertex(-7.0f, 0.0f, size, color),

        Vertex(-8.0f, 0.0f, -size, color),
        Vertex(-8.0f, 0.0f, size, color),

        Vertex(-9.0f, 0.0f, -size, color),
        Vertex(-9.0f, 0.0f, size, color),

        Vertex(-10.0f, 0.0f, -size, color),
        Vertex(-10.0f, 0.0f, size, color),

        //////////////////////////////////////////////////
        // VERTICAL UP
        //////////////////////////////////////////////////
        Vertex(-size, 0.0f, -1.0f, color),
        Vertex(size, 0.0f, -1.0f, color),

        Vertex(-size, 0.0f, -2.0f, color),
        Vertex(size, 0.0f, -2.0f, color),

        Vertex(-size, 0.0f, -3.0f, color),
        Vertex(size, 0.0f, -3.0f, color),

        Vertex(-size, 0.0f, -4.0f, color),
        Vertex(size, 0.0f, -4.0f, color),

        Vertex(-size, 0.0f, -5.0f, color),
        Vertex(size, 0.0f, -5.0f, color),

        Vertex(-size, 0.0f, -6.0f, color),
        Vertex(size, 0.0f, -6.0f, color),

        Vertex(-size, 0.0f, -7.0f, color),
        Vertex(size, 0.0f, -7.0f, color),

        Vertex(-size, 0.0f, -8.0f, color),
        Vertex(size, 0.0f, -8.0f, color),

        Vertex(-size, 0.0f, -9.0f, color),
        Vertex(size, 0.0f, -9.0f, color),

        Vertex(-size, 0.0f, -size, color),
        Vertex(size, 0.0f, -size, color),

        //////////////////////////////////////////////////
        // VERTICAL DOWN
        //////////////////////////////////////////////////
        Vertex(-size, 0.0f, 1.0f, color),
        Vertex(size, 0.0f, 1.0f, color),

        Vertex(-size, 0.0f, 2.0f, color),
        Vertex(size, 0.0f, 2.0f, color),

        Vertex(-size, 0.0f, 3.0f, color),
        Vertex(size, 0.0f, 3.0f, color),

        Vertex(-size, 0.0f, 4.0f, color),
        Vertex(size, 0.0f, 4.0f, color),

        Vertex(-size, 0.0f, 5.0f, color),
        Vertex(size, 0.0f, 5.0f, color),

        Vertex(-size, 0.0f, 6.0f, color),
        Vertex(size, 0.0f, 6.0f, color),

        Vertex(-size, 0.0f, 7.0f, color),
        Vertex(size, 0.0f, 7.0f, color),

        Vertex(-size, 0.0f, 8.0f, color),
        Vertex(size, 0.0f, 8.0f, color),

        Vertex(-size, 0.0f, 9.0f, color),
        Vertex(size, 0.0f, 9.0f, color),

        Vertex(-size, 0.0f, size, color),
        Vertex(size, 0.0f, size, color),

    };

    ushort indices[] = {
        0, 1,
        2, 3,
        4, 5,
        6, 7,
        8, 9,
        10,11,
        12,13,
        14,15,
        16,17,
        18,19,
        20,21,
        22,23,

        24,25,
        26,27,
        28,29,
        30,31,
        32,33,
        34,35,
        36,37,
        38,39,
        40,41,
        42,43,
        44,45,

        46,47,
        48,49,
        50,51,
        52,53,
        54,55,
        56,57,
        58,59,
        60,61,
        62,63,

        64,65,
        66,67,
        68,69,
        70,71,
        72,73,
        74,75,
        76,77,
        78,79,
        80,81,
        82,83,

    };

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

}

