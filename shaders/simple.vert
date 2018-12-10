#version 330

layout(location = 0) in vec3 position;      // ID 0, ON POSITION IS STORED THE VERTICES POSITIONS INFO
layout(location = 1) in vec4 color;         // ID 1, ON COLOR IS STORED THE VERTICES COLOTS INFO
layout(location = 2) in float offset;         // ID 1, ON COLOR IS STORED THE VERTICES COLOTS INFO

//uniform vec4 uniformValue;
uniform mat4 worldMatrix;
uniform mat4 projection;
out vec4 vColor;                            // OUTPUT COLOR, THIS VAR WILL SEND TO FRAGMENT SHADER

void main()
{
//  gl_Position = worldMatrix* projection * vec4(position, 1.0);        // SET POSITION, gl_Position is a GLSL var
    vec4 v = vec4(position.x+offset, position.y, position.z, 1.0);
            vec4 newPosition = worldMatrix * v;
            vec4 projectedPosition = projection * newPosition;
            gl_Position = projectedPosition;
  vColor = color;               // SET VColor, AFTER IS SEND TO FRAGMENT SHADER
}
