#version 330
layout(location = 0) in vec3 position;      // ID 0, ON POSITION IS STORED THE VERTICES POSITIONS INFO
layout(location = 1) in vec4 color;         // ID 1, ON COLOR IS STORED THE VERTICES COLOTS INFO

uniform vec4 uniformValue;
out vec4 vColor;                            // OUTPUT COLOR, THIS VAR WILL SEND TO FRAGMENT SHADER

void main()
{
  gl_Position = vec4(position, 1.0);        // SET POSITION, gl_Position is a GLSL var
  vColor = uniformValue;               // SET VColor, AFTER IS SEND TO FRAGMENT SHADER
}
