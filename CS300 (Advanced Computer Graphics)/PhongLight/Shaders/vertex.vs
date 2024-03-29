#version 400

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoords;
layout(location = 2) in vec3 vNormals;

out vec2 UV;
out vec3 Normals;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{  
   gl_Position = projection * view * model * vPosition;  
   
   UV = vTextCoords;

   Normals = mat3(transpose(inverse(view * model))) * vNormals;

   FragPos = vec3(view * model * vPosition);
}