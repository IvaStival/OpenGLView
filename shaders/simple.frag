#version 330 core               // FRAGMENT SHADER WILL CALCULATE TO ALL PIXELS OF THE GEOMETRY GENERATED ON VERTEX SHADER

uniform vec4 ambient_light;
uniform vec3 point_light;

in vec4 vColor;                 // VAR COLOR SEND BY VERTEX SHADER
in vec3 vNormal;
in vec3 vPositon;
out vec4 fColor;                // RESULT VAR COLOR, THIS VAR WILL

void main()
{
    vec3 vectorLight = normalize(point_light - vPositon);
    float brightness = max(dot(vectorLight, vNormal), 0.0);
    fColor = vColor * (brightness + ambient_light);
//    fColor = vec4(brightness, brightness, brightness, 1);
}
