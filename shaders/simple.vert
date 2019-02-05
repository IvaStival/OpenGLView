#version 330 core

layout(location = 0) in vec3 position;      // ID 0, ON POSITION IS STORED THE VERTICES POSITIONS INFO
layout(location = 1) in vec4 color;         // ID 1, ON COLOR IS STORED THE VERTICES COLOTS INFO
layout(location = 2) in vec3 normal;         // ID 2, ON NORMAL IS STORED THE VERTICES COLOTS INFO
layout(location = 3) in mat4 fullTransform; // ID 2, WERE IS THE COMPLETE TRANSFORMA AND PROJECTION MATRIX

uniform mat4 modelToWorld;

out vec4 vColor;                            // OUTPUT COLOR, THIS VAR WILL SEND TO FRAGMENT SHADER
out vec3 vNormal;
out vec3 vPositon;

void main()
{
//  gl_Position = worldMatrix* projection * vec4(position, 1.0);        // SET POSITION, gl_Position is a GLSL var
    vec4 v = vec4(position, 1.0);
    gl_Position = fullTransform * v;
    vNormal = mat3(modelToWorld) * normal;
    vPositon = vec3(modelToWorld * v);

    if(normal.x == 0 && normal.y == 0 && normal.z == 0){
        vNormal = vec3(0.0, 1.0, 0.0);
        vPositon = vec3(0.0, 0.0, 0.0);
    }
//    vColor = color * ambient_light;               // SET VColor, AFTER IS SEND TO FRAGMENT SHADER
//    vColor = color * brightness;
    vColor = color;
}
