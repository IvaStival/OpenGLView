#version 330                    // FRAGMENT SHADER WILL CALCULATE TO ALL PIXELS OF THE GEOMETRY GENERATED ON VERTEX SHADER

in vec4 vColor;                 // VAR COLOR SEND BY VERTEX SHADER
out vec4 fColor;                // RESULT VAR COLOR, THIS VAR WILL

void main()
{
   fColor = vColor;
}
