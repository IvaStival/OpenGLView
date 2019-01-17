#ifndef SHADERGENERATOR_H
#define SHADERGENERATOR_H

#include "shaderData.h"

class ShaderGenerator{
public:
    ShaderGenerator();

    static ShaderData makeTriangle();
};

#endif // SHADERGENERATOR_H
