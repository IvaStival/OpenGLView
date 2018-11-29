#version 330
layout(location = 0) in vec3 position;      // ID 0, ON POSITION IS STORED THE VERTICES POSITIONS INFO
layout(location = 1) in vec3 color;         // ID 1, ON COLOR IS STORED THE VERTICES COLOTS INFO
out vec4 vColor;                            // OUTPUT COLOR, THIS VAR WILL SEND TO FRAGMENT SHADER

void main()
{
  gl_Position = vec4(position, 1.0);        // SET POSITION, gl_Position is a GLSL var
  vColor = vec4(color, 1.0f);               // SET VColor, AFTER IS SEND TO FRAGMENT SHADER
}
