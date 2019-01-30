#include "arrowShader.h"

ArrowShader::ArrowShader(){
    Vertex verts[] = {
        // Top side of arrow head
            Vertex(+0.00f, +0.25f, -0.25f, +1.00f, +0.00f, +0.00f),
            Vertex(+0.50f, +0.25f, -0.25f, +1.00f, +0.00f, +0.00f),
            Vertex(+0.00f, +0.25f, -1.00f, 1.00f, +0.00f, +0.00f),
            Vertex(-0.50f, +0.25f, -0.25f, +1.00f, +0.00f, +0.00f),

            // Bottom side of arrow head
            Vertex(+0.00f, -0.25f, -0.25f, +0.00f, +0.00f, +1.00f),
            Vertex(+0.50f, -0.25f, -0.25f, +0.00f, +0.00f, +1.00f),
            Vertex(+0.00f, -0.25f, -1.00f, +0.00f, +0.00f, +1.00f),
            Vertex(-0.50f, -0.25f, -0.25f, +0.00f, +0.00f, +1.00f),

            // Right side of arrow tip
            Vertex(+0.50f, +0.25f, -0.25f, +0.60f, +1.00f, +0.00f),
            Vertex(+0.00f, +0.25f, -1.00f, +0.60f, +1.00f, +0.00f),
            Vertex(+0.00f, -0.25f, -1.00f, +0.60f, +1.00f, +0.00f),
            Vertex(+0.50f, -0.25f, -0.25f, +0.60f, +1.00f, +0.00f),

            // Left side of arrow tip
            Vertex(+0.00f, +0.25f, -1.00f, +0.00f, +1.00f, +0.00f),
            Vertex(-0.50f, +0.25f, -0.25f, +0.00f, +1.00f, +0.00f),
            Vertex(+0.00f, -0.25f, -1.00f, +0.00f, +1.00f, +0.00f),
            Vertex(-0.50f, -0.25f, -0.25f, +0.00f, +1.00f, +0.00f),

            // Back side of arrow tip
            Vertex(-0.50f, +0.25f, -0.25f, +0.50f, +0.50f, +0.50f),
            Vertex(+0.50f, +0.25f, -0.25f, +0.50f, +0.50f, +0.50f),
            Vertex(-0.50f, -0.25f, -0.25f, +0.50f, +0.50f, +0.50f),
            Vertex(+0.50f, -0.25f, -0.25f, +0.50f, +0.50f, +0.50f),

            // Top side of back of arrow
            Vertex(+0.25f, +0.25f, -0.25f, +1.00f, +0.00f, +0.00f),
            Vertex(+0.25f, +0.25f, +1.00f, +1.00f, +0.00f, +0.00f),
            Vertex(-0.25f, +0.25f, +1.00f, +1.00f, +0.00f, +0.00f),
            Vertex(-0.25f, +0.25f, -0.25f, +1.00f, +0.00f, +0.00f),

            // Bottom side of back of arrow
            Vertex(+0.25f, -0.25f, -0.25f, +0.00f, +0.00f, +1.00f),
            Vertex(+0.25f, -0.25f, +1.00f, +0.00f, +0.00f, +1.00f),
            Vertex(-0.25f, -0.25f, +1.00f, +0.00f, +0.00f, +1.00f),
            Vertex(-0.25f, -0.25f, -0.25f, +0.00f, +0.00f, +1.00f),

            // Right side of back of arrow
            Vertex(+0.25f, +0.25f, -0.25f, +0.60f, +1.00f, +0.00f),
            Vertex(+0.25f, -0.25f, -0.25f, +0.60f, +1.00f, +0.00f),
            Vertex(+0.25f, -0.25f, +1.00f, +0.60f, +1.00f, +0.00f),
            Vertex(+0.25f, +0.25f, +1.00f, +0.60f, +1.00f, +0.00f),

            // Left side of back of arrow
            Vertex(-0.25f, +0.25f, -0.25f, +0.00f, +1.00f, +0.00f),
            Vertex(-0.25f, -0.25f, -0.25f, +0.00f, +1.00f, +0.00f),
            Vertex(-0.25f, -0.25f, +1.00f, +0.00f, +1.00f, +0.00f),
            Vertex(-0.25f, +0.25f, +1.00f, +0.00f, +1.00f, +0.00f),

            // Back side of back of arrow
            Vertex(-0.25f, +0.25f, +1.00f, +0.50f, +0.50f, +0.50f),
            Vertex(+0.25f, +0.25f, +1.00f, +0.50f, +0.50f, +0.50f),
            Vertex(-0.25f, -0.25f, +1.00f, +0.50f, +0.50f, +0.50f),
            Vertex(+0.25f, -0.25f, +1.00f, +0.50f, +0.50f, +0.50f),

    };

    ushort indices[] = {
        0, 1, 2, // Top
        0, 2, 3,
        4, 6, 5, // Bottom
        4, 7, 6,
        8, 10, 9, // Right side of arrow tip
        8, 11, 10,
        12, 15, 13, // Left side of arrow tip
        12, 14, 15,
        16, 19, 17, // Back side of arrow tip
        16, 18, 19,
        20, 22, 21, // Top side of back of arrow
        20, 23, 22,
        24, 25, 26, // Bottom side of back of arrow
        24, 26, 27,
        28, 30, 29, // Right side of back of arrow
        28, 31, 30,
        32, 33, 34, // Left side of back of arrow
        32, 34, 35,
        36, 39, 37, // Back side of back of arrow
        36, 38, 39,
    };

    this->numVertices = sizeof (verts) / sizeof(verts[0]);
    this->vertices = new Vertex[this->numVertices];
    memcpy(this->vertices, verts, sizeof(verts));

    this->numIndex = sizeof (indices) / sizeof (indices[0]);
    this->index = new ushort[this->numIndex];
    memcpy(this->index, indices, sizeof (indices));

    this->positionSize = Vertex::positionSize;
    this->colorSize = Vertex::colorSize;
    this->stride = Vertex::stride();

    this->positionOffSet = Vertex::positionOffSet();
    this->colorOffset = Vertex::colorOffSet();
    this->normal();


}
