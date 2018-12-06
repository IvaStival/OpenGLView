#ifndef SHADERGENERATOR_H
#define SHADERGENERATOR_H

#include "shaderdata.h"

class ShaderGenerator{
public:
    ShaderGenerator();

    static ShaderData makeTriangle();
};

#endif // SHADERGENERATOR_H
