#version 400

layout(location = 0) in vec4 vPosition;

uniform mat4 model;
uniform mat4 LightSpaceMatrix;

void main()
{  
   gl_Position = LightSpaceMatrix * model * vPosition;  
   
}