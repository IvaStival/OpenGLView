#version 330 core

layout(location = 0) in vec3 position;      // ID 0, ON POSITION IS STORED THE VERTICES POSITIONS INFO
layout(location = 1) in vec4 color;         // ID 1, ON COLOR IS STORED THE VERTICES COLOTS INFO
layout(location = 2) in mat4 fullTransform; // ID 2, WERE IS THE COMPLETE TRANSFORMA AND PROJECTION MATRIX

out vec4 vColor;                            // OUTPUT COLOR, THIS VAR WILL SEND TO FRAGMENT SHADER

void main()
{
//  gl_Position = worldMatrix* projection * vec4(position, 1.0);        // SET POSITION, gl_Position is a GLSL var
    vec4 v = vec4(position, 1.0);
    gl_Position = fullTransform * v;
    vColor = color;               // SET VColor, AFTER IS SEND TO FRAGMENT SHADER
}
