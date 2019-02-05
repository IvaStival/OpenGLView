#ifndef PLANESHADER_H
#define PLANESHADER_H

#include "shaderData.h"

class PlaneShader : public ShaderData
{
private:
    int dimensions;
public:
    PlaneShader();
    PlaneShader(int dimension);

    void make();
};

#endif // PLANESHADER_H
